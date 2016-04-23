/*
Please read the Readme file and try running code first.
Then look into the code for better understanding.
*/
#include "GL/freeglut.h"
#include "GL/gl.h"
#include "Controller.h"
#include "View.h"
#include "Model.h"

int SCREEN_WIDTH=700;
int SCREEN_HEIGHT=700;

void init();
//void glui_work(int);
PlyReader View::pl;

int main(int argc, char** argv)
{
    View::pl.ReadFile();

    //GLUT initializations
    glutInit(&argc, argv);
    init();

    //Mouse event controller
    glutMouseFunc(Controller::mouseEventHandler);
    glutMotionFunc (Controller::mouseMotion);

    //Keyboard Event Controller
    glutKeyboardFunc(Controller::keyboardEventHandler);
    glutSpecialFunc(Controller::specialKeyEventHandler);

    //Display function
    glutReshapeFunc(View::reshape);
    glutDisplayFunc(View::renderFunction);

    glutMainLoop();

    return 0;
}
void init(){
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    glutInitWindowPosition(100,100);
    int main_window =  glutCreateWindow("Assignment 2: 3D Rendering");
}
