#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "../includes/corridor.h"
#include "../includes/corridorDrawing.h"
#include "../includes/create_obj_pt.h"

/* variables globales pour la gestion de la caméra */
float profondeur = 3;
float latitude = 0.0;
float longitude = M_PI/2.;

float obj_rot = 0.0;
unsigned int size_pt = 5;
int flag_anim = 0;
int flag_run = 1;


/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "The light corridor";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Virtual windows space */
// Space is defined in interval -10 and 10 on x and y axes
static const float GL_VIEW_SIZE = 10.;


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

	if( aspectRatio > 1)
	{
		gluOrtho2D(
		-GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	}
	else
	{
		gluOrtho2D(
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
		-GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
	}
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
			case GLFW_KEY_L :
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				break;
			case GLFW_KEY_P :
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				break;
			default: fprintf(stdout,"Touche non gérée\n");
		}
	}
}

int main(int argc, char** argv) 
{
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

	glPointSize(4.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		/* RENDER HERE */
		drawRacket();
		//drawWall(/*WINDOW_WIDTH,WINDOW_HEIGHT*/);
		drawStep(-(GL_VIEW_SIZE / 2),-(GL_VIEW_SIZE / 2));

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
	}

	glfwTerminate();
	return 0;
}

/*********************************************************/
/* fonction de changement de dimension de la fenetre     */
/* paramètres :                                          */
/* - width : largeur (x) de la zone de visualisation     */
/* - height : hauteur (y) de la zone de visualisation    */
static void reshapeFunc(int width,int height) {
	GLfloat  h = (GLfloat) width / (GLfloat) height ;
	
	/* dimension de l'écran GL */
	glViewport(0, 0, (GLint)width, (GLint)height);
	/* construction de la matrice de projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* définition de la camera */
	gluPerspective( 60.0, h, 0.01, 10.0 );			// Angle de vue, rapport largeur/hauteur, near, far

	/* Retour a la pile de matrice Modelview
			et effacement de celle-ci */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*********************************************************/
/* fonction associée aux interruptions clavier           */
/* paramètres :                                          */
/* - kEvt : evenement clavier                            */
static void kbdFunc(sf::Event kEvt) {
	switch(kEvt.key.code) {
		/* sortie du programme si utilisation de la touches ESC */
		case sf::Keyboard::Escape :
			flag_run = 0;
			break;
		case sf::Keyboard::F : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			break;
		case sf::Keyboard::P : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			break;
		// case sf::Keyboard::S : 
		// 	flag_anim = 1-flag_anim;
		// 	break;
		// case sf::Keyboard::Up :
		// 	if (latitude>STEP_ANGLE) latitude -= STEP_ANGLE;
		// 	break;
		// case sf::Keyboard::Down :
		// 	if(latitude<M_PI-STEP_ANGLE) latitude += STEP_ANGLE;
		// 	break;
		// case sf::Keyboard::Left :
		// 	longitude -= STEP_ANGLE;
		// 	break;
		// case sf::Keyboard::Right :
		// 	longitude += STEP_ANGLE;
		// 	break;
		// case sf::Keyboard::PageUp :
		// case sf::Keyboard::Numpad9 :
		// 	profondeur += STEP_PROF;
		// 	break;
		// case sf::Keyboard::PageDown :
		// case sf::Keyboard::Numpad3 :
		// 	if (profondeur>0.1+STEP_PROF) profondeur -= STEP_PROF;
		// 	break;
		default:
			printf("Key %d \n",kEvt.key.code);
			break;
	}
}

void init() {
	profondeur = 3;
	latitude = M_PI/2.0;
	longitude = 0.0;

	obj_rot = 0.0;
	size_pt = 5;
	flag_anim = 0;
	flag_run = 1;

	/* INITIALISATION DES PARAMETRES GL */
	/* couleur du fond (gris sombre) */
	glClearColor(0.3,0.3,0.3,0.0);
	/* activation du ZBuffer */
	glEnable( GL_DEPTH_TEST);

	/* lissage des couleurs sur les facettes */
	glShadeModel(GL_SMOOTH);

	/* INITIALISATION DE LA SCENE */
	createCoordinates(&size_pt);
}

// int main() {
// 	sf::ContextSettings settings;
// 	settings.depthBits = 24;
// 	settings.stencilBits = 8;
// 	settings.antialiasingLevel = 4;
// 	settings.majorVersion = 3;
// 	settings.minorVersion = 0;

// 	sf::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "OpenGL", sf::Style::Default, settings);
	
// 	window.setVerticalSyncEnabled(true); // call it once, after creating the window
	
//     window.setActive(true);

// 	init();
// 	reshapeFunc(800,800);

//     while (flag_run)
//     {
//         // handle events
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 // end the program
//                 flag_run = 0;
//             }
//             else if (event.type == sf::Event::Resized)
//             {
//             	// adjust the viewport when the window is resized
// 				reshapeFunc(event.size.width,event.size.height);
//             }
// 			else if (event.type == sf::Event::KeyPressed) 
// 			{
// 				kbdFunc(event);
// 			}
//         }

// 		// // If animation is running update scene
// 		// if (flag_anim) {
// 		// 	obj_rot+=STEP_ANGLE;
// 		// }
//         // draw...
// 		drawStep(-(GL_VIEW_SIZE / 2),-(GL_VIEW_SIZE / 2));

//         // end the current frame (internally swaps the front and back buffers)
//         window.display();
//     }



// 	return 0;
// }