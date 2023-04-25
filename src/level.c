#include "../includes/level.h"
#include "../includes/corridorDrawing.h"


void drawObstacle(){
    glColor3f(.5,0.,0.);
    glRotatef(90,0,0,1);
    glTranslatef(-5.0,0.,0.);
    drawWall(10,10);
}

void drawLevel(int rand){
    switch(rand){
        case 1 : 
            glPushMatrix();
            glTranslatef(0,0,-6);
            drawObstacle();
            glPopMatrix();
            break;
        case 2 : 
            glPushMatrix();
            glTranslatef(0,0,6);
            drawObstacle();
            glPopMatrix();
            break;
        case 3 : 
            glPushMatrix();
            glTranslatef(0,-6,0);
            drawObstacle();
            glPopMatrix();
            break;
        case 4 : 
            glPushMatrix();
            glTranslatef(0,6,0);
            drawObstacle();
            glPopMatrix();
            break;

        default:
            break;
    }
}