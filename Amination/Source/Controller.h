#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include "GL/glut.h"
#include "GL/gl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


static float scale = 1;
static int status = 0;
static int xangle = 0,yangle = 0, zangle = 0;
static char spin = ' ';


class Controller{
    private:
        float memRot[3];
    public:
        Controller(int,char**);
        static void render_callback();
        static void reshape_callback(int,int);
        static void mouse_callback(int, int, int, int);
        static void motion_callback(int, int);
        static void keyboard_callback(unsigned char,int,int);
        static void specialKey_callback(int,int,int);
        static void idle_callback();
        void idleFunc();
        void display();
        void resize(int ,int );
        void mouseEventHandler(int, int, int, int);
        void mouseMotion (int, int);
        void keyboardEventHandler(unsigned char,int,int);
        void specialKeyEventHandler(int,int,int);
        void click_scene(int, int);
        void drag_scene(int, int);
        void updateLight (int);
        void light();
        float getScale();
        char getSpin();
};


#endif