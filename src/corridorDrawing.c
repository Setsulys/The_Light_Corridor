#include "../includes/corridorDrawing.h"
#include "../includes/level.h"

void drawWall(int width, int height){
    glBegin(GL_POLYGON);
	
    glVertex3f(0., 0., 0.);
    glVertex3f(0., 0., height);
    glVertex3f(width, 0., height);
    glVertex3f(width, 0., 0.);
    glEnd();
	
}



void drawStep(int width,int height){
	int w = width/2;
	int h = height/2;
	glColor3f(0.1, 0.1, 0.5);
	glPushMatrix();
	glTranslatef(0, w, 0);
	drawWall(width,height);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -w, 0);
	drawWall(width,height);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -h);
	drawWall(width,height);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, height, -h);
	drawWall(width,height);
	glPopMatrix();
}

void drawCorridor(int value,int size){
	for(int i = 0 ; i < value; i++){
		//int random = rand()%5;
		glPushMatrix();
		glTranslatef(-i * size, 0, 0);
		drawLevel(i);
		drawStep(size, size);
		glPopMatrix();
		
	}
}