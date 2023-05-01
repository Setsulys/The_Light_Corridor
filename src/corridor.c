#include "../includes/corridor.h"

#include "../includes/3D_tools.h"
#include "../includes/draw_scene.h"
#include "../includes/corridorDrawing.h"
#include "../includes/level.h"
#include "../includes/lights.h"
#include "../includes/objects.h"
#include "../includes/music.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../includes/stb_image.h"

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "Light corridor";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

static const int size =1;
GLuint texture[size];
const char * path[size] = {"/home/setsuly/Documents/Synthese/project/the_light_corridor/src/silver.png"};
	
/* Menu or not*/
	bool menu = true;
	bool game = true;
	bool win = false;
/*Ball bounce values*/

float ballVertical =0;
float ballHorizontal =0;
float ballFront =2;

int toTheLeft =0;
int toTheFront = 0;
int toTheDown = 0;

/* Error handling function */
void onError(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,aspectRatio,Z_NEAR,Z_FAR);
	glMatrixMode(GL_MODELVIEW);
}



void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_A :
			case GLFW_KEY_ESCAPE :
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
/////////////////////////Cas de débuggage				
			case GLFW_KEY_KP_9 :
				if(dist_zoom<100.0f) dist_zoom*=1.1;
				printf("Zoom is %f\n",dist_zoom);
				break;
			case GLFW_KEY_KP_3 :
				if(dist_zoom>1.0f) dist_zoom*=0.9;
				printf("Zoom is %f\n",dist_zoom);
				break;
			case GLFW_KEY_KP_8 :
				if (phy>2) phy -= 2;
				printf("Phy %f\n",phy);
				break;
			case GLFW_KEY_KP_5 :
				if (phy<=88.) phy += 2;
				printf("Phy %f\n",phy);
				break;
			case GLFW_KEY_KP_4 :
				theta -= 5;
				break;
			case GLFW_KEY_KP_6 :
				theta += 5;
				break;
			//changement lumiere
			case GLFW_KEY_P :
				up+=0.5;
				break;
			case GLFW_KEY_M :
				up-=0.5;
				break;
////////////////////////////////
			//mouvement de raquette	
			case GLFW_KEY_UP  :
				if(vertical < 3){
					vertical += 0.5;
				}
				break;
			case GLFW_KEY_LEFT :
				if(horizontal > -3){
					horizontal -= 0.5;
				}
				break;
			case  GLFW_KEY_DOWN:
				if(vertical > -3){
					vertical -= 0.5;
				}
				break;
			case GLFW_KEY_RIGHT :
				if(horizontal < 3  ){
					horizontal += 0.5;
				}
				break;
			case GLFW_KEY_TAB:
				if(menu ==false){
					posCamera+=10;
				}
				break;
			case GLFW_KEY_LEFT_SHIFT:
				if(menu == false){
					if(posCamera >=2){
						posCamera-=10;
					}
				}
				break;
			case GLFW_KEY_ENTER : 
				if(menu == true){
					menu =false;
				}else{
					toTheFront =1;
				}
				break;
			default: fprintf(stdout,"Touche non gérée (%d)\n",key);
		}
	}
}

void mouse_button_callback(GLFWwindow* window, int button,int action,int mods){
	double x;
	double y;

	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		glfwGetCursorPos(window,&x,&y);
		if(x >=  410 && x <= 560 && y >=449 && y <=537){
			if(menu==true){
				menu = false;
			}
		}
		if(x >=  410 && x <= 560 && y >=562 && y <=661){
			if(menu == true){
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}
		if(x >=  410 && x <= 560 && y >=600 && y <=690){
			if(menu == false && game == false){
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}
	}
}


void output(int x, int y, float r, float g, float b, void * font, char *string)
{
  glColor3f( r, g, b );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}


void button(){
	glPushMatrix();
	glRotatef(90,0,1,0);
	glTranslatef(2,7.75,4);
	drawSquare();
	glPopMatrix();
}


int main(int argc, char** argv)
{
	srand(time(NULL));
	/* GLFW initialisation */
	GLFWwindow* window;
	glutInit(&argc,argv);
	if (!glfwInit()) return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);

	/*Mouse*/
	glfwSetMouseButtonCallback(window,mouse_button_callback);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);

	Mix_Music * music = init_audio();
	
	// // // //Stating TExture
	int width, height, n;
	//stbi_set_flip_vertically_on_load(true);
	unsigned char * data = stbi_load("imgs/backs.png",&width,&height,&n,0);
	if(!data){
		printf("error picture not loaded\n");
		return 1;
	}
	GLuint texture;
	glGenTextures(1,&texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);

	stbi_image_free(data);

	data = stbi_load("imgs/heart.png",&width,&height,&n,0);
	if(!data){
		printf("error picture not loaded\n");
		return 1;
	}
	GLuint textureHeart;
	glGenTextures(1,&textureHeart);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textureHeart);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);

	stbi_image_free(data);
	
	int distanceObstacle=0;
	int countLife = 3;

	Mix_PlayMusic(music,-1);
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();
		/* Cleaning buffers and setting Matrix Mode */
		if(menu == true){
			//menu
			glClearColor(0.5,0.5,0.5,0.5);
			drawSceneLight();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();
			setCamera();

			glPushMatrix();
			glRotatef(90,0,0,1);
			glTranslatef(-5,-5,0);
			drawWall(10,10,texture);
			glPopMatrix();
			glPushMatrix();
			const char * text="THE LIGHT CORRIDOR";
			char buffer[20];
			strcpy(buffer,text);
			glTranslatef(2,-8,7);
			output(5,7,1,1,1,GLUT_BITMAP_TIMES_ROMAN_24,buffer);

			//Buttons
			glPushMatrix();
			text = "JOUER";
			strcpy(buffer,text);
			glTranslatef(0,0.60,-1.85);
			output(5,7,1,1,1,GLUT_BITMAP_TIMES_ROMAN_24,buffer);
			glTranslatef(0,0,-0.85);
			text = "QUITTER";
			strcpy(buffer,text);
			output(5,7,1,1,1,GLUT_BITMAP_TIMES_ROMAN_24,buffer);
			glPopMatrix();
			button();
			glTranslatef(0,0,-1);
			button();

			glPopMatrix();
		}
		else if(game == true){
			//Game start
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for(int i = 0;i < countLife ;i++){
				drawSphereLife(i);
			}
			
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			setCamera();
			drawRacket(10,10);



			/* Bouncing*/
			if(toTheDown ==1){
				ballVertical+=0.25;
			}
			else if(toTheDown ==2){
				ballVertical-=0.25;
			}

			if(toTheFront == 1){
				ballFront-=0.25;
			}
			else if( toTheFront == 2){
				ballFront+=0.25;
			}

			if(toTheLeft ==1){
				ballHorizontal+=0.25;
			}
			else if(toTheLeft == 2) {
				ballHorizontal-=0.25;
			}
			if(toTheFront == 0){
				ballHorizontal= vertical;
				ballVertical= horizontal;
			}

			if(ballFront>=2 - posCamera && toTheFront!=0){
				toTheFront=1;
			} 
			if(ballHorizontal<=-4){
				toTheLeft=1;
			}
			if(ballHorizontal >=4){
				toTheLeft =2;
			}
			if(ballVertical<=-4){
				toTheDown =1;
			}
			if(ballVertical >=4){
				toTheDown =2;
			}


		/*collision racket and ball*/
			/*Out of the racket*/
			if(ballVertical>=horizontal+3|| ballVertical<=horizontal-3 || ballHorizontal>=vertical+3 ||ballHorizontal<=vertical-3){
				if( toTheFront!=0 && ballVertical>=horizontal+3 && ballFront >= 2 -posCamera){
					printf("lose");
					toTheDown = 0;
					toTheFront = 0;
					toTheLeft = 0;
					ballFront =2 -posCamera;
					ballHorizontal = 0;
					ballVertical =0;
					countLife--;
					//return 0;
				}
				if( toTheFront!=0 && ballVertical<=horizontal-3 && ballFront >= 2 -posCamera){
					printf("lose");
					toTheDown = 0;
					toTheFront = 0;
					toTheLeft = 0;
					ballFront =2 -posCamera;
					ballHorizontal = 0;
					ballVertical =0;
					countLife--;
				}
				if( toTheFront!=0 && ballHorizontal>=vertical+3 && ballFront >= 2 -posCamera){
					printf("lose");
					toTheDown = 0;
					toTheFront = 0;
					toTheLeft = 0;
					ballFront =2 -posCamera;
					ballHorizontal = 0;
					ballVertical =0;
					countLife--;
				}
				if( toTheFront!=0 && ballHorizontal<=vertical-3 && ballFront >= 2 -posCamera){
					printf("lose");
					toTheDown = 0;
					toTheFront = 0;
					toTheLeft = 0;
					ballFront =2 -posCamera;
					ballHorizontal = 0;
					ballVertical =0;
					countLife--;
				}

				if(countLife<= 0){
					printf("Partie Terminée");
					game = false;
				}
			}
			else{
				/*variations bounce racket*/
				if(ballFront>=2-posCamera && ballVertical>= horizontal+1){
					toTheDown = 1;
				}
				if(ballFront>=2-posCamera && ballVertical<= horizontal-1){
					toTheDown = 2;
				}
				if(ballFront>=2-posCamera && ballHorizontal>= vertical+1){
					toTheLeft = 1;
				}
				if(ballFront>=2-posCamera && ballHorizontal<= vertical-1){
					toTheLeft = 2;
				}
			}
			

			
		/*Collision wall and ball*/
			if(ballFront == obstacle[distanceObstacle].x){
				if(obstacle[distanceObstacle].z ==-20 || obstacle[distanceObstacle].y ==-20){
					distanceObstacle++;
				}
				else{
					if(obstacle[distanceObstacle].z < 0 && ballHorizontal <= (obstacle[distanceObstacle].z/2) +3){
						if(toTheFront == 1){
							toTheFront =2;
							distanceObstacle--;
						}
						else{
							toTheFront =1;
						
						}
					}
					if(obstacle[distanceObstacle].z > 0 && ballHorizontal >= (obstacle[distanceObstacle].z/2) -3){
						if(toTheFront == 1){
							toTheFront =2;
							distanceObstacle--;
						}
						else{
							toTheFront =1;
						
						}
					}
					if(obstacle[distanceObstacle].y < 0 && ballVertical <= (obstacle[distanceObstacle].y/2) +3){
						if(toTheFront == 1){
							toTheFront =2;
							distanceObstacle--;
						}
						else{
							toTheFront =1;
						
						}
					}
					if(obstacle[distanceObstacle].y > 0 && ballVertical >= (obstacle[distanceObstacle].y/2) -3){
						if(toTheFront == 1){
							toTheFront =2;
							distanceObstacle--;
						}
						else{
							toTheFront =1;
						
						}
					}
					else{
						distanceObstacle++;
					}
				}
				
			}


			/*Take bonus*/
			//if(ballFront+1 >= bonus[distanceBonus].x && ballFront-1 <= bonus[distanceBonus].x
			// && ballVertical+1 >= bonus[distanceBonus].y && ballVertical <= bonus[distanceBonus].y)
			// && ballHorizontal+1 >= bonus[distanceBonus].z && ballhorizontal <= bonus[distanceBonus].z)
			/*win scenario*/
			if(ballFront < -100){
				
				game=false;
				win = true;
			}
			glPushMatrix();
			glTranslatef(ballFront,ballVertical,ballHorizontal);
			drawSphereOn();
			glPopMatrix();
			/* Initial scenery setup */
			glPushMatrix();
			glTranslatef(0.0,0.0,-0.01);
			glScalef(10.0,10.0,1.0);
			glColor3f(0.0,0.0,0.1);
			//drawSquare();
			glBegin(GL_POINTS);
				glColor3f(1.0,1.0,0.0);
				glVertex3f(0.0,0.0,0.0);
			glEnd();

			glPopMatrix();

			//DRAW BONUS
			drawBonusHeartPosition(textureHeart);
			
			drawCorridor(10,10,texture);
			glPushMatrix();
			glTranslatef(-posCamera,0,0);
			drawSceneLight(); //ball for the light
			glPopMatrix();
		}
		if(game ==false && menu==false){
			/*End of the game*/
			const char * text ="GAME OVER";
			posCamera=1.0;
			glClearColor(0.5,0.5,0.5,0.5);
			drawSceneLight();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();
			setCamera();

			glPushMatrix();
			glRotatef(90,0,0,1);
			glTranslatef(-5,-5,0);
			drawWall(10,10,textureHeart);
			glPopMatrix();
			glPushMatrix();
			if(win == true){
				text =" YOU WIN ";
			}
			char buffer[20];
			strcpy(buffer,text);
			glTranslatef(2,-7.60,5);
			output(5,7,1,0.5,0.5,GLUT_BITMAP_TIMES_ROMAN_24,buffer);

			
			glTranslatef(0,0.1,-1);
			text = "QUITTER";
			strcpy(buffer,text);
			output(5,7,1,1,1,GLUT_BITMAP_TIMES_ROMAN_24,buffer);
			glTranslatef(0,-0.5,1.75);
			button();
			glPopMatrix();
		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}

		/* Animate scenery */
	}
	free_audio(music);
	glDeleteTextures(1, &texture);
	//glDeleteTextures(1, &textureHeart);
	glfwTerminate();
	return 0;
}
//** */