#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <stdbool.h>
#include <time.h>

#include "../includes/3D_tools.h"
#include "../includes/draw_scene.h"
#include "../includes/corridorDrawing.h"
#include "../includes/level.h"
#include "../includes/lights.h"
#include "../includes/objects.h"
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


/*Ball bounce values*/

float ballVertical =0;
float ballHorizontal =0;
float ballFront =2;

int toTheLeft =0;
int toTheFront = 0;
int toTheDown = 0;

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_A :
			case GLFW_KEY_ESCAPE :
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
			// case GLFW_KEY_L :
			// 	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			// 	break;
			// case GLFW_KEY_P :
			// 	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			// 	break;
			// case GLFW_KEY_R :
			// 	flag_animate_rot_arm = 1-flag_animate_rot_arm;
			// 	break;
			// case GLFW_KEY_T :
			// 	flag_animate_rot_scale = 1-flag_animate_rot_scale;
			// 	break;
			case GLFW_KEY_KP_9 :
				if(dist_zoom<100.0f) dist_zoom*=1.1;
				printf("Zoom is %f\n",dist_zoom);
				break;
			case GLFW_KEY_KP_3 :
				if(dist_zoom>1.0f) dist_zoom*=0.9;
				printf("Zoom is %f\n",dist_zoom);
				break;
			case GLFW_KEY_UP :
				if (phy>2) phy -= 2;
				printf("Phy %f\n",phy);
				break;
			case GLFW_KEY_DOWN :
				if (phy<=88.) phy += 2;
				printf("Phy %f\n",phy);
				break;
			case GLFW_KEY_LEFT :
				theta -= 5;
				break;
			case GLFW_KEY_RIGHT :
				theta += 5;
				break;
			//changement lumiere
			// case GLFW_KEY_P :
			// 	up+=0.5;
			// 	break;
			// case GLFW_KEY_M :
			// 	up-=0.5;
			// 	break;

			//mouvement de raquette	
			case GLFW_KEY_KP_8 :
				if(vertical < 3){
					vertical += 0.5;
				}
				break;
			case GLFW_KEY_KP_4 :
				if(horizontal > -3){
					horizontal -= 0.5;
				}
				break;
			case GLFW_KEY_KP_5 :
				if(vertical > -3){
					vertical -= 0.5;
				}
				break;
			case GLFW_KEY_KP_6 :
				if(horizontal < 3  ){
					horizontal += 0.5;
				}
				break;
			case GLFW_KEY_SPACE :
				posCamera+=10;
				break;
			case GLFW_KEY_LEFT_CONTROL:
				if(posCamera >=2){
					posCamera-=10;
				}
				break;
			case GLFW_KEY_ENTER : 
				toTheFront =1;
				break;
			default: fprintf(stdout,"Touche non gérée (%d)\n",key);
		}
	}
}




int main(int argc, char** argv)
{
	srand(time(NULL));
	/* GLFW initialisation */
	GLFWwindow* window;
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

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);




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
	glBindTexture(GL_TEXTURE_2D,0);
	glTexCoord3f(width,height,0);
	
	int distanceObstacle=0;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();
		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.5,0.5,0.5,0.5);
		//glClearColor(0.,0.,0.,0.);
		drawSceneLight(); // No ball for the light
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//drawFrame();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();
		drawRacket(10,10);



		/* Bouncing*/
			if(toTheDown ==1){
				ballVertical++;
			}
			else if(toTheDown ==2){
				ballVertical--;
			}

			if(toTheFront == 1){
				ballFront--;
			}
			else if( toTheFront == 2){
				ballFront++;
			}

			if(toTheLeft ==1){
				ballHorizontal++;
			}
			else if(toTheLeft == 2) {
				ballHorizontal--;
			}
			if(toTheFront == 0){
				ballHorizontal= vertical;
				ballVertical= horizontal;
			}


			if(ballFront==2 && toTheFront!=0){
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



		/*Collision wall and ball*/
			if(ballFront == obstacle[distanceObstacle].x){
				printf("mur %f",obstacle[distanceObstacle].x);
				printf("\nobstacles\n%d et %f et %f\n",distanceObstacle,obstacle[distanceObstacle].z/2.0 ,obstacle[distanceObstacle].y/2.0);
				printf("%f, %f\n",ballHorizontal,ballVertical);
				
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
		drawCorridor(10,10,texture);
		//drawWall(10,10,texture);
		drawSceneLight(); //ball for the light
		/* Scene rendering */

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
	//freeTextures(texture,texturesDatas,size);
	glDeleteTextures(1, &texture);
	glfwTerminate();
	return 0;
}
//** */