#ifndef HEADER_H
#define HEADER_H
#include "headerfile.h"
#endif
void init(void)
{
	glClearColor(0.0,0.0,102.0/255.0,0.0);
	glPointSize(10.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Assignment 1: 2D Rendering");
    init();
    control_p=(POINT *)malloc(clicks_count*sizeof(POINT));
    if(!control_p){
		printf("Allocation failure!");
		exit(EXIT_FAILURE);
		}
    else{
	clicks_count++;
	aux=(POINT *)realloc(control_p,clicks_count*sizeof(POINT));
	if(!aux){
		printf("Reallocation failure!");
		exit(EXIT_FAILURE);
		}
	else{
		control_p=aux;
    		glutMouseFunc(controller::mouseEventHandler);
		}
	}
    glutReshapeFunc (view::reshape);
    glutDisplayFunc(view::renderFunction);
    glutKeyboardFunc(controller::keyboardEventHandler);
    glutMainLoop();
   free(control_p);
    free(aux);
    return 0;
}
