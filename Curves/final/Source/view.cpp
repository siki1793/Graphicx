#ifndef HEADER_EH
#define HEADER_EH
#include "exh.h"
#endif

void view::drawPoint(int x,int y){//draw control points
	glColor3f(1.0,2.0,1.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

void view::drawLine(POINT p1,POINT p2){//draw the line between control points
	glColor3f(1.0,1.0,1.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex2f(p1.x,p1.y);
		glVertex2f(p2.x,p2.y);
	glEnd();
	glFlush();
}
void view::drawCurve(POINT p1,POINT p2,float color){//draw the bezier curve
	glColor3f(1.0,0.0,0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex2f(p1.x,p1.y);
		glVertex2f(p2.x,p2.y);
	glEnd();
	glFlush();
}

void view::drawAxis(void)
{
 glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_LINES);//y axies line segment
    glVertex3f( 0,-SCREEN_WIDTH/2,0);
    glVertex3f( 0,SCREEN_WIDTH/2,0);
   glEnd();
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_LINES);//x axies line segment
    glVertex3f( -SCREEN_WIDTH/2,0,0);
    glVertex3f( SCREEN_WIDTH/2,0,0);
   glEnd();
}

void view::relocate(void)
{
    POINT P=control_p[0];
    glPointSize(5.0);
    glColor3f(1.0, 2.0, 1.0);
     glBegin(GL_POINTS);
      for (int i = 0; i < p_count; i++)
      {
         glVertex2i(control_p[i].x,control_p[i].y);
        }
     glEnd();
}

void view::bezier(void)
{
    model cm;
    view cv;
    POINT M,P=control_p[0];
    cv.relocate();
    for(t = 0;t <= 1.0; t += STEP) {
					M=cm.bernstein(control_p,t,p_count-1);
					cv.drawCurve(P,M,t);
					P=M;
				}
}

void view::lagrange(void)
{
    float lag_x;
    float lag_y;
    model cm;
    view cv;
    cv.relocate();
    glColor3f(1.0,0.0,1.0);
    glBegin(GL_LINE_STRIP);
      for (i = lower_x; i <= upper_x; i++) {
	 lag_x = (float) i ;
         lag_y = cm.interpolation( control_p , lag_x, p_count);
         glColor3f(1.0,0.0,1.0);
	 glVertex2f ( lag_x, lag_y );
      }
   glEnd();

}

void view::renderFunction() {

    view cv;

    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    cv.drawAxis();

    glPushMatrix();

    //if(setangle)
    glRotatef(Angle,0.0,0.0,1.0);

    glTranslatef(distanceX,distanceY,0.0);
    glScalef(scale,scale,scale);


    if(settranslate) //&& flag == 2)
    {
        cout<<"inside render"<<endl;
        two_px = two_px1-two_px2;
        two_py = two_py1-two_py2;
        cout<<two_px<<" x "<<two_py<<" y "<<endl;
        glTranslatef(two_px,two_py,0.0);
    }
    cv.relocate();
    if(loadBezier)
    {
        cv.bezier();
        //loadBezier=false;
    }
    if(loadLagrange)
    {
        cv.lagrange();
        //loadLagrange = false;
    }
        cv.relocate();
    cout<<"scaled "<<scale<<"and translated x by "<<distanceX<<" and by y"<<distanceY<<" at an angle of "<<Angle<<endl;
    glPopMatrix();
    glFlush();
}

void view::reshape (int w, int h)
{
   view cv;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (-(GLdouble) SCREEN_WIDTH/2, (GLdouble) SCREEN_WIDTH/2, -(GLdouble) SCREEN_HEIGHT/2, (GLdouble) SCREEN_HEIGHT/2);
//   if (w >= h)
//      gluOrtho2D (-(GLdouble) SCREEN_WIDTH/2, (GLdouble) SCREEN_WIDTH/2,
//         -(GLdouble) SCREEN_HEIGHT/2*(GLfloat)h/(GLfloat)w, (GLdouble) SCREEN_HEIGHT/2*(GLfloat)h/(GLfloat)w);
//   else
//      gluOrtho2D (-(GLdouble) SCREEN_WIDTH/2*(GLfloat)w/(GLfloat)h,
//         (GLdouble) SCREEN_WIDTH/2*(GLfloat)w/(GLfloat)h, -(GLdouble) SCREEN_HEIGHT/2, (GLdouble) SCREEN_HEIGHT/2);
   cv.relocate();
   glutPostRedisplay();
//adjusting the window height and widht while reshaping
   SCREEN_HEIGHT = h;
   SCREEN_WIDTH = w;
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
