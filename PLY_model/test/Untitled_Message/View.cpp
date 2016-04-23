#include <iostream>
#include <math.h>
#include "View.h"
#include "Controller.h"
#include "Model.h"
#include "FastTrackball.h"


void View::display(){
    //Objects of corresponding classes

    Controller a1c;
    View a1v;
    Model a1m;

    //Default Settings and clearing buffers
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glMatrixMode (GL_MODELVIEW);
    glPushMatrix();
        a1m.quaternion('x',a1c.getmAngle());
        a1v.light();
    glPopMatrix();

    //Call for drawing the axes
    glLoadIdentity();
    a1v.drawAxes();

    int clicks = a1c.getClickCount();
    if(clicks){
        for(int i = 0; i < clicks; i++){
            a1v.drawPoint(2.0, a1c.getCoordinatesX(i), a1c.getCoordinatesY(i));
        }
    }

    if(clicks >= 2){
        distance = a1m.calculateDistance(a1c.getCoordinatesX(0), a1c.getCoordinatesY(0),
            a1c.getCoordinatesX(1), a1c.getCoordinatesY(1));
        if(a1c.getFlag()){
            a1c.setFlag(0);
        }
        a1v.drawLine(a1c.getCoordinatesX(0), a1c.getCoordinatesY(0), 0.0,
            a1c.getCoordinatesX(1), a1c.getCoordinatesY(1), 0.0);
    }

    glPushMatrix();
	//Quaternion rotation about x,y,z axes respectively.
    a1m.quaternion('x', gRot[0]);
    a1m.quaternion('y', gRot[1]);
    a1m.quaternion('z', gRot[2]);
    
    //This is to translate the object.
    glTranslatef(distanceX, distanceY, 0.0);
    //printf("%f  %f\n", gRot[0], gRot[1]);

    //Also, the object is scaled by "+/-" keys.
    glScalef(a1c.getScale(),a1c.getScale(),a1c.getScale());

    //a1v.light();
    a1v.drawModel();
    a1v.drawBoundingBox();
    glDisable(GL_LIGHTING);

    View a2v;
    glColor3f(1.0, 0.0, 0.0);
    a2v.drawLine(-0.5, 0.0, 0.0, 0.5, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    a2v.drawLine(0.0, -0.5, 0.0, 0.0, 0.5, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    a2v.drawLine(0.0, 0.0, -0.5, 0.0, 0.0, 0.5);

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

//Light position
void View::light(){
    GLfloat light0_position[] = {1.0f, 1.0f, 0.0f, 0.0f};
    GLfloat light0_ambient[] =  {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat light0_diffuse[] =  {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat cyan[]={1.0,1.0,1.0,0.0};
    
    // GLfloat specular[]={1.0,1.0,1.0,0.0};
    // GLfloat shininess[]={80.0};

    glEnable( GL_LIGHTING );
        glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0_ambient);
        glColor3f(1.0, 1.0, 0.0);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

void View::drawBoundingBox () {
    glColor3f (1.0, 0.0, 0.0);
    printf("%f %f %f\n", pl.getMaxX(), pl.getMaxY(), pl.getMaxZ() );
    drawPoint(10.0, (pl.getMaxX()-325)/(float)650, (-pl.getMaxY()+325)/(float)650);
    drawPoint(10.0, (pl.getMinX()-325)/(float)650, (-pl.getMinY()+325)/(float)650);
    //drawLine ((pl.getMaxX()-325), (-pl.getMaxY()+325) , pl.getMaxZ()
    // drawLine ((pl.getMaxX()-325)/(float)650, (-pl.getMaxY()+325)/(float)650 , pl.getMaxZ(),
    //     (pl.getMinX()-325)/(float)650, (-pl.getMaxY()+325)/(float)650, pl.getMaxZ());
}

//Draws model
void View::drawModel(){

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
void View::drawAxes(){
    View a1v;
    //glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0, 0.0, 0.0);
    a1v.drawLine(-1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    a1v.drawLine(0.0, -1.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    a1v.drawLine(0.0, 0.0, -1.0, 0.0, 0.0, 1.0);
}

//Draws line
void View::drawLine(float x1, float y1, float z1, float x2, float y2, float z2){
    glBegin(GL_LINES);
        glVertex3f(x1 , y1 , z1);
        glVertex3f(x2 , y2 , z2);
    glEnd();
}

//Draws point
void View::drawPoint(float pointSize, float x, float y){
    glPointSize(pointSize);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
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
void View::updateRotation(int xPos, int yPos) {

    gRot[0] -= ((yPos - currentLoc[1]) * 180.0f) / 100.0f;
    gRot[1] -= ((xPos - currentLoc[0]) * 180.0f) / 100.0f;
        
    for (int i = 0; i < 3; i ++)
        if (gRot[i] > 360 || gRot[i] < -360)
            gRot[i] = 0.0f;

    currentLoc[0] = xPos;
    currentLoc[1] = yPos;
}
