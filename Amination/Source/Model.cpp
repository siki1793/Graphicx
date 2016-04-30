#include <iostream>
#include <math.h>
#include "Model.h"
#include "Controller.h"
#include "Model.h"
//Light position

// Draws grids
void Model::drawFloor() {
    float coor = 2.0;
    glBegin(GL_QUADS);
        glNormal3d(0,1,0);
        glTexCoord2f(0,0);
        glVertex3f(-coor/2,-coor/2,-coor/2);
        glTexCoord2f(0,5);
        glVertex3f(-coor/2,-coor/2,coor/2);
        glTexCoord2f(5,5);
        glVertex3f(coor/2,-coor/2,coor/2);
        glTexCoord2f(5,0);
        glVertex3f(coor/2,-coor/2,-coor/2);
    glEnd();
}


//Draws X,Y,Z Axes
void Model::drawAxes(){
    glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_LINES);//x axies line segment
    glVertex3f( 0.0, 0.0, 0.0);
    glVertex3f( 0.5, 0.0, 0.0);
   glEnd();
   glPushMatrix();
   glTranslatef(0.5,0.0,0.0);
      glRotatef(90.0,0.0,1.0,0.0);
      glutSolidCone (0.01, 0.02, 3, 4);
    glPopMatrix();
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_LINES);//y axies line segment
    glVertex3f( 0.0, 0.0, 0.0);
    glVertex3f( 0.0, 0.5, 0.0);
   glEnd();
   glPushMatrix();
   glTranslatef(0.0,0.5,0.0);
   glRotatef(-90.0,1.0,0.0,0.0);
      glutSolidCone (0.01, 0.02, 3, 4);
    glPopMatrix();
   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_LINES);//z axies line segment
    glVertex3f( 0.0, 0.0, 0.0);
    glVertex3f( 0.0, 0.0, 0.5);
   glEnd();
   glPushMatrix();
   glTranslatef(0.0,0.0,.5);
      glutSolidCone (0.01, 0.02, 3, 4);
    glPopMatrix();
}

//Getter and Setter functions required to call from other classes
float Model::getDistance(){
    return distance;
}
float Model::getDistanceX(){
    return distanceX;
}
float Model::getDistanceY(){
    return distanceY;
}
void Model::setDistance(float value){
    distance = value;
}
void Model::setDistanceX(float value){
    distanceX = value;
}
void Model::setDistanceY(float value){
    distanceY = value;
}