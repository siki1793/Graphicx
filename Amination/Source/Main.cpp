#include <GL/glut.h>
#include <GL/glext.h>
#include <string>
#include "Controller.h"
#include "Model.h"
#include "View.h"

int SCREEN_WIDTH=1200;
int SCREEN_HEIGHT=700;

using namespace std;

void init();

// PlyReader Model::pl;
// PlyReader Model::pl1;
View *view;
Controller *c;
int main(int argc, char** argv) {

    if (argc < 3) {
        printf("format : ./assign4 <ply file1 path> <ply file2 path>\n");
        return 0;
    }

    // Model::pl.readFile(argv[1]);

    // Model::pl1.readFile(argv[2]);

    c=new Controller(argc,argv);

    glutInit(&argc, argv);
    view->init(SCREEN_WIDTH,SCREEN_HEIGHT);

    //Mouse event controller
    glutMouseFunc(Controller::mouse_callback);
    glutMotionFunc (Controller::motion_callback);

    //Keyboard Event Controller
    glutKeyboardFunc(Controller::keyboard_callback);
    glutSpecialFunc(Controller::specialKey_callback);

    //Display function
    glutIdleFunc(Controller::idle_callback);
    glutReshapeFunc(Controller::reshape_callback);
    glutDisplayFunc(Controller::render_callback);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glutMainLoop();

    return 0;
}

