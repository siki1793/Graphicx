#include "Controller.h"
#include "View.h"
#include <iostream>

View pv;

//Mouse events
void Controller::mouseEventHandler(int button, int state,int x, int y){
    mState = 10;
    //If left mouse button clicked, then store the coordinates in the x and y vectors
    //Also increment clickcount
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
        mState = GLUT_LEFT_BUTTON;
        pv.currentX = x;
        pv.currentY = y;
        std::cout<<"on clicked x:: "<<pv.currentX<<" y:: "<<pv.currentY<<std::endl;
    }

    //If right button is clicked clear or set all values to the default values
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		flag = 1;
        pv.setDistance(0.0);
        pv.setDistanceX(0.0);
        pv.setDistanceY(0.0);
        scale = 1.0;
        special = 0;
        xangle = 0;
        yangle = 0;
        zangle = 0;
        light = 0;
	}
}

//mouse motion events
void Controller::mouseMotion (int x, int y) {

    if (mState == GLUT_LEFT_BUTTON) {
        pv.dragRotation (x, y);
    }
}

//Keyboard events
void Controller::keyboardEventHandler(unsigned char key, int x, int y){
    //
   if(key == 'x'){
        spin = 'x';
        xangle = xangle + 15;
    }
    else if(key == 'y'){
        spin = 'y';
        yangle = yangle + 15;
    }
    else if(key == 'z'){
        spin = 'z';
        zangle = zangle + 15;
    }
    else if(key == 'X'){
        spin = 'X';
        xangle = xangle - 15;
    }
    else if(key == 'Y'){
        spin = 'Y';
        yangle = yangle - 15;
    }
    else if(key == 'Z'){
        spin = 'Z';
        zangle = zangle - 15;
    }
    std::cout<<"Rotate by"<<spin<<" x angle "<<xangle<<" y angle "<<yangle<<" z angle "<<zangle<<std::endl;
    switch (key) {
            // scale by 1.2 factor.
          case '+':
            scale = scale * 1.2;
          break;
          case '-':
          scale = scale / (float)1.2;
          break;
          case 'c'://camera zooming by 0.3 moves camera in z axis
            pv.setCameraZ(pv.getCameraZ()+0.3);
          break;
          case 'C':
          pv.setCameraZ(pv.getCameraZ()-0.3);
          break;
         case 27:  /*  Escape Key  */
            exit(0);
         break;
         }

}
//Special keys event
void Controller::specialKeyEventHandler(int key,int x,int y){
    //Translation depends on arrow keys buttons.
    //Seeting the special flag according to the button pressed.
    //Also setting the distances in view to X and Y.
    if(key == GLUT_KEY_UP){
        special = 1;
        pv.setDistanceY(pv.getDistanceY() + pv.getDistance());
    }
    else if(key == GLUT_KEY_DOWN){
        special = 2;
        pv.setDistanceY(pv.getDistanceY() - pv.getDistance());
    }
    else if(key == GLUT_KEY_RIGHT){
        special = 3;
        pv.setDistanceX(pv.getDistanceX() + pv.getDistance());
    }
    else if(key == GLUT_KEY_LEFT){
        special = 4;
        pv.setDistanceX(pv.getDistanceX() - pv.getDistance());
    }
}

//Getters and Setters to use from other classes.
void Controller::setFlag(int value){
    flag = value;
}
int Controller::getFlag(){
    return flag;
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
char Controller::getSpin(){
    return spin;
}
int Controller::getLight(){
    return light;
}
