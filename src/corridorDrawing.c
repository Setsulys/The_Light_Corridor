#include "corridor.h"

#include <stdio.h>

void glDrawRepere(float length) {
	// dessin du repère
	glBegin(GL_LINES);
		glColor3f(1.,0.,0.);
		glVertex3f(0.,0.,0.);
		glVertex3f(length,0.,0.);
		glColor3f(0.,1.,0.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,length,0.);
		glColor3f(0.,0.,1.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,0.,length);
	glEnd();
}

void glDrawObject() {
	float white[3] = {1.0,1.0,1.0};
	glPointSize(size_pt);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,vertex_coord);
	glNormalPointer(GL_FLOAT,0,normal_coord);
	glDrawArrays(GL_POINTS,0,vertex_number);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void drawWall(int width, int height){
    glBegin(GL_POLYGON);

    glVertex3f(0., 0., 0.);
    glVertex3f(0., width, 0.);
    glVertex3f(height / 4, width, 0.);
    glVertex3f(height / 4, 0., 0.);

    glEnd();
}

void drawRacket(){
    glBegin(GL_LINE_LOOP);

    glVertex3f(0., 0., 0.);
    glVertex3f(0., 1., 0.);
    glVertex3f(1., 1., 0.);
    glVertex3f(1., 0., 0.);

    glEnd();
}

void drawStep(){
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-(width / 2), 0, 0);
	drawWall(width, height);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(width / 2, 0, 0);
	drawWall(width, height);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(width / 2, 0, 0);
	drawWall(width, height);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(width / 2, 0, 0);
	glTranslatef(0, height, 0);
	drawWall(width, height);
	glPopMatrix();
}