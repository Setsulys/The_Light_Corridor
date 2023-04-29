#include "../includes/corridorDrawing.h"
#include "../includes/level.h"
#include "../includes/textures.h"

void drawWall(int width, int height,GLuint texture){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
    glBegin(GL_POLYGON);
	glTexCoord3f(1,1,1);
    glVertex3f(0., 0., 0.);

	glTexCoord3f(1,1,1);
    glVertex3f(0., 0., height);

	glTexCoord3f(1.,1.,1);
    glVertex3f(width, 0., height);
	
	glTexCoord3f(1,1,1);
    glVertex3f(width, 0., 0.);
    glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
}



void drawStep(int width,int height, GLuint texture){
	int w = width/2;
	int h = height/2;
	glColor3f(0.1, 0.1, 0.5);
	glPushMatrix();
	glTranslatef(0, w, 0);
	drawWall(width,height,texture);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -w, 0);
	drawWall(width,height,texture);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -h);
	drawWall(width,height,texture);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, height, -h);
	drawWall(width,height,texture);
	glPopMatrix();
}

void drawCorridor(int value,int size,GLuint texture){
	for(int i = 0 ; i < value; i++){
		//int random = rand()%5;
		glPushMatrix();
		glTranslatef(-i * size, 0, 0);
		drawLevel(i,(float)size,texture);
		drawStep(size, size, texture);
		glPopMatrix();
		
	}
}