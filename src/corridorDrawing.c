#include "../includes/corridorDrawing.h"
#include "../includes/level.h"
static const float GL_VIEW_SIZE = 10.;

void drawWall(int width, int height){
    glBegin(GL_POLYGON);
    glVertex3f(0., 0., 0.);
    glVertex3f(0., 0., height);
    glVertex3f(width, 0., height);
    glVertex3f(width, 0., 0.);
    glEnd();
	
}

void drawRacket(){
    glBegin(GL_LINE_LOOP);
	glColor3f(1., 0., 0.);
    glVertex3f(0., 0., 0.);
    glVertex3f(0., 0., 2.);
    glVertex3f(0., 2., 2.);
    glVertex3f(0., 2., 0.);

    glEnd();
}

void drawStep(int width,int height){
	glColor3f(0.1, 0.1, 0.5);
	glPushMatrix();
	//glRotatef(45, 0, 1, 0);
	glTranslatef(0, 5, 0);
	drawWall(width,height);
	glPopMatrix();

	glPushMatrix();
	//glRotatef(45, 0, 1, 0);
	glTranslatef(0, -5, 0);
	drawWall(width,height);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, -5);
	drawWall(width,height);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
		glTranslatef(0, 10, -5);
	drawWall(width,height);
	glPopMatrix();
}

void drawCorridor(int value){
	for(int i = 0 ; i < value; i++){
		int random = rand()%5;
		glPushMatrix();
		glTranslatef(-i * 10, 0, 0);
		drawLevel(3);
		drawStep(10, 10);
		glPopMatrix();
		
	}
}