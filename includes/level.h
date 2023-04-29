#ifndef __LEVEL_H
#define __LEVEL_H

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct{
    float x;
    float y;
    float z;
} Mur;

extern Mur obstacle[50];

void drawObstacle();

void drawLevel(int rand,float size);
#endif