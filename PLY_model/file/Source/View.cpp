#include "View.h"
#include "Controller.h"
#include "Model.h"
#include<iostream>
#include<math.h>

float trackBallRotate[3]={0,0,0};
float cameraZ = 2.0;

void View::renderFunction(){
    //Objects of corresponding classes
    Controller pc;
    View pv;
    Model pm;

    //Default Settings and clearing buffers
    glClearColor(0.1, 0.2, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glPushMatrix();
         pv.light();
    glPopMatrix();

    //Call for drawing the axes
    glLoadIdentity();
    gluLookAt(0.0,0.0,pv.getCameraZ(),0.0,0.0,0.0,0.0,1.0,0.0);
    glPushMatrix();
	//Quaternion rotation about x,y,z axes respectively.
	glTranslatef(distanceX,distanceY,0.0);
	pm.quaternion('x',pc.getxAngle());
    pm.quaternion('y',pc.getyAngle());
    pm.quaternion('z',pc.getzAngle());


    //Quaternion rotation trackBall rotation
    pm.quaternion('x', trackBallRotate[0]);
    pm.quaternion('y', trackBallRotate[1]);
    pm.quaternion('z', trackBallRotate[2]);


    //std::cout<<"inside renderFunction vertices: "<<pl.noOfVertices<<" faces: "<<pl.noOfFaces<<std::endl;
    //This is to translate the object.



    //std::cout<<(pl.getyMax()+pl.getyMin())/2<<" ymax  "<<pl.getyMax()<<"  y min "<<pl.getyMin()<<"  total sum    "<<pl.getyMax()+pl.getyMin()<<std::endl;

    //Also, the object is scaled by "+/-" keys.
    glScalef(pc.getScale(),pc.getScale(),pc.getScale());


    glPushMatrix();

    if((pl.getyMin()+pl.getyMax())>1.0 && (pl.getyMin()+pl.getyMax())>1.0 && (pl.getyMin()+pl.getyMax())>1.0)
        glScalef(0.5,0.5,0.5);
    else
        if((pl.getyMin()+pl.getyMax())<1.0 && (pl.getyMin()+pl.getyMax())<1.0 && (pl.getyMin()+pl.getyMax())<1.0)
        glScalef(1.2,1.2,1.2);
    glTranslatef(0.0,-((pl.getyMin()+pl.getyMax())),0.0);
    pv.drawPly();
    glPopMatrix();
    glDisable(GL_LIGHTING);
      pv.drawAxis();
      pv.drawBoundingBox();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}
void View::reshape(int w, int h)
{
	float ratio =  ((float) w) / ((float) h); // window aspect ratio
	glMatrixMode(GL_PROJECTION); // projection matrix is active
	glLoadIdentity(); // reset the projection
	gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
	glMatrixMode(GL_MODELVIEW); // return to modelview mode
	glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
	glutPostRedisplay();
}
//Light position
void View::light(){
    View pv;
    GLfloat light0_position[] = {0.75f, 0.75f, 0.0f, 0.0f};
    GLfloat light1_position[] = {0.0f,0.0f, 0.0f, 0.0f};
    GLfloat light0_ambient[] =  {102.0/255.0f, 51.0/255.0f, 1.0f, 0.0f};
    GLfloat light0_diffuse[] =  {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat cyan[]={1.0,1.0,1.0,0.0};
    GLfloat specular[]={1.0,1.0,1.0,0.0};
    GLfloat shininess[]={80.0};


    pv.drawPoint(0.75,0.75);
    glEnable( GL_LIGHTING );
        glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
        glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);

        glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
        glLightfv(GL_LIGHT1,GL_AMBIENT,light0_ambient);
        glLightfv(GL_LIGHT1,GL_DIFFUSE,light0_diffuse);

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light0_ambient);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

//Draws Bunny
void View::drawPly(){
    for(int i = 0; i < pl.getNoOfFaces(); i++){
        glBegin(GL_POLYGON);
            glNormal3f(pl.getNormals(i,0), pl.getNormals(i,1), pl.getNormals(i,2));
            for(int j = 0; j < 3; j++){
                glVertex3f(3*pl.getVertices(pl.getFaces(i,j),0),
                    3*pl.getVertices(pl.getFaces(i,j),1),3*pl.getVertices(pl.getFaces(i,j),2));
            }
        glEnd();
    }
}

//Draws X,Y,Z Axes
void View::drawAxis()
{
    glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_LINES);//x axies line segment
    glVertex3f( -0.5, 0.0, 0.0);
    glVertex3f( 0.5, 0.0, 0.0);
   glEnd();
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_LINES);//y axies line segment
    glVertex3f( 0.0, -0.5, 0.0);
    glVertex3f( 0.0, 0.5, 0.0);
   glEnd();
   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_LINES);//z axies line segment
    glVertex3f( 0.0, 0.0, -0.5);
    glVertex3f( 0.0, 0.0, 0.5);
   glEnd();
}
//Draws line
void View::drawLine(float x1,float y1,float z1,float x2,float y2,float z2){
    glBegin(GL_LINES);
        glVertex3f(x1 , y1 , z1);
        glVertex3f(x2 , y2 , z2);
    glEnd();
}

//Draw boundingBox
void View::drawBoundingBox ()
{
    glColor3f (1.0, 1.0, 1.0);
    drawLine(-0.5,0.5,0.5,0.5,0.5,0.5);//-x y z || x y z
    glColor3f (1.0, 1.0, 1.0);
    drawLine(-0.5,-0.5,0.5,0.5,-0.5,0.5);//-x -y z || x -y z
    glColor3f (1.0, 1.0, 1.0);
    drawLine(-0.5,0.5,0.5,-0.5,-0.5,0.5);//-x y z || -x -y z
    glColor3f (1.0, 1.0, 1.0);
    drawLine(-0.5,0.5,-0.5,0.5,0.5,-0.5);//-x y -z || x y -z
    glColor3f (1.0, 1.0, 1.0);
    drawLine(-0.5,-0.5,-0.5,0.5,-0.5,-0.5);//-x -y -z || x -y -z
    glColor3f (1.0, 1.0, 1.0);
    drawLine(-0.5,0.5,-0.5,-0.5,-0.5,-0.5);//-x y -z || -x -y -z
    glColor3f (1.0, 1.0, 1.0);
    drawLine(-0.5,0.5,0.5,-0.5,0.5,-0.5);//-x y z || -x y -z
    glColor3f (1.0, 1.0, 1.0);
    drawLine(-0.5,-0.5,0.5,-0.5,-0.5,-0.5);//-x -y z || -x -y -z
    glColor3f (1.0, 1.0, 1.0);
    drawLine(0.5,0.5,0.5,0.5,-0.5,0.5);//x y z || x y -z
    glColor3f (1.0, 1.0, 1.0);
    drawLine(0.5,0.5,-0.5,0.5,-0.5,-0.5);//x -y z || x -y -z
    glColor3f (1.0, 1.0, 1.0);
    drawLine(0.5,0.5,0.5,0.5,0.5,-0.5);//-x y z || -x -y z
    glColor3f (1.0, 1.0, 1.0);
    drawLine(0.5,-0.5,0.5,0.5,-0.5,-0.5);//-x y z || -x -y z
}
//Draws point
void View::drawPoint(float x,float y){
    glPointSize(3.0);
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}

void View::dragRotation(int xPos, int yPos) {

    trackBallRotate[0] -= ((yPos - currentY) * 180.0f) / 100.0f;
    trackBallRotate[1] -= ((xPos - currentX) * 180.0f) / 100.0f;

    for (int i = 0; i < 3; i ++)
        if (trackBallRotate[i] > 360 || trackBallRotate[i] < -360)
            trackBallRotate[i] = 0.0f;

    currentX = xPos;
    currentY = yPos;
}

//Getter and Setter functions required to call from other classes
float View::getDistance(){
    return distance;
}
float View::getDistanceX(){
    return distanceX;
}
float View::getDistanceY(){
    return distanceY;
}
void View::setDistance(float value){
    distance = value;
}
void View::setDistanceX(float value){
    distanceX = value;
}
void View::setDistanceY(float value){
    distanceY = value;
}

float View::getCameraZ(){
    return cameraZ;
}

void View::setCameraZ(float value){
    cameraZ = value;
}
