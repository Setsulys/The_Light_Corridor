#ifndef __CORRIDOR_CM_H
#define __CORRIDOR_CM_H
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


void onError(int error, const char* description);

void onWindowResized(GLFWwindow* window, int width, int height);

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods);

void output(int x, int y, float r, float g, float b, void * font, char *string);

#endif