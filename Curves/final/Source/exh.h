#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <vector>

using namespace std;

#define STEP 0.01// values between 0 and 1. it's the step for time parameter.

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern bool loadBezier;
extern bool loadLagrange;
extern bool setangle;
extern bool settranslate;
extern bool click;
extern int flag;
extern float two_px,two_py;
extern bool pic;
extern bool del;
extern float two_px1,two_px2;
extern float two_py1,two_py2;
extern float Angle;
extern float distanceX, distanceY;
extern float scale;

extern int p_count,clicks_count;//number of control points
typedef struct{
	float x,y;// 2D coordinates of a point
}POINT;
extern POINT *control_p,*aux;//array of control points
extern int i,j,f;
extern int lower_x;
extern int upper_x;
extern float t;//time

#include "model.h"
#include "controller.h"
#include "view.h"
