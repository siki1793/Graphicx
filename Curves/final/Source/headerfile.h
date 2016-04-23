#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <vector>

using namespace std;

#define STEP 0.01// values between 0 and 1. it's the step for time parameter.

int SCREEN_WIDTH=1000;
int SCREEN_HEIGHT=780;
bool loadBezier = false;
bool loadLagrange = false;
bool setangle = false;
bool settranslate = false;
bool click=false;
int flag=0;
float two_px=0.,two_py= 0.;
bool pic=true;
bool del=false;
float two_px1=0.,two_px2=0.;
float two_py1=0.,two_py2=0.;
float Angle=0.;
float distanceX = 0., distanceY = 0.;
float scale = 1.;

int p_count=0,clicks_count=0;//number of control points
typedef struct{
	float x,y;// 2D coordinates of a point
}POINT;
POINT *control_p,*aux;//array of control points
int i,j,f;
int lower_x;
int upper_x;
float t;//time

#include "model.h"
#include "controller.h"
#include "view.h"
