#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <stdio.h>

// void glDrawRepere(float length) {
// 	// dessin du repère
// 	glBegin(GL_LINES);
// 		glColor3f(1.,0.,0.);
// 		glVertex3f(0.,0.,0.);
// 		glVertex3f(length,0.,0.);
// 		glColor3f(0.,1.,0.);
// 		glVertex3i(0.,0.,0.);
// 		glVertex3i(0.,length,0.);
// 		glColor3f(0.,0.,1.);
// 		glVertex3i(0.,0.,0.);
// 		glVertex3i(0.,0.,length);
// 	glEnd();
// }

// void glDrawObject() {
// 	float white[3] = {1.0,1.0,1.0};
// 	glPointSize(size_pt);
// 	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white);
// 	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1.0);
// 	glEnableClientState(GL_VERTEX_ARRAY);
// 	glEnableClientState(GL_NORMAL_ARRAY);
// 	glVertexPointer(3,GL_FLOAT,0,vertex_coord);
// 	glNormalPointer(GL_FLOAT,0,normal_coord);
// 	glDrawArrays(GL_POINTS,0,vertex_number);
// 	glDisableClientState(GL_NORMAL_ARRAY);
// 	glDisableClientState(GL_VERTEX_ARRAY);
// }
static const float GL_VIEW_SIZE = 10.;

void drawWall(int width, int height){
    glBegin(GL_POLYGON);
	glColor3f(1., 1., 1.);
    
	glVertex3f(0., 0., 0.);
    glVertex3f(0., height, 0.);
    glVertex3f(width, height, 0.);
    glVertex3f(width, 0., 0.);

    glEnd();
}

void drawRacket(){
    glBegin(GL_LINE_LOOP);
	glColor3f(1., 1., 0.);
    glVertex3f(0., 0., 0.);
    glVertex3f(0., 1., 0.);
    glVertex3f(1., 1., 0.);
    glVertex3f(1., 0., 0.);

    glEnd();
}

void drawStep(int width,int height){
	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glTranslatef(width, height, 0);
	drawWall((int) GL_VIEW_SIZE / 3, -height * 2);
	glPopMatrix();

	// glPushMatrix();
	// glRotatef(80, 0, 1, 0);
	// glTranslatef(width / 2, 0, 0);
	// drawWall(width, height);
	// glPopMatrix();

	// glPushMatrix();
	// glRotatef(80, 0, 0, 1);
	// glRotatef(80, 1, 0, 0);
	// glTranslatef(width / 2, 0, 0);
	// drawWall(width, height);
	// glPopMatrix();

	// glPushMatrix();
	// glRotatef(80, 0, 0, 1);
	// glRotatef(80, 1, 0, 0);
	// glTranslatef(width / 2, 0, 0);
	// glTranslatef(0, height, 0);
	// drawWall(width, height);
	// glPopMatrix();
}