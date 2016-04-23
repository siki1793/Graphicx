/*
    OpenGL Tutor : Rotate

    Copyright (c) 1999 Nate Miller
    
    File        -- rotate.c
    Date        -- 7/01/99
    Author      -- Nate 'm|d' Miller
    Contact     -- vandals1@home.com
    Web         -- http://nate.scuzzy.net

    Many people have asked about how to rotate objects about an axis or point
    or just about their center.  That is why I wrote this demo.  I tried to 
    keep it as simple as possible so that people can see the big picture.  
    It looks horrid I know but its not intended to be flashy, it should be used
    as a tool to learn.  I overcommented this one so beware.  

    If you want to compile this make sure that you link too the following 
    libraries: opengl32.lib glu32.lib glut32.lib

    Usage
    =====
    q           -- quit
    x/y/z       -- changes axis of rotation
    left mouse  -- rotates entire scene
*/
#define APP_NAME                "OpenGL Tutor : Rotate"
#define X_AXIS                  0
#define Y_AXIS                  1
#define Z_AXIS                  2

#include <stdio.h>
#include <GL/glut.h>

/* vector */
typedef float vec3_t[3]; 

/* enumerations for the mouse buttons */
enum {
    UP = 1, 
    DOWN, 
};

/* window width and height */
int winW = 640;
int winH = 480;

/* old position of the mouse */
int oldX = -13;
int oldY = -13;

/* mouse state, UP or DOWN */
int mState = UP;

/* current axis of rotation */
int axisRot = X_AXIS;

/* amount to rotate about axis */
float rotate = 0.0f;

/* vector which describes the axis to rotate about */
vec3_t axis = {1.0, 0.0, 0.0};

/* global rotation, for use with the mouse */
vec3_t gRot = {0,0,0};

/* should we animate ? */
int aniOn = 1;

/*
=============
drawSphere
=============

Draws our spheres to the screen.  The first sphere rotates about the current 
axis.  The second rotates about its center.  
*/
void drawSphere (void)
{
    /* 
        This sphere is going to be rotated around the *current axis*.  This is 
        because the model was first rotated and then translated.
    */
    glPushMatrix ();

    glRotatef (rotate, axis[0], axis[1], axis[2]);

    glTranslatef (-15.0, 10.0, 5.0);

    glColor3f (1.0, 0.0, 0.0);

    glutWireSphere (5.0, 6.0, 6.0);

    glPopMatrix ();

    /* 
        This sphere is going to be rotated around the its own center.  This is 
        because the model was first translated and then rotated.  
    */
    glPushMatrix ();

    glTranslatef (5.0, 10.0, 0.0);

    glRotatef (rotate, axis[0], axis[1], axis[2]);

    glColor3f (0.0, 1.0, 0.0);

    glutWireSphere (2.0, 6.0, 6.0);

    glPopMatrix ();
}
/*
=============
drawAxis
=============

Draws out the X / Y / Z axis just for reference.  
*/
void drawAxis (void)
{
    glColor3f (0.5, 0.5, 0.5);
    glBegin (GL_LINES);
        glColor3f (0.5, 0.0, 0.0);
        glVertex3f (-20.0, 0.0, 0.0);
        glVertex3f (20.0, 0.0, 0.0);

        glColor3f (0.0, 0.5, 0.0);
        glVertex3f (0.0, 20.0, 0.0);
        glVertex3f (0.0, -20.0, 0.0);

        glColor3f (0.0, 0.0, 0.5);
        glVertex3f (0.0, 0.0, -20.0);
        glVertex3f (0.0, 0.0, 20.0);
    glEnd ();
}
/*
=============
glutDisplay
=============

The display function. 
*/
void glutDisplay (void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    /* move our eye position 50 units away */
    glTranslatef (0, 0, -50);	  
    /* apply the rotation from the mouse */
    glRotatef (gRot[0], 1.0, 0.0, 0.0);
    glRotatef (gRot[1], 0.0, 1.0, 0.0);

    drawAxis ();
    drawSphere ();

    glutSwapBuffers();
}
/* 
=============
glutIdle
=============

Idle function, makes it animate.  
*/
void glutIdle (void)
{	
    if (aniOn)
    {
        rotate += 1.0f;

        if (rotate > 360)
            rotate = 0.0f;
        glutPostRedisplay ();
    }
}
/* 
=============
glutResize
=============

Resize function, called on app start and on resize.
*/
void glutResize (int w, int h)
{	
    if (!h)
       return;

    winW = w;
    winH = h;

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport (0, 0, winW, winH);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    gluPerspective (90, winW / winH, 1, 9999);

    glutPostRedisplay ();
}
/* 
=============
glutKeyboard
=============

Keyboard handler.
*/
void glutKeyboard (unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':
        case 'Q':
            exit (1);
        break;
        case 'x':
        case 'X':
            /* axis of rotation is now X */
            axisRot = X_AXIS;
            axis[0] = 1.0;
            axis[1] = axis[2] = 0.0;
        break;
        case 'y':
        case 'Y':
            /* axis of rotation is now Y */
            axisRot = Y_AXIS;
            axis[1] = 1.0;
            axis[0] = axis[2] = 0.0;
        break;
        case 'z':
        case 'Z':
            /* axis of rotation is now Z */
            axisRot = Z_AXIS;
            axis[2] = 1.0;
            axis[1] = axis[0] = 0.0;
        break;
        case ' ':
            /* animation on/off */
            aniOn = !aniOn;
        break;
    }
    glutPostRedisplay ();
}
/*
=============
clamp
=============

Clamps the rotation to -360 to 360
*/
void clamp (vec3_t v)
{
    int i;

    for (i = 0; i < 3; i ++)
        if (v[i] > 360 || v[i] < -360)
            v[i] = 0.0f;
}
/*
=============
glutMotion
=============

Called when the mouse moves in our app area. 
*/
void glutMotion(int x, int y) 
{
    if (mState == DOWN) 
    {
        gRot[0] -= ((oldY - y) * 180.0f) / 100.0f;
        gRot[1] -= ((oldX - x) * 180.0f) / 100.0f;
        clamp (gRot);
        glutPostRedisplay ();
    }
    printf("%f  %f\n", gRot[0], gRot[1]);
    oldX = x; 
    oldY = y;
}
/*
=============
glutMouse
=============

Called when the mouse is clicked.
*/
void glutMouse(int button, int state, int x, int y) 
{
    if(state == GLUT_DOWN) 
    {
        switch(button) 
        {
            case GLUT_LEFT_BUTTON:
            case GLUT_RIGHT_BUTTON:
                mState = DOWN;
                oldX = x;
                oldY = y;
            break;
        }
    } else if (state == GLUT_UP) 
        mState = UP;
}
/* 
=============
glInit
=============

Sets up various OpenGL stuff.
*/
void glInit (void)
{
    glEnable (GL_DEPTH_TEST);
}
void main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (winW,winH);
    glutCreateWindow (APP_NAME);
    glutKeyboardFunc (glutKeyboard);
    glutDisplayFunc (glutDisplay);
    glutReshapeFunc (glutResize);
    glutMotionFunc (glutMotion);
    glutMouseFunc (glutMouse);
    glutIdleFunc (glutIdle);
    
    glInit ();
    glutMainLoop();
}
