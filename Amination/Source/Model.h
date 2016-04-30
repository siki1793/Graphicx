#ifndef MODEL_H
#define MODEL_H

#include "GL/freeglut.h"
#include "GL/gl.h"
#include "PlyReader.h"
#include "Texture.h"

#include <vector>
// #define PI 3.1415926535897932384626433832795
// static Image *texture[10];
static float radius = 0.25;
static float distance = 0;
static float distanceX = 0, distanceY = 0;
static float Trackball[3] = {0, 0, 0};
static float angle = 0.0f;
static float plyScale;
// static float originX=0.0,originY=0.0,originZ=0.0;
// static float errorY;

class Model{
    public:
        int currentX,currentY;
        // void display();
        void resize(int, int);
        void light();
        void drawLine(float, float, float, float, float, float);
        // void drawPly(PlyReader,int);
        void drawFloor();
        void drawAxes();
        float getDistance();
        float getDistanceX();
        float getDistanceY();
        void setDistance(float);
        void setDistanceX(float);
        void setDistanceY(float);
        void dragRotation (int, int);
        // void updateLight (int);
        static char *bmpFile;
        static PlyReader pl;
        static PlyReader pl1;
};

#endif