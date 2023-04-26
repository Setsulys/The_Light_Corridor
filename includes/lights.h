#ifndef __LIGHTS_H
#define __LIGHTS_H


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

extern float up;
void glDrawLight(float size);

void drawSceneLight();

#endif