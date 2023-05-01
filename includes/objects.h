#ifndef __OBJECTS_H
#define __OBJECTS_H



#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

extern float vertical;
extern float horizontal;

typedef struct{
    float x;
    float y;
    float z;
    int type;
} Bonus;

extern Bonus bonu[50];

void drawSphereOn();

void drawRacket(int width, int height);

void drawSphereLife(float value);

void drawCube(GLuint texture);

void drawBonus(GLuint texture);

void drawBonusHeartPosition(GLuint texture);

void drawBonusStickPosition(GLuint texture);
#endif