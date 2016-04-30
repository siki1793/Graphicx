#include <vector>
#include "GL/glut.h"
#include "GL/gl.h"


static float scale = 1;
static int status = 0;
static int xangle = 0,yangle = 0, zangle = 0;
static char spin = ' ';


class Controller{
    private:
        float memRot[3];
    public:
        static void mouseEventHandler(int, int, int, int);
        static void mouseMotion (int, int);
        static void keyboardEventHandler(unsigned char,int,int);
        static void specialKeyEventHandler(int,int,int);
        static void click_scene(int, int);
        static void drag_scene(int, int);
        float getScale();
        char getSpin();
};


