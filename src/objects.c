#include "../includes/objects.h"
#include "../includes/3D_tools.h"
#include "../includes/lights.h"

float vertical = 0;
float horizontal = 0;

Bonus bonu[50];

void drawSphereOn(){
	float alpha = 0;
	float x =  cos(alpha);
	float y =  sin(alpha);
	glPushMatrix();
	glTranslatef(x,y,5);
	glColor3f(0.5,0.5,0.5);
	//gluSphere(gluNewQuadric(),1,NB_SEG_CIRCLE,NB_SEG_CIRCLE);
	drawSceneLightIntense();
	glPopMatrix();
}

void drawRacket(int width, int height){
	float w = width/3;
	float h = height/3;
	glPushMatrix();
	glTranslatef(-posCamera,horizontal,vertical);
	glLineWidth(10);
	glTranslatef(5,-1.5,3.5);
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

void drawSphereLife(float value){
	float alpha = 0;
	float x =  cos(alpha);
	float y =  sin(alpha);
	glPushMatrix();
	glTranslatef(x+7-posCamera,y-3+value/3,8);
	glColor3f(0.5,0.5,0.5);
	gluSphere(gluNewQuadric(),0.2,NB_SEG_CIRCLE,NB_SEG_CIRCLE);
	//drawSceneLightIntense();
	glPopMatrix();
}

void drawCube(GLuint texture){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
    glBegin(GL_POLYGON);

    //face in xy plane 
    glTexCoord2f(0,0);
	glVertex3f(0, 0 ,0 );
	glTexCoord2f(0,1);
    glVertex3f(0.5, 0, 0);
	glTexCoord2f(1,1);
    glVertex3f(0.5, 0.5, 0);
	glTexCoord2f(1,0);
    glVertex3f(0, 0.5, 0);

    //face in yz plane
	glTexCoord2f(0,0);
    glVertex3f(0, 0, 0);
	glTexCoord2f(0,1);
    glVertex3f(0, 0, 0.5);
	glTexCoord2f(1,1);
    glVertex3f(0, 0.5, 0);
	glTexCoord2f(1,0);
    glVertex3f(0, 0.5, 0.5);

    //face in zx plance
	glTexCoord2f(0,0);
    glVertex3f(0, 0, 0);
	glTexCoord2f(0,1);
    glVertex3f(0, 0, 0.5);
	glTexCoord2f(1,1);
    glVertex3f(0.5, 0, 0.5);
	glTexCoord2f(1,0);
    glVertex3f(0.5, 0, 0);

    //|| to xy plane.
	glTexCoord2f(0,0);
    glVertex3f(0, 0, 0.5);
	glTexCoord2f(0,1);
    glVertex3f(0.5, 0, 0.5);
	glTexCoord2f(1,1);
    glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1,0);
    glVertex3f(0, 0.5, 0.5);

    //|| to yz plane
	glTexCoord2f(0,0);
    glVertex3f(0, 0, 0.5);
	glTexCoord2f(0,1);
    glVertex3f(0.5, 0, 0.5);
	glTexCoord2f(1,1);
    glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1,0);
    glVertex3f(0, 0.5, 0.5);

    //|| to zx plane
	glTexCoord2f(0,0);
    glVertex3f(0, 0.5, 0);
	glTexCoord2f(0,1);
    glVertex3f(0, 0.5, 0.5);
	glTexCoord2f(1,1);
    glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1,0);
    glVertex3f(0.5, 0.5, 0);

    glEnd();
	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);
}


void drawBonus(GLuint texture){
	glPushMatrix();
    drawCube(texture);
	glPopMatrix();
}

void drawBonusHeartPosition(GLuint texture){
	//Bonus bon;
	glPushMatrix();
	glTranslatef(-10,1,4);
	glRotatef(90,0,1,0);
	// bon.type =1;
	// bon.x = ;
	// bon.y = ;
	// bon.z = ;
	// bonu[0] = bon;
	drawBonus(texture);
	glPopMatrix();
}


void drawBonusStickPosition(GLuint texture){
	//Bonus bon;
	glPushMatrix();
	glTranslatef(-10,1,4);
	glRotatef(90,0,1,0);
	// bon.type =2;
	// bon.x = ;
	// bon.y = ;
	// bon.z = ;
	// bonu[0] = bon;
	drawBonus(texture);
	glPopMatrix();
}
