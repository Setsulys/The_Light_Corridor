#ifndef __CORRIDOR__DRAWING_CM_H
#define __CORRIDOR__DRAWING_CM_H


#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void drawWall(int width, int height);

void drawRacket();

void drawStep(int width,int height);

void drawCorridor(int value);

#endif