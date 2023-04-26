#include "../includes/objects.h"
#include "../includes/3D_tools.h"

float vertical = 0;
float horizontal = 0;

void drawSphereOn(){
	float alpha = 0;
	float x =  cos(alpha);
	float y =  sin(alpha);
	glPushMatrix();
	glTranslatef(x,y,5);
	glColor3f(0.5,0.5,0.5);
	gluSphere(gluNewQuadric(),1,NB_SEG_CIRCLE,NB_SEG_CIRCLE);
	glPopMatrix();
}

void drawRacket(int width, int height){
	float w = width/4;
	float h = height/4;
	
	glPushMatrix();
	glTranslatef(0,horizontal,vertical);
	glLineWidth(10);
	glTranslatef(5,-1,4);
    glBegin(GL_LINE_LOOP);
	glColor3f(1., 1., 1.);
    glVertex3f(0., 0., 0.);
    glVertex3f(0., 0., h);
    glVertex3f(0., w, h);
    glVertex3f(0., w, 0.);
    glEnd();
	glLineWidth(1.0);
	glPopMatrix();
}