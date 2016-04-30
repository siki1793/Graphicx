#include <iostream>
#include <math.h>
#include "Model.h"
#include "Controller.h"
// #include "Model.h"
#include "arcball.h"

// #include "FastTrackball.h"

const vec eye( 0.5f, 0.3f, -2.0f );
const vec centre( 0.0f, 0.0f, 0.0f );
const vec up( 0.0f, 1.0f, 0.0f );
const float SPHERE_RADIUS = 15.0f;



void Model::resize(int w, int h) {

const vec eye( 0.5f, 0.3f, -2.0f );
const vec centre( 0.0f, 0.0f, 0.0f );
const vec up( 0.0f, 1.0f, 0.0f );

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 50.0f, (float) w / (float) h, 1.0f, 50.0f );
    gluLookAt(
        eye.x, eye.y, eye.z,
        centre.x, centre.y, centre.z,
        up.x, up.y, up.z );

        printf("light    %f    %f     %f\n", eye.x, eye.y, eye.z);

    arcball_setzoom( SPHERE_RADIUS, eye, up );

    texture[0] = LoadGLTextures("textures/brickwall.bmp");
    texture[1] = LoadGLTextures("textures/world.bmp");
    texture[2] = LoadGLTextures("textures/apple.bmp");
}

void Model::display(){
    //Objects of corresponding classes
    GLuint myTexture;
    Controller texC;
    Model texV;
    

    //Default Settings and clearing buffers
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &myTexture);
    glBindTexture(GL_TEXTURE_2D, myTexture); //the title screen
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
/*
    texM.quaternion('x', Trackball[0]);
    
/*    gluLookAt(
        texM.getEyeCurrent(0)/15.0f, texM.getEyeCurrent(1)/15.0f, texM.getEyeCurrent(2)/15.0f,
        0, 0, 0,
        0, 1, 0 );
*/ //   texV.light();
    /*texM.quaternion('y', Trackball[1]);
    gluLookAt(
        texM.getEyeCurrent(0)/15.0f, texM.getEyeCurrent(1)/15.0f, texM.getEyeCurrent(2)/15.0f,
        0, 0, 0,
        0, 1, 0 );*/
    arcball_rotate();
    texV.light();

    glPushMatrix();

        //translate the object
        glTranslatef(distanceX, distanceY, 0.0);
        // glTranslatef(0.0, -(pl1.getyMin()+pl1.getyMax()), 0.0);

        //scaled by mouse scroll
        // glScalef(texC.getScale(), texC.getScale(), texC.getScale());
        glPushMatrix();

        glTranslatef(-0.5, 0.0, 0.0);
        // glTranslatef(0.0, -0.09, 0.0);
        // glRotatef(-90.0, 1.0, 0.0, 0.0);
        // glRotatef(-90.0, 0.0, 0.0, 1.0);
        // glRotatef(45.0, 0.0, 0.0, 1.0);
        // glTranslatef(0.0, 0.90, 0.3);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture[1]->sizeX, texture[1]->sizeY, 1, 
                        GL_RGB, GL_UNSIGNED_BYTE, texture[1]->data);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        plyScale=pl.scalePly(0.5);
        std::cout<<" scale value "<<plyScale<<std::endl;
        originX=0.0;
        originY=0.0;
        originZ=0.0;
        errorY=0.0;
        errorY=(pl.getYMax()-pl.getYMin())/2.0;

        glScalef(plyScale,plyScale,plyScale);
        glTranslatef((-pl.getCentroid(0)-originX),(-pl.getCentroid(1)+errorY-originY),(-pl.getCentroid(2)-originZ));

        texV.drawPly(pl,2);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.5, 0.0, 0.0);
        // glTranslatef(0.0, -0.09, 0.0);
        // glRotatef(-90.0, 1.0, 0.0, 0.0);
        // glRotatef(-90.0, 0.0, 0.0, 1.0);
        // glRotatef(45.0, 0.0, 0.0, 1.0);
        // glTranslatef(0.0, 0.90, 0.3);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture[2]->sizeX, texture[2]->sizeY, 1, 
                        GL_RGB, GL_UNSIGNED_BYTE, texture[2]->data);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        plyScale=pl1.scalePly(0.5);
        std::cout<<" scale value "<<plyScale<<std::endl;
        originX=0.0;
        originY=0.0;
        originZ=0.0;
        errorY=0.0;
        errorY=(pl1.getYMax()-pl1.getYMin())/2.0;

        glScalef(plyScale,plyScale,plyScale);
        glTranslatef((-pl1.getCentroid(0)-originX),(-pl1.getCentroid(1)+errorY-originY),(-pl1.getCentroid(2)-originZ));

        texV.drawPly(pl1,1);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture[0]->sizeX, texture[0]->sizeY, 
                            1  , GL_RGB, GL_UNSIGNED_BYTE, texture[0]->data);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTranslatef (0.0, 0.98, 0.0);
        // glRotatef (90, 1, 0, 0);
       texV.drawFloor();
    glPopMatrix();

    glDisable(GL_LIGHTING);

    //Call for drawing the axes

    glFlush();
    glutSwapBuffers();
}

//Light position
void Model::light(){
    Model texV;
    vec eye_coor;
    GLfloat light0_position[] = {0.0f, 1.0f, 0.0f, 0.0f};
    GLfloat light4_position[] = {0.5f, 1.0f, 0.0f, 0.0f};
    GLfloat light0_ambient[] =  {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat light0_diffuse[] =  {1.0f, 1.0f, 1.0f, 0.0f};

    // GLfloat light1_position[] = {0.0f, 0.0f, 2.0f, 1.0f};
    printf("light    %f    %f     %f\n", eye_coor.getCurrentX(), eye_coor.getCurrentY(), eye_coor.getCurrentZ());
    GLfloat light1_position[] = {eye_coor.getCurrentX(), eye_coor.getCurrentY(), eye_coor.getCurrentZ(), 1.0f};
    GLfloat light1_ambient[] =  {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat light1_diffuse[] =  {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat qaSpecularLight[]    = {1.0, 0.0, 0.0, 0.0};
    GLfloat dirVector1[]={  -eye_coor.getCurrentX(), -eye_coor.getCurrentY(), -eye_coor.getCurrentZ(), 0.0};
    glEnable( GL_LIGHTING );

    if (lightList[0]) {
        glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
        glLightfv(GL_LIGHT4, GL_AMBIENT, light0_ambient);
        glLightfv(GL_LIGHT4, GL_DIFFUSE, light0_diffuse);
        glEnable(GL_LIGHT4);
    } else {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT4);
    }
    if (lightList[1]) {
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 40.0);
        glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,dirVector1);
        glEnable(GL_LIGHT1);
    } else {
        glDisable(GL_LIGHT1);
    }
    if (lightList[2]) {
        GLfloat light2_position[] = {0.05f, 0.3f, 0.1f, 1.0f};
        GLfloat light2_ambient[] =  {200.0/255.0f, 251.0/255.0f, 1.0f, 0.0f};
        GLfloat light2_diffuse[] =  {1.0f, 1.0f, 1.0f, 0.0f};
        GLfloat dirVector2[] = {0.3f, 0.0f, 0.0f, 0.0};

        glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
        glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 25.0);
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 40.0);
        glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,dirVector2);
        glEnable(GL_LIGHT2);
    } else {
        glDisable(GL_LIGHT2);
    }
    if (lightList[3]) {
        GLfloat light3_position[] = {-0.05f, 0.3f, 0.1f, 1.0f};
        GLfloat light3_ambient[] =  {102.0/255.0f, 151.0/255.0f, 220.0/255.0f, 0.0f};
        GLfloat light3_diffuse[] =  {1.0f, 1.0f, 1.0f, 0.0f};
        GLfloat dirVector3[] = {-0.3f, 0.0f, 0.0f, 0.0};

        glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
        glLightfv(GL_LIGHT3, GL_AMBIENT, light3_ambient);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 25.0);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 40.0);
        glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,dirVector3);
        glEnable(GL_LIGHT3);
    } else {
        glDisable(GL_LIGHT3);
    }
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_NORMALIZE);
}

// Draws grids
void Model::drawFloor() {
    float coor = 2.0;
    glBegin(GL_QUADS);
        glNormal3d(0,1,0);
        glTexCoord2f(0,0);
        glVertex3f(-coor/2,-coor/2,-coor/2);
        glTexCoord2f(0,5);
        glVertex3f(-coor/2,-coor/2,coor/2);
        glTexCoord2f(5,5);
        glVertex3f(coor/2,-coor/2,coor/2);
        glTexCoord2f(5,0);
        glVertex3f(coor/2,-coor/2,-coor/2);
    glEnd();
}

//Draws Bunny
void Model::drawPly(PlyReader pl,int shape){
    for(int i = 0; i < pl.getNoOfFaces(); i++){
        glBegin(GL_POLYGON);
            for(int j = 0; j < (int)pl.getFacesVertices(i); j++){
                int f=pl.getFaces(i,j);
                glNormal3f(pl.getNormal(f,0), pl.getNormal(f,1), pl.getNormal(f,2));
                GLfloat x=pl.getVertices(pl.getFaces(i,j),0);
                GLfloat y=pl.getVertices(pl.getFaces(i,j),1);
                GLfloat z=pl.getVertices(pl.getFaces(i,j),2);

                if(shape==1)
                {
                    double u=((atan2(x,z))/(2*M_PI))+.5;
                    double v=(y/pl.getZMax())+.5;

                glTexCoord2f(u,v);
                }
                else if(shape==2)
                {
                    
                    double lenght=sqrt((x-pl.getCentroid(0))*(x-pl.getCentroid(0))+
                        (y-pl.getCentroid(1))*(y-pl.getCentroid(1))+(z-pl.getCentroid(2))*(z-pl.getCentroid(2)));

                    //normalization
                    double normX=(x-pl.getCentroid(0))/lenght;
                    double normY=(y-pl.getCentroid(1))/lenght;
                    double normZ=(z-pl.getCentroid(2))/lenght;

                    double u=0.5+(atan2(normX,normZ)/(2*M_PI));
                    double v=0.5+(asin(normY)/M_PI);

                    glTexCoord2f(u,v);
                }
                //getUVCoord(3*pl.getVertices(pl.getFaces(i,j),0),
                //    3*pl.getVertices(pl.getFaces(i,j),1),3*pl.getVertices(pl.getFaces(i,j),2));
                glVertex3f(x,y,z);

            }
        glEnd();
    }
}

//Draws X,Y,Z Axes
void Model::drawAxes(){
    glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_LINES);//x axies line segment
    glVertex3f( 0.0, 0.0, 0.0);
    glVertex3f( 0.5, 0.0, 0.0);
   glEnd();
   glPushMatrix();
   glTranslatef(0.5,0.0,0.0);
      glRotatef(90.0,0.0,1.0,0.0);
      glutSolidCone (0.01, 0.02, 3, 4);
    glPopMatrix();
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_LINES);//y axies line segment
    glVertex3f( 0.0, 0.0, 0.0);
    glVertex3f( 0.0, 0.5, 0.0);
   glEnd();
   glPushMatrix();
   glTranslatef(0.0,0.5,0.0);
   glRotatef(-90.0,1.0,0.0,0.0);
      glutSolidCone (0.01, 0.02, 3, 4);
    glPopMatrix();
   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_LINES);//z axies line segment
    glVertex3f( 0.0, 0.0, 0.0);
    glVertex3f( 0.0, 0.0, 0.5);
   glEnd();
   glPushMatrix();
   glTranslatef(0.0,0.0,.5);
      glutSolidCone (0.01, 0.02, 3, 4);
    glPopMatrix();
}

//Getter and Setter functions required to call from other classes
float Model::getDistance(){
    return distance;
}
float Model::getDistanceX(){
    return distanceX;
}
float Model::getDistanceY(){
    return distanceY;
}
void Model::setDistance(float value){
    distance = value;
}
void Model::setDistanceX(float value){
    distanceX = value;
}
void Model::setDistanceY(float value){
    distanceY = value;
}

void Model::updateLight (int index) {
    lightList[index] = !lightList[index];
}
