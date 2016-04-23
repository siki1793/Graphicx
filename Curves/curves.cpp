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
long double factorial(int x){
	long double fact=1;
	int p=1;
	if(x==0 || x==1)
		return 1;
	else{
		while(p<=x){
			fact*=p;
			p++;}
		}
	return fact;
}
long double binomial( int f, int n){
	double com=factorial(n)/(factorial(f)*factorial(n-f));
	return com;
}

//polynomial interpretation for N points
float interploy ( POINT *control_p, float x, int N )
{
  float y;

  float num = 1.0, den = 1.0;
  float sum = 0.0;

  for ( int i = 0; i < N; ++i ) {
    num = den = 1.0;
    for ( int j = 0; j < N; ++j ) {
      if ( j == i ) continue;
      num = num * ( x - control_p[j].x );		 	//x - x2
    }
    for ( int j = 0; j < N; ++j ) {
      if ( j == i ) continue;
      den = den * ( control_p[i].x - control_p[j].x );	//x1 - x2
    }
    sum += num / den * control_p[i].y;
  }
  y = sum;

  return y;
}

POINT bernstein(POINT *control_p,float t,int n){POINT N;N.x=N.y=0;//n=nr de puncte

for(i=0;i<=n;i++){
	N.x+=control_p[i].x*binomial(i,n)*pow(t,i)*pow((1-t),(n-i));
	N.y+=control_p[i].y*binomial(i,n)*pow(t,i)*pow((1-t),(n-i));
	}
	return N;

}

void init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glPointSize(10.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void drawPoint(int x,int y){//draw control points
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

void drawLine(POINT p1,POINT p2){//draw the line between control points
	glColor3f(1.0,1.0,1.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex2f(p1.x,p1.y);
		glVertex2f(p2.x,p2.y);
	glEnd();
	glFlush();
}
void drawCurve(POINT p1,POINT p2,float color){//draw the bezier curve
	glColor3f(1.0,0.0,0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex2f(p1.x,p1.y);
		glVertex2f(p2.x,p2.y);
	glEnd();
	glFlush();
}

void drawAxis(void)
{
 glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_LINES);//y axies line segment
    glVertex3f( 0,-SCREEN_HEIGHT/2,0);
    glVertex3f( 0,SCREEN_HEIGHT/2,0);
   glEnd();
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_LINES);//x axies line segment
    glVertex3f( -SCREEN_WIDTH/2,0,0);
    glVertex3f( SCREEN_WIDTH/2,0,0);
   glEnd();
}

void relocate(void)
{
    POINT P=control_p[0];
    glPointSize(10.0);
    glColor3f(0.0, 0.0, 1.0);
     glBegin(GL_POINTS);
      for (int i = 0; i < p_count; i++)
      {
         glVertex2i(control_p[i].x,control_p[i].y);
        }
     glEnd();
}

void bezier(void)
{
    POINT M,P=control_p[0];
    relocate();
    for(t = 0;t <= 1.0; t += STEP) {
					M=bernstein(control_p,t,p_count-1);
					drawCurve(P,M,t);
					P=M;
				}
}

void lagrange(void)
{
    float lag_x;
    float lag_y;
    relocate();
    glColor3f(1.0,0.0,1.0);
    glBegin(GL_LINE_STRIP);
      for (i = lower_x; i <= upper_x; i++) {
	 lag_x = (float) i ;
         lag_y = interploy( control_p , lag_x, p_count);
         glColor3f(1.0,0.0,1.0);
	 glVertex2f ( lag_x, lag_y );
      }
   glEnd();

}


void mouseEventHandler(int button,int state,int x,int y){
	POINT M,P=control_p[0];
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){//if left-button is clicked then a new control point will be draw
        if(pic)
        {
            cout<<"x : "<<x<<" y : "<<y<<endl;
            x=x-SCREEN_WIDTH/2;
            y=SCREEN_HEIGHT/2-y;
            control_p[p_count].x=(float)x;
            control_p[p_count].y=(float)y;
            cout<<"x "<<control_p[p_count].x<<" and y "<<control_p[p_count].y<<" is stored "<<endl;
            cout<<"insert points"<<endl;
            p_count++;
            for(i=0;i<=p_count-1;i++)
            {
                cout<<"x "<<control_p[i].x<<" y "<<control_p[i].y<<endl;
            }
            if(x>=-SCREEN_WIDTH/2 && x<=lower_x)
                lower_x=x;
            if(x<=SCREEN_WIDTH/2 && x>=upper_x)
                upper_x=x;

            drawPoint(x,y);
		}

    }
	else
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        if(del)
        {
            int pos=0,found=0;
            cout<<"x : "<<x<<" y : "<<y<<endl;
            x=x-SCREEN_WIDTH/2;
            y=SCREEN_HEIGHT/2-y;
            cout<<"x "<<x<<" and y "<<y<<" is stored "<<endl;
                for (i = 0; i < p_count; i++)
                {
                    if ((abs(abs(control_p[i].x) - abs(x)) < 5) && (abs(abs(control_p[i].y) - abs(y)) < 5))
                    {

                        found = 1;
                        cout<<"found x "<<control_p[i].x<<"y "<<control_p[i].y<<endl;
                        pos = i;
                        break;
                    }
                }
                printf("Enter the element to be deleted\n");
                if (found == 1)
                {
                    printf("Enter the element to be deleted\n");
                    for (i = pos; i <  p_count - 1; i++)
                    {
                        control_p[i].x = control_p[i+1].x;
                        control_p[i].y = control_p[i+1].y;
                    }
                    //deletePoint(control_p[p_count-1].x,control_p[p_count-1].y);

                    for(i=0;i<p_count-1;i++)
                    {
                        cout<<"x "<<control_p[i].x<<" y "<<control_p[i].y<<endl;
                    }
                    p_count--;
                    glutPostRedisplay();
            }
        }
        if(click)
        {
            cout<<"inside translate"<<endl;
            //twopoints.clear();
            cout<<"x : "<<x<<" y : "<<y<<endl;
            x=x-SCREEN_WIDTH/2;
            y=SCREEN_HEIGHT/2-y;

            if(flag==0)
            {
            cout<<"x "<<x<<" and y "<<y<<" is stored "<<endl;
                two_px1=(float)x;
                two_py1=(float)y;
            }
            if(flag==1)
            {
            cout<<"x "<<x<<" and y "<<y<<" is stored "<<endl;
                two_px2=(float)x;
                two_py2=(float)y;
            }
            flag++;
            glutPostRedisplay();
        }
}
}

void renderFunction() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glLoadIdentity();
    drawAxis();

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
relocate();
    if(loadBezier)
    {
        bezier();
        //loadBezier=false;
    }
    if(loadLagrange)
    {
        lagrange();
        //loadLagrange = false;
    }
        cout<<"scaled "<<scale<<"and translated x by "<<distanceX<<" and by y"<<distanceY<<" at an angle of "<<Angle<<endl;
  glPopMatrix();
    glFlush();
}

void keyboardEventHandler(unsigned char key,int x, int y){
    if(key == 'w'){
    cout<<"up"<<endl;
        distanceY += 2.;
        glutPostRedisplay();
    }
    else if(key == 's'){
    cout<<"down"<<endl;
        distanceY -= 2.;
        glutPostRedisplay();
    }
    else if(key == 'd'){
    cout<<"right"<<endl;
        distanceX += 2.;
        glutPostRedisplay();
    }
    else if(key == 'a'){
    cout<<"left"<<endl;
        distanceX -= 2.;
        glutPostRedisplay();
    }
    else if(key == '+')
    {
        cout<<"zoom out"<<endl;
        scale = scale * 1.2;
        glutPostRedisplay();
    }
    else if(key == '-')
    {
        cout<<"zoom in"<<endl;
        scale = scale / (float)1.2;
        glutPostRedisplay();
    }
    else if(key == 'q')
    {
        flag = 0;
        del=false;
        pic=true;
        settranslate=false;
    }
    else if(key == 'e')
    {
        flag = 0;
        del=true;
        pic=false;
        settranslate=false;
    }
    else if(key == 't')
    {
        cout<<"inside two points switch"<<endl;
        settranslate=true;
        cout<<settranslate<<endl;
        cout<<"flag "<<flag<<endl;

        del=false;
        pic=false;
        glutPostRedisplay();
    }
    else if(key == 'i')
    {
        click=true;
        del=false;
        pic=false;
    }

switch (key) {
      case 'c':
            renderFunction();
            break;
      case '1':
         cout<<"curve switched"<<endl;
         loadBezier = true;
         loadLagrange=true;
         glutPostRedisplay();
         break;
      case '2':
         loadBezier = false;
         loadLagrange=false;
         glutPostRedisplay();
         break;

      case 'r':
         Angle += 20.;
         setangle=true;
         glutPostRedisplay();
         break;
      case 'l':
         Angle -= 20.;
         setangle=true;
         glutPostRedisplay();
         break;
      case 'D':
      for(i=0;i<p_count-1;i++)
					drawLine(control_p[i],control_p[i+1]);
					break;
      case 27:  /*  Escape Key  */
         exit(0);
         break;
      default:
         break;
    }
}

void reshape (int w, int h)
{
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
   relocate();
   glutPostRedisplay();
//adjusting the window height and widht while reshaping
   SCREEN_HEIGHT = h;
   SCREEN_WIDTH = w;
    glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Bezier Curve");
    init();
    control_p=(POINT *)malloc(clicks_count*sizeof(POINT));
    if(!control_p){
		printf("Allocation failure!");
		exit(EXIT_FAILURE);
		}
    else{
	clicks_count++;
	aux=(POINT *)realloc(control_p,clicks_count*sizeof(POINT));
	if(!aux){
		printf("Reallocation failure!");
		exit(EXIT_FAILURE);
		}
	else{
		control_p=aux;
    		glutmouseEventHandlerFunc(mouseEventHandler);
		}
	}
    glutReshapeFunc (reshape);
    glutDisplayFunc(renderFunction);
    glutKeyboardFunc(keyboardEventHandler);
    glutMainLoop();
   free(control_p);
    free(aux);
    return 0;
}
