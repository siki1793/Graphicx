#include "GL/freeglut.h"
#include "GL/gl.h"
#include "PlyReader.h"

#include <vector>
#include <math.h>
#define PI 3.1415926535897932384626433832795
static float radius = 0.25;
static float distance = .2;
static float distanceX = 0, distanceY = 0;

class View{
    public:
        int currentX,currentY;
        static void renderFunction();
        static void reshape(int,int);
        void updateCamera();
        void light();
        void drawLine(float,float,float,float,float,float);
        void drawBoundingBox();
        void drawPly();
        void drawAxis();
        void drawPoint(float,float);
        void dragRotation(int,int);
        float getDistance();
        float getDistanceX();
        float getDistanceY();
        void setDistance(float);
        void setDistanceX(float);
        void setDistanceY(float);
        float getCameraZ();
        void setCameraZ(float);
        static PlyReader pl;
};
