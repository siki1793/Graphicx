// Assignment 2 -  Transformation and OpenGL Interaction 
// Alark Joshi
// 
// Please go through the file first and write the matrix multiplication function first. 
// You CANNOT compile the program without writing the matrix multiplication function. 


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <GL/glut.h>

float xpos =0.0, ypos =0.0; 
float zoomin = 0.0; 

float modelview[16];

#define OBJSIZE 50000

float vArr[OBJSIZE][3], nArr[OBJSIZE][3], tArr[OBJSIZE][3];
int fArr[OBJSIZE][9];

int vcounter = 0, ncounter =0, tcounter =0, fcounter =0; 

// Axes for rotation 
#define X_AXIS                  0
#define Y_AXIS                  1
#define Z_AXIS                  2

typedef float vec3_t[3];  // vec3_t for rotation

static int f1, f2; 

typedef struct{
	float x,y,z;       // vector component x,y,z
} vector;


/* enumerations for the mouse buttons */
enum {
    UP = 1, 
    DOWN, 
};

float translatex = 0.0; 

/* old position of the mouse */
int oldX = -13;
int oldY = -13;

/* mouse state, UP or DOWN */
int mState = UP;
int rightmouse = UP; 
int middleButton = UP; 

/* current axis of rotation */
int axisRot = X_AXIS;

/* amount to rotate about axis */
float rotate = 0.0f;

/* vector which describes the axis to rotate about */
vec3_t axis = {1.0, 0.0, 0.0};

/* global rotation, for use with the mouse */
vec3_t gRot = {0,0,0};


// This function is called whenever a "Normal" key press is received.
void keyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;

	case 'X':
		translatex += 0.1;
		printf("\ntranslatex is %f\n", translatex);
		glutPostRedisplay(); 
		break; 

	case 'x':
		translatex -= 0.1;
		printf("\ntranslatex is %f\n", translatex);
		glutPostRedisplay(); 
		break; 

	default:
        printf("Unhandled key press \n", key );
        
    }
}

// This function is called whenever a "Special" key press is received.
// Right now, it's handling the arrow keys.
void specialFunc( int key, int x, int y )
{
    switch ( key )
    {
    case GLUT_KEY_UP:		
        printf("Up arrow.\n"); 
		ypos+= 0.5;
		glutPostRedisplay();
		break;
    case GLUT_KEY_DOWN:
        printf("Down arrow.\n"); 
		ypos-= 0.5;
		glutPostRedisplay();
		break;
    case GLUT_KEY_LEFT:
        printf("Left arrow.\n"); 
		xpos+=0.5;
		glutPostRedisplay();
		break;
    case GLUT_KEY_RIGHT:
		printf("Right arrow.\n"); 
		xpos-=0.5; 
		glutPostRedisplay();
		break;
    }
}

// You need to uncomment this and implement matrix multiplication in this function 
void matrix_multiply (float a[4][4], float b[4][4], float result[4][4])
{
	// Implement matrix multiplication function here. 

}



// My version of Translation transform being implemented using homogeneous coordinates.
void myglTranslatef()
{
	// Important: Remember that OpenGL stores the matrix as column major and NOT row major
	// That means that the transformation matrix 
	// |1 0 0 translatex |
	// |0 1 0 0 |
	// |0 0 1 0 |
	// |0 0 0 1 |
	// is written in OpenGL as 
	float transformation_matrix[4][4] = {{1.0, 0.0, 0.0, 0.0}, 
										 {0.0, 1.0, 0.0, 0.0},
										 {0.0, 0.0, 1.0, 0.0},
										 {translatex, 0.0, 0.0, 1.0}};

	float resultant_matrix[4][4]; 

	float modelview_2[4][4];
	
	int counter = 0; 
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			modelview_2[i][j] = modelview[counter];
			counter++;

			// initialize resultant_matrix 
			resultant_matrix[i][j] = 0.0;
		}
	}

	// Implement your own matrix multiplication routine
	matrix_multiply(modelview_2, transformation_matrix, resultant_matrix); 

	counter = 0; 
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			modelview[counter] = resultant_matrix[i][j];
			counter++;
		}
	}	

}

// This function is responsible for displaying the object.
void drawScene(void)
{
    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate the image
    glMatrixMode( GL_MODELVIEW );  // Current matrix affects objects positions
    glLoadIdentity();              // Initialize to the identity

    // Position the camera at [0,0,5], looking at [0,0,0],
    // with [0,1,0] as the up direction.
    gluLookAt(5.0, 5.0, 15.0+zoomin,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

	glLineWidth(1.0); 

	glBegin(GL_LINES); 

		// X-axis 
		glColor3f(1, 0, 0); 
		glVertex3f(-5.0, 0.0, 0.0);
		glVertex3f(5.0, 0.0, 0.0);

		// Y-axis 
		glColor3f(0, 1, 0); 
		glVertex3f(0.0, -5.0, 0.0);
		glVertex3f(0.0, 5.0, 0.0);

		//Z-axis
		glColor3f(0, 0, 1); 
		glVertex3f(0.0, 0.0, -5.0);
		glVertex3f(0.0, 0.0, 5.0);

	glEnd(); 

	
	// Replace the following 3-glRotatef's with your own function - myGLRotatef(angle, x, y, z)
	glRotatef(-gRot[0], 1.0, 0.0, 0.0);
	glRotatef(-gRot[1], 0.0, 1.0, 0.0);
	glRotatef(-gRot[2], 0.0, 0.0, 1.0);

	//	 save the current modelview matrix
	glGetFloatv(GL_MODELVIEW_MATRIX , modelview);
	
	// Uncomment this line after you have implemented the matrix multiplication function.
	//myglTranslatef(); 
	
	glLoadMatrixf(modelview);

	glColor3f(0.0f, 0.5f, .2f); 

	glBegin(GL_TRIANGLES);
	for(int i=0;i<fcounter;i++)
	{
		glVertex3d(vArr[fArr[i][0]-1][0], vArr[fArr[i][0]-1][1], vArr[fArr[i][0]-1][2]);
		glVertex3d(vArr[fArr[i][3]-1][0], vArr[fArr[i][3]-1][1], vArr[fArr[i][3]-1][2]);
		glVertex3d(vArr[fArr[i][6]-1][0], vArr[fArr[i][6]-1][1], vArr[fArr[i][6]-1][2]);
	}
	glEnd();


    // Dump the image to the screen.
    glutSwapBuffers();


}

// Initialize OpenGL's rendering modes
void initRendering()
{

	glClearColor(1.0, 1.0, 1.0, 1.0);

    glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on

	FILE *fp = fopen("gargoyle.obj","rb"); // Name of the input object file

	if(fp==NULL)
	{
		printf("File not found. Please check the path of the input model file. Exiting.\n");
		exit(0); 
	}

	char *c1 = new char[5]; 

	char str[100]; 
	
	// skip comments embedded in header
    fgets(str,100,fp);  

	do
	{
		fgets(str,100,fp);
	}while(str[0]!='g');	


	while(!feof(fp))
	{
		fscanf(fp, "%s", c1);
		if(strcmp(c1, "v")==0)
		{
			fscanf(fp, "%f %f %f\n", &vArr[vcounter][0], &vArr[vcounter][1], &vArr[vcounter][2]); 
			vcounter++; 
		} 
		else if(strcmp(c1, "vt")==0)
		{		
			fscanf(fp, "%f %f %f\n", &tArr[tcounter][0], &tArr[tcounter][1], &tArr[tcounter][2]); 
			tcounter++; 			
		}
		else if(strcmp(c1, "vn") == 0)
		{
			fscanf(fp, "%f %f %f\n", &nArr[ncounter][0], &nArr[ncounter][1], &nArr[ncounter][2]); 
			ncounter++; 
		}
		else if(strcmp(c1, "f") == 0)
		{
			fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &fArr[fcounter][0], &fArr[fcounter][1], &fArr[fcounter][2],  
													   &fArr[fcounter][3], &fArr[fcounter][4], &fArr[fcounter][5], 
													   &fArr[fcounter][6], &fArr[fcounter][7], &fArr[fcounter][8]); 
			fcounter++;
		}
		else
			fgets(str,100,fp);

	}

	printf("Number of vertices in this model: %d\n", vcounter); 
	fclose(fp); 

}

// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshapeFunc(int w, int h)
{
    // Always use the largest square viewport possible
    if (w > h) {
        glViewport((w - h) / 2, 0, h, h);
    } else {
        glViewport(0, (h - w) / 2, w, w);
    }

    // Set up a perspective view, with square aspect ratio
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 50 degree fov, uniform aspect ratio, near = 1, far = 100
    gluPerspective(50.0, 1.0, 1.0, 100.0);
}

// Method to clamp the angle of rotation between 0 and 360
void clamp_angle (vec3_t v)
{
    int i;

    for (i = 0; i < 3; i ++)
        if (v[i] > 360 || v[i] < -360)
            v[i] = 0.0f;
}


//Called when the mouse moves in our app area. 
void glutMotion(int x, int y) 
{
    if (mState == DOWN) 
    {
        gRot[0] -= ((oldY - y) * 180.0f) / 360.0f;
        gRot[1] -= ((oldX - x) * 180.0f) / 360.0f;
        clamp_angle (gRot);
        glutPostRedisplay ();
    } 
	 if (rightmouse == DOWN) 
    {
    	gRot[2] -= ((oldX - x) * 180.0f) / 360.0f;
        clamp_angle (gRot);
        glutPostRedisplay ();
    } 
	if(middleButton == DOWN)
	{
		zoomin+= oldY-y;
		if(zoomin <-3.0)
			zoomin = -3.0; 
		
		glutPostRedisplay(); 
	}
    oldX = x; 
    oldY = y;
}


//	glutMouse - called when the mouse is clicked  
// 
//  The Left mouse button is used for rotation around the X and Y axes
//  and the Right mouse button is used for rotation around the Z axis 
//
//  Left Mouse Button and Horizontal movement = rotation in X direction 
//  Left Mouse Button and Vertical movement = rotation in X direction 
//  Right Mouse Button and Horizontal movement = rotation in Z direction 
//  Middle Mouse Button and Vertical movement = zoom in and out 

void glutMouse(int button, int state, int x, int y) 
{
    if(state == GLUT_DOWN) 
    {
        switch(button) 
        {
            case GLUT_LEFT_BUTTON:				
				mState = DOWN;
                oldX = x;
                oldY = y;
				break;

            case GLUT_RIGHT_BUTTON:				
                rightmouse = DOWN;
                oldX = x;
                oldY = y;
            break;

			case GLUT_MIDDLE_BUTTON:
				middleButton = DOWN;
				oldX = x;
                oldY = y;
				break; 
        }
    } else if (state == GLUT_UP) 
	{
        mState = UP; rightmouse= UP; 
		middleButton = UP; 
	}
}
 


// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
    glutInit(&argc,argv);

    // We're going to animate it, so double buffer 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Initial parameters for window position and size
    glutInitWindowPosition( 60, 60 );
    glutInitWindowSize( 360, 360 );
    glutCreateWindow("Assignment 2");

    // Initialize OpenGL parameters.
    initRendering();

    // Set up callback functions for key presses
    glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys

     // Set up the callback function for resizing windows
    glutReshapeFunc( reshapeFunc );

    // Call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

	glutMouseFunc(glutMouse);
    glutMotionFunc (glutMotion);

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );

    return 0;	
}
