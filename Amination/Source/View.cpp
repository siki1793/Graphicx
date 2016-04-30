#include "View.h"
#include <iostream>
#include <stdio.h>
// View m;

const vec eye( 0.5f, 1.3f, -2.0f );
const vec centre( 0.0f, 0.0f, 0.0f );
const vec up( 0.0f, 1.0f, 0.0f );
const float SPHERE_RADIUS = 15.0f;


void View::init(int SCREEN_WIDTH,int SCREEN_HEIGHT){
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100,100);
    int main_window =  glutCreateWindow("Assignment 5 : Scene Graph BY MT2015096 SAIKRISHNA");
}

void View::resize(int w, int h) {

    const vec eye( .5f, 0.5f, -2.0f );
    const vec centre( 0.0f, 0.0f, 0.0f );
    const vec up( 0.0f, 1.0f, 0.0f );

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 70.0f, (float) w / (float) h, 1.0f, 100.0f );
    gluLookAt(
        eye.x, eye.y, eye.z,
        centre.x, centre.y, centre.z,
        up.x, up.y, up.z );

        printf("light    %f    %f     %f\n", eye.x, eye.y, eye.z);

    arcball_setzoom( SPHERE_RADIUS, eye, up );
}