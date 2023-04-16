#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <GL/glu.h>
#include <GL/gl.h>

#include "../includes/corridor.h"
#include "../includes/corridorDrawing.h"

int main(int argc, char const *argv[])
{
    sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	sf::Window window(sf::VideoMode(800, 800), "The LightCorridor", sf::Style::Default, settings);
	
	window.setVerticalSyncEnabled(true); // call it once, after creating the window
	
    window.setActive(true);
    /* code */
    return 0;
}
