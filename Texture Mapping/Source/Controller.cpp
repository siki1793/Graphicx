#include "Controller.h"
#include "Model.h"
#include "arcball.h"

Model texV;
Controller texC;

//Mouse events handling
void Controller::mouseEventHandler(int button, int state,int x, int y){

    status = 10;
    if (button == 3) {
        scale = scale * 1.2;
    }

    if (button == 4) {
        scale = scale / (float)1.2;
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
        status = GLUT_LEFT_BUTTON;
        texC.click_scene(x,y);
    }

    //If right button is clicked clear or set all values to the default values
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        texV.setDistance(0.0);
        texV.setDistanceX(0.0);
        texV.setDistanceY(0.0);
        scale = 1.0;
	}
    glutPostRedisplay();
}

void Controller::mouseMotion (int x, int y) {

    if (status == GLUT_LEFT_BUTTON) {
        texC.drag_scene(x,y);
        x=texV.currentX;
        y=texV.currentY;
    }
    glutPostRedisplay();
}

void Controller::click_scene(int x, int y)
{
    arcball_start(-x,y);
}


void Controller::drag_scene(int x, int y)
{
    arcball_move(-x,y);
}

void Controller::keyboardEventHandler(unsigned char key, int x, int y){

    if(key == 'x') {
        spin = 'x';
        xangle = xangle + 15;
    } else if(key == 'y') {
        spin = 'y';
        yangle = yangle + 15;
    } else if(key == 'z') {
        spin = 'z';
        zangle = zangle + 15;
    } else if(key == '1') {
        texV.updateLight(0);
    } else if(key == '2') {
        texV.updateLight(1);
    } else if(key == '3') {
        texV.updateLight(2);
    } else if(key == '4') {
        texV.updateLight(3);
    }
    else if(key==27)
    {
        exit(0);
    }
    glutPostRedisplay();
}

void Controller::specialKeyEventHandler(int key,int x,int y){

    if(key == GLUT_KEY_UP){
        texV.setDistanceY(texV.getDistanceY() + 0.1);
    }
    else if(key == GLUT_KEY_DOWN){
        texV.setDistanceY(texV.getDistanceY() - 0.1);
    }
    else if(key == GLUT_KEY_RIGHT){
        texV.setDistanceX(texV.getDistanceX() + 0.1);
    }
    else if(key == GLUT_KEY_LEFT){
        texV.setDistanceX(texV.getDistanceX() - 0.1);
    }
    glutPostRedisplay();
}

//Getters and Setters to use from other classes.
float Controller::getScale(){
    return scale;
}

char Controller::getSpin(){
    return spin;
}