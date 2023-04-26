#ifndef __CORRIDOR__DRAWING_H
#define __CORRIDOR__DRAWING_H


#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void drawWall(int width, int height);

void drawStep(int width,int height);

void drawCorridor(int value,int size);

#endif