#include "Controller.h"
#include "Model.h"
#include "arcball.h"
#include "PlyReader.h"
#include "Scenenode.h"
#include "View.h"

Model texV;
Model *model;
View *v;
// Controller controller->
Controller *controller;
Image *te;

float x = 0.0f;
float y = 0.0f;
float z = 0.0f;
float x3 = 0.0f;
float y3 = 0.0f;
float z3 = -0.2f;

float slop = 0.007;
float prevoiusX =0.0f;
float prevoiusZ =0.0f;
float initX =0.0f;
float initZ =0.0f;

int counter_period=0;
int camera=0;
int count = 0;

bool addChildRoot = false;
bool arcballStatus = false;

float childx = 0.0f;
float childy = 0.0f;
float childz = 0.0f;
float Rchildx = 0.0f;
float Rchildy = 0.0f;
float Rchildz = 0.0f;
float Model3 = 0.0f;

float modelX = 0.0f;
float modelY = 0.0f;
float modelZ = 0.0f;

float speed1=0.05;
float speed2=0.02;
float speed3=0.008f;

Vec3f shift(0.0,0.0,0.0);
Vec3f shift1(0.0,0.0,0.0);
Vec3f shift2(0.0,0.0,0.0);

float theta = 0.0f;

const vec eye( 0.5f, 0.3f, -2.0f );
const vec centre( 0.0f, 0.0f, 0.0f );
const vec up( 0.0f, 1.0f, 0.0f );
const float SPHERE_RADIUS = 15.0f;


PlyReader pl;
PlyReader pl1;
PlyReader pl2;

SceneNode s1(NULL,0,NULL);
SceneNode s2(NULL,0,NULL);
SceneNode s3(NULL,0,NULL);

Controller::Controller(int argc,char** argv)
{
    pl.readFile(argv[1],argv[2]);
    pl1.readFile(argv[3],argv[4]);
    pl2.readFile(argv[5],argv[6]);

    s1 = SceneNode(&pl,0,const_cast<char*>("ply 1"));
    s2 = SceneNode(&pl1,1,const_cast<char*>("ply 2"));
    s3 = SceneNode(&pl2,2,const_cast<char*>("ply 3"));
    
    te = LoadGLTextures(const_cast<char*>("textures/floor.bmp"));

    s1.addChild(&s2);
}

void Controller::idle_callback()
{
    controller->idleFunc();
}

void Controller::idleFunc()
{

    x = 0.5*cos(theta);
    y = 0.5*sin(theta);
    count++;

    x = 0.8*sin(modelX);
    z = 0.8*cos(modelX);
    // float tempZ=

    Vec3f axis(0.0,2.0,0.0);
    modelY-=0.02f;


//tranformation on s2
    Rchildx = 0.2*cos(theta);
    Rchildy = 0.2*sin(theta);

    childx = 0.5*sin(modelX);
    childz = 0.5*cos(modelX);
    childy = 0.5;

    shift1.setval(childx, childy, childz);
    shift2.setval(Rchildx, Rchildy, Rchildz);

    s1.localTransform = s1.localTransform.Translation(shift);
    s1.localTransform = s1.localTransform.Rotation(axis,modelY)*s1.localTransform;


    s2.localTransform = s2.localTransform.Translation(shift2);
    s2.localTransform = s2.localTransform.Translation(shift1)*s2.localTransform;
    s2.localTransform = s2.localTransform.Rotation(axis,modelY)*s2.localTransform;

    if(y3<-.5 && y3>.5)
    {
        printf("inside the range\n");
        Model3 -= 0.05f;
    }
    else
    {
        printf("out side the rande\n");
        Model3 += 0.05f;
    }


    if(y<0)
    {
        y=-y;
    }
    if(childy<0)
        childy=-childy;

    theta+=speed1;
    modelX+=speed2;
    shift.setval(x, 0.0f, z);

    if(theta>=360)
    {
        theta=0;
    }
    


    s1.node -> init();


    if (count > 45 && count < 200) {

            printf("inside counter limit\n");
            if(!addChildRoot)
            {
                s2.addChild(&s3);
                addChildRoot=true;
            }

            // x3 = x * 0.8f;
            y3 = -0.5f;
            // z3 = z * 0.8f;

            if(count==50)
            {
                initX = x3;
                initZ = z3;
                printf("first commite position  x %f and z %f\n",x3 ,z3 );
            }

            if(count==200)
            {
                prevoiusX = x3;
                prevoiusZ = z3;

                printf("last position x %f and z %f\n",x3 ,z3 );
            }
            s3.localTransform = s3.localTransform.Translation(Vec3f(0.0, 0.0, z3));
        } else {

            printf("outside the limit\n");
            if (y3 < 0) {
                y3 = -y3;
            }
            // }
                if(count == 300 )
                {
                    count=0;
                }
                if(count ==  250)
                {
                    x3=-0.5;
                    y3=-0.5;
                }

                x3 += speed3;
                y3 = 0.5;
            

            if(addChildRoot)
            {
                s2.deleteChild(&s3);    
                addChildRoot = false;
            }
            
            s3.localTransform = s3.localTransform.Translation(Vec3f(x3, y3, z3));
            s3.drawSceneNode();
        }
    
        printf("here localTransform matric ------------------++++<<<<<<\n");
        s1.localTransform.printMatrix();

    float f = 0.0f;

     Vec3f eye;
    Matrix4 transform;
    Vec3f eye_coor;
  switch(camera)
    {
        case 0:
            arcball_rotate();
            break;
        case 1:
            eye.setval(1.5,1.5,1.5);
            printf("before eye coor x%f  y%f z%f \n", eye.x,eye.y,eye.z);
            transform=s3.getWorldTransform();
            // eye.x=x;
            // eye.z=z;
            // eye.y=x*y;
            transform.printMatrix();
            eye_coor=transform.multiVector(eye);
            // eye_coor.x=eye_coor.x*cos(theta);
            // eye_coor.z=eye_coor.y*sin(theta);
            eye_coor.x=-x;
            eye_coor.y = 0.2f; 
            eye_coor.z=-z;
            gluLookAt(eye_coor.x,eye_coor.y,eye_coor.z,0,0,0 ,0,1,0);
            break;
        case 2:
            eye_coor.x=-childx-Rchildx;
            eye_coor.y =-childy-Rchildy; 
            eye_coor.z=-childz-Rchildz;
            gluLookAt(eye_coor.x,eye_coor.y,eye_coor.z,0,0,0 ,0,1,0);
            break;

    }

    s1.drawSceneNode();


    glutPostRedisplay();

}

void Controller::display(){
    

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
     glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    Vec3f eye;
    Matrix4 transform;
    Vec3f eye_coor;

    light();
    switch(camera)
    {
        case 0:
            arcball_rotate();
            break;
        case 1:
            eye_coor.x=-x;
            eye_coor.y = 0.2f; 
            eye_coor.z=-z;
            gluLookAt(eye_coor.x,eye_coor.y,eye_coor.z,0,0,0 ,0,1,0);
            break;
        case 2:
            eye_coor.x=-childx-Rchildx;
            eye_coor.y =-childy-Rchildy; 
            eye_coor.z=-childz-Rchildz;
            gluLookAt(eye_coor.x,eye_coor.y,eye_coor.z,0,0,0 ,0,1,0);
            break;

    }

     glPushMatrix();
     GLuint myTexture;
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &myTexture);
    glBindTexture(GL_TEXTURE_2D, myTexture); //the title screen
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, te->sizeX, te->sizeY, 1, 
                        GL_RGB, GL_UNSIGNED_BYTE, te->data);
    glTranslatef (0.0, 0.98, 0.0);
    model->drawFloor();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
       
 
    glFlush();
    glutSwapBuffers();
}

void Controller::render_callback()
{
    controller->display();
}

void Controller::reshape_callback(int w,int h)
{
    v->resize(w,h);
}

void Controller::mouse_callback(int button,int stat,int x,int y)
{
    controller->mouseEventHandler(button,stat,x,y);
}

void Controller::motion_callback(int x,int y)
{
    controller->mouseMotion(x,y);
}

void Controller::keyboard_callback(unsigned char key,int x,int y)
{
    controller->keyboardEventHandler(key,x,y);
}

void Controller::specialKey_callback(int key,int x,int y)
{
    controller->specialKeyEventHandler(key,x,y);
}


//Mouse events handling
void Controller::mouseEventHandler(int button, int state,int x, int y){

    status = 10;
    if (button == 3) {
        scale = scale * 1.2;
    }

    if (button == 4) {
        scale = scale / (float)1.2;
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
        status = GLUT_LEFT_BUTTON;
        controller->click_scene(x,y);
    }

    //If right button is clicked clear or set all values to the default values
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        texV.setDistance(0.0);
        texV.setDistanceX(0.0);
        texV.setDistanceY(0.0);
        scale = 1.0;
	}
    glutPostRedisplay();
}

void Controller::mouseMotion (int x, int y) {

    if (status == GLUT_LEFT_BUTTON) {
        controller->drag_scene(x,y);
        x=texV.currentX;
        y=texV.currentY;
    }
    glutPostRedisplay();
}

void Controller::click_scene(int x, int y)
{
    arcball_start(-x,y);
}


void Controller::drag_scene(int x, int y)
{
    arcball_move(-x,y);
}

void Controller::keyboardEventHandler(unsigned char key, int x, int y){

    if(key == 'x') {
        spin = 'x';
        xangle = xangle + 15;
    } else if(key == 'y') {
        spin = 'y';
        yangle = yangle + 15;
    } else if(key == 'z') {
        spin = 'z';
        zangle = zangle + 15;
    } else if(key == '1') {
        updateLight(0);
    } else if(key == '2') {
        updateLight(1);
    } else if(key == '3') {
        updateLight(2);
    } else if(key == '4') {
        updateLight(3);
    }
    else if(key == 'c'||key == 'C')
    {
        camera=(++camera)%3;
    }
    else if(key == 'l' || key == 'L')
    {
        speed1 +=0.05f;
    }else if(key == 'k' || key == 'K')
    {
        speed1 -=0.05f;
    }
    else if(key == 'm' || key == 'M')
    {
        speed2 +=0.02f;
    }else if(key == 'n' || key == 'N')
    {
        speed2 -=0.02f;
    }
    else if(key == 'p' || key == 'P')
    {
        speed3 +=0.002f;
    }else if(key == 'o' || key == 'O')
    {
        speed3 -=0.002f;
    }
    else if(key==27)
    {
        exit(0);
    }
    glutPostRedisplay();
}

void Controller::specialKeyEventHandler(int key,int x,int y){

    if(key == GLUT_KEY_UP){
        texV.setDistanceY(texV.getDistanceY() + 0.1);
    }
    else if(key == GLUT_KEY_DOWN){
        texV.setDistanceY(texV.getDistanceY() - 0.1);
    }
    else if(key == GLUT_KEY_RIGHT){
        texV.setDistanceX(texV.getDistanceX() + 0.1);
    }
    else if(key == GLUT_KEY_LEFT){
        texV.setDistanceX(texV.getDistanceX() - 0.1);
    }
    glutPostRedisplay();
}

void Controller::resize(int w, int h) {

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

    // texture[0] = LoadGLTextures("textures/brickwall.bmp");
    // texture[1] = LoadGLTextures("textures/world.bmp");
    // texture[2] = LoadGLTextures("textures/apple.bmp");
}


//Getters and Setters to use from other classes.
float Controller::getScale(){
    return scale;
}

char Controller::getSpin(){
    return spin;
}

void Controller::light(){
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
        glEnable(GL_LIGHT2);
    } else {
        glDisable(GL_LIGHT2);
    }
    if (lightList[3]) {
        glEnable(GL_LIGHT3);
    } else {
        glDisable(GL_LIGHT3);
    }
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_NORMALIZE);
}

void Controller::updateLight (int index) {
    lightList[index] = !lightList[index];
}
