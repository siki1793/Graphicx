#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

int window_h = 600;
int window_w = 800;
int window_x = 350;
int window_y = 150;

void init(void)
{
   glClearColor(0.0,0.0,0.0,0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(window_x,window_y);
   glutInitWindowSize(window_w,window_h);
   glutCreateWindow ("points");

}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    init();

}
