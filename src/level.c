#include "../includes/level.h"
#include "../includes/corridorDrawing.h"

Mur obstacle[50];

void drawObstacle(){
    glColor3f(.5,0.,0.);
    glRotatef(90,0,0,1);
    glTranslatef(-5.0,0.,0.);
    drawWall(10,10);
}

void drawLevel(int rand,float size){
    Mur mur;
    switch(rand%5){
        case 3 : 
            glPushMatrix();
            glTranslatef(0,0,-6);
            mur.x =-rand*size;
            mur.y = 0;
            mur.z =-6;
            obstacle[rand] = mur;
            drawObstacle();
            glPopMatrix();
            break;
        case 4 : 
            glPushMatrix();
            glTranslatef(0,0,6);
            mur.x =-rand*size;
            mur.y = 0;
            mur.z =6;
            obstacle[rand] = mur;
            drawObstacle();
            glPopMatrix();
            break;
        case 1 : 
            glPushMatrix();
            glTranslatef(0,-6,0);
            mur.x =-rand*size;
            mur.y = -6;
            mur.z =0;
            obstacle[rand] = mur;
            drawObstacle();
            glPopMatrix();
            break;
        case 2 : 
            glPushMatrix();
            glTranslatef(0,6,0);
            mur.x =-rand*size;
            mur.y = 6;
            mur.z =0;
            obstacle[rand] = mur;
            drawObstacle();
            glPopMatrix();
            break;

        default:
            mur.x =-rand*size;
            mur.y = -20;
            mur.z =-20;
            obstacle[rand] = mur;
            break;
    }
}