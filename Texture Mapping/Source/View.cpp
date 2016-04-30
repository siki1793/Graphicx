#include "View.h"

Model m;


void View::init(int SCREEN_WIDTH,int SCREEN_HEIGHT){
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100,100);
    int main_window =  glutCreateWindow("Assignment 4 : Texture Mapping BY MT2015096 SAIKRISHNA");
}

void View::render()
{
	m.display();
}

void View::reshape(int w,int h)
{
	m.resize(w,h);
}