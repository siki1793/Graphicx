#include "Controller.h"
#include "View.h"

View a1v;

//Mouse events handling
void Controller::mouseEventHandler(int button, int state,int x, int y){

    mState = 10;
    if (button == 3) {
        scale = scale * 1.2;
    }

    if (button == 4) {
        scale = scale / (float)1.2;
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
        mState = GLUT_LEFT_BUTTON;
        a1v.currentLoc[0] = x;
        a1v.currentLoc[1] = y;
        if (clickCount < 2) {
            coordinatesVectorX.push_back(((x-325)/(float)650)*2);
            coordinatesVectorY.push_back(((325-y)/(float)650)*2);
            clickCount++;
        }
    }

    //If right button is clicked clear or set all values to the default values
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		clickCount = 0;
		coordinatesVectorX.clear();
		coordinatesVectorY.clear();
		flag = 1;
        a1v.setDistance(0.0);
        a1v.setDistanceX(0.0);
        a1v.setDistanceY(0.0);
        scale = 1.0;
        special = 0;
        shape = 0;
        xangle = 0;
        yangle = 0;
        zangle = 0;
        shade = 1;
        light = 0;
        mangle = 0;
	}
}

void Controller::mouseMotion (int x, int y) {

    if (mState == GLUT_LEFT_BUTTON) {
        a1v.updateRotation (x, y);
    }
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
    }
}

void Controller::specialKeyEventHandler(int key,int x,int y){

    if(key == GLUT_KEY_UP){
        a1v.setDistanceY(a1v.getDistanceY() + a1v.getDistance());
    }
    else if(key == GLUT_KEY_DOWN){
        a1v.setDistanceY(a1v.getDistanceY() - a1v.getDistance());
    }
    else if(key == GLUT_KEY_RIGHT){
        a1v.setDistanceX(a1v.getDistanceX() + a1v.getDistance());
    }
    else if(key == GLUT_KEY_LEFT){
        a1v.setDistanceX(a1v.getDistanceX() - a1v.getDistance());
    }
}

//Getters and Setters to use from other classes.
int Controller::getClickCount(){
    return clickCount;
}
float Controller::getCoordinatesX(int pos){
    return coordinatesVectorX[pos];
}
float Controller::getCoordinatesY(int pos){
    return coordinatesVectorY[pos];
}
void Controller::setFlag(int value){
    flag = value;
}
int Controller::getFlag(){
    return flag;
}
int Controller::getShape(){
    return shape;
}
float Controller::getScale(){
    return scale;
}
int Controller::getSpecial(){
    return special;
}
int Controller::getxAngle(){
    return xangle;
}
int Controller::getyAngle(){
    return yangle;
}
int Controller::getzAngle(){
    return zangle;
}
int Controller::getShade(){
    return shade;
}
char Controller::getSpin(){
    return spin;
}
int Controller::getLight(){
    return light;
}
int Controller::getmAngle(){
    return mangle;
}
