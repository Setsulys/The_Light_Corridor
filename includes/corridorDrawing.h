#ifndef __CORRIDOR__DRAWING_CM_H
#define __CORRIDOR__DRAWING_CM_H


#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <GL/glu.h>
#include <GL/gl.h>

void drawWall(/*int width, int height*/);

void drawRacket();

void drawStep(int width,int height);

#endif