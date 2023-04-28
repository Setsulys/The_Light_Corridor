#include "../includes/lights.h"
#include "../includes/draw_scene.h"
#include "../includes/3D_tools.h"


float up =1.5;

void glDrawLight(float size) {
    gluSphere(gluNewQuadric(),size,NB_SEG_CIRCLE,NB_SEG_CIRCLE);
}


void drawSceneLight(){
    // LIGHT POSITION
    float position[4] = {40.0,0.0,5.0,up};
    /*
        * position[0] = axe camera
        * position[1] = horizontal
        * position[2] = vertical
        * position[3] = angle par raport a la camera si 0 noir et blanc
        */
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glDrawLight(1);
    glPopMatrix();


    GLfloat view[16]; 
    glGetFloatv(GL_MODELVIEW_MATRIX, view); 
    //glUniformMatrix4fv(glGetUniformLocation(my_shader->getGLId(),"view_matrix"),1,GL_FALSE,view);

    float overall_intensity = 3000.0;
    float black[4] = {0.0,0.0,0.0,1.0};
    float spec_intensity[4] = {overall_intensity,0.0,0.0,0.0};
    float intensite[4] = {overall_intensity,overall_intensity,overall_intensity,overall_intensity};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glLightfv(GL_LIGHT0,GL_POSITION,position);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,intensite);
    glLightfv(GL_LIGHT0,GL_SPECULAR,spec_intensity);
    glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,1.0);
    glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,0.0);
    glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,M_PI);
}

void drawSceneLightIntense(){
    // LIGHT POSITION
    float position[4] = {-30.0,0.0,0.0,up};
    /*
        * position[0] = axe camera
        * position[1] = horizontal
        * position[2] = vertical
        * position[3] = angle par raport a la camera si 0 noir et blanc
        */
    glPushMatrix();
        glTranslatef(position[0],position[1],position[2]);
        glDrawLight(1);
    glPopMatrix();


    GLfloat view[16]; 
    glGetFloatv(GL_MODELVIEW_MATRIX, view); 
    //glUniformMatrix4fv(glGetUniformLocation(my_shader->getGLId(),"view_matrix"),1,GL_FALSE,view);

    float overall_intensity = 1500.0;
    float black[4] = {0.0,0.0,0.0,1.0};
    float spec_intensity[4] = {overall_intensity,0.0,0.0,0.0};
    float intensite[4] = {overall_intensity,overall_intensity,overall_intensity,overall_intensity};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glLightfv(GL_LIGHT0,GL_POSITION,position);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,intensite);
    glLightfv(GL_LIGHT0,GL_SPECULAR,spec_intensity);
    glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,1.0);
    glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,0.0);
    glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,M_PI);
}