#include <vector>
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <iostream>

static int flag = 1;
static float scale = 1.;
static int special = 0;
static int xangle = 0,yangle = 0, zangle = 0;
static char spin = ' ';
static int light = 0;
static int mState=0;

class Controller{
    private:

    public:

        static void mouseEventHandler(int,int,int,int);
        static void keyboardEventHandler(unsigned char,int,int);
        static void specialKeyEventHandler(int,int,int);
        static void mouseMotion(int,int);
        int getClickCount();
        float getCoordinatesX(int);
        float getCoordinatesY(int);
        void setFlag(int);
        int getFlag();
        int getShape();
        float getScale();
        int getSpecial();
        int getxAngle();
        int getyAngle();
        int getzAngle();
        int getShade();
        char getSpin();
        int getLight();
        int getmAngle();
};


