/*
 * Solution for project 2 of the course CEG476/676 taught by Thomas
 * Wischgoll.
 *
 * This solution kept simple and can be used as starting point for the
 * following projects. It creates a top, side, and front view of the
 * geometry retreived from a ply file using Greg Turk's ply reader.
 *
 * Thomas Wischgoll, November 2010.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>


#include "ply.h"

int width, height;

// ply vertices and faces
Vertex **vlist;
Face **flist;
int num_elems;

float sliderx, slidery, sliderz;

void init () {
  // set the clear color (black)
  glClearColor(0.0, 0.0, 0.0, 0.0);

  sliderx = slidery = sliderz = 0.0;
}

void reshape (int w, int h) {
  // store width and height for later (see display function)
  width = w;
  height = h;
}

void draw () {
  // draw the entire geometry by looping through the faces which in
  // turn reference the vertices
  for (int j=0; j<num_elems; j++) {
    glBegin (GL_POLYGON);
    for (int k = 0; k < flist[j]->nverts; k++)
      glVertex3f (vlist[flist[j]->verts[k]]->x,
		  vlist[flist[j]->verts[k]]->y,
		  vlist[flist[j]->verts[k]]->z);
    glEnd ();
  }
}

void display () {
  float location;

  // reset frame and depth buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draw lower left view (sliders)
  glViewport (0, 0,
	      (GLsizei) width, (GLsizei) height);
  // set the projection to match word COS and display COS
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity ();
  gluOrtho2D (0.0, width, 0.0, height);

  // set matrix mode back to modelview
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();

  glColor3f (1.0, 1.0, 1.0);
  // draw slider boxes
  glBegin (GL_LINE_LOOP);
  glVertex2f (width/2+5, height/8 - 5);
  glVertex2f (width/2+5, height/8 + 5);
  glVertex2f (width-5, height/8 + 5);
  glVertex2f (width-5, height/8 - 5);
  glEnd ();
  glBegin (GL_LINE_LOOP);
  glVertex2f (width/2+5, height/4 - 5);
  glVertex2f (width/2+5, height/4 + 5);
  glVertex2f (width-5, height/4 + 5);
  glVertex2f (width-5, height/4 - 5);
  glEnd ();
  glBegin (GL_LINE_LOOP);
  glVertex2f (width/2+5, 3*height/8 - 5);
  glVertex2f (width/2+5, 3*height/8 + 5);
  glVertex2f (width-5, 3*height/8 + 5);
  glVertex2f (width-5, 3*height/8 - 5);
  glEnd ();
  // draw slider markers
  glBegin (GL_QUADS);
  location = (width/2-20)*sliderx/360.0;
  glVertex2f (width/2+10+location+5, height/8 - 5);
  glVertex2f (width/2+10+location+5, height/8 + 5);
  glVertex2f (width/2+10+location-5, height/8 + 5);
  glVertex2f (width/2+10+location-5, height/8 - 5);
  glEnd ();
  glBegin (GL_QUADS);
  location = (width/2-20)*slidery/360.0;
  glVertex2f (width/2+10+location+5, height/4 - 5);
  glVertex2f (width/2+10+location+5, height/4 + 5);
  glVertex2f (width/2+10+location-5, height/4 + 5);
  glVertex2f (width/2+10+location-5, height/4 - 5);
  glEnd ();
  glBegin (GL_QUADS);
  location = (width/2-20)*sliderz/360.0;
  glVertex2f (width/2+10+location+5, 3*height/8 - 5);
  glVertex2f (width/2+10+location+5, 3*height/8 + 5);
  glVertex2f (width/2+10+location-5, 3*height/8 + 5);
  glVertex2f (width/2+10+location-5, 3*height/8 - 5);
  glEnd ();

  // we draw everything in red for now
  glColor3f (1.0, 0.0, 0.0);

  // set the projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective( 65.0, (GLfloat) width / height,
		  1.0, 100.0 );

  // set matrix mode back to modelview
  glMatrixMode (GL_MODELVIEW);

  // create upper left view (top)
  glViewport (0, (GLsizei) height/2,
	      (GLsizei) width/2, (GLsizei) height/2);
  glLoadIdentity ();
  gluLookAt (0.0, 5.0, 0.0,
	     0.0, 0.0, 0.0,
	     0.0, 0.0, 1.0);
  glRotatef (sliderx, 1.0, 0.0, 0.0);
  glRotatef (slidery, 0.0, 1.0, 0.0);
  glRotatef (sliderz, 0.0, 0.0, 1.0);
  draw ();

  // draw upper right view (side)
  glViewport ((GLsizei) width/2, (GLsizei) height/2,
	      (GLsizei) width/2, (GLsizei) height/2);
  glLoadIdentity();
  gluLookAt (5.0, 0.0, 0.0,
	     0.0, 0.0, 0.0,
	     0.0, 1.0, 0.0);
  glRotatef (sliderx, 1.0, 0.0, 0.0);
  glRotatef (slidery, 0.0, 1.0, 0.0);
  glRotatef (sliderz, 0.0, 0.0, 1.0);
  draw ();

  // draw lower left view (front)
  glViewport (0, 0,
	      (GLsizei) width/2, (GLsizei) height/2);
  glLoadIdentity();
  gluLookAt (0.0, 0.0, 5.0,
	     0.0, 0.0, 0.0,
	     0.0, 1.0, 0.0);
  glRotatef (sliderx, 1.0, 0.0, 0.0);
  glRotatef (slidery, 0.0, 1.0, 0.0);
  glRotatef (sliderz, 0.0, 0.0, 1.0);
  draw ();

  // swap buffers since we are using double buffering
  glutSwapBuffers ();
  // flush just in case
  glFlush ();
}

void parsekey (unsigned char key, int x, int y)
{
  switch (key)
    {
    case 27: exit(0); break;
    }
}

void motion (int x, int mousey)
{
  int y = height - mousey;

  if (x > width/2+10 && x < width-10) {
    if (y > height/8-5 && y < height/8+5) {
      // we are moving the slider for x
      sliderx = (x - (width/2+10))*360.0/(width/2-20);
      if (sliderx < 0.0)
	sliderx = 0.0;
      if (sliderx > 360.0)
	sliderx = 360.0;
      glutPostRedisplay ();
    }
    else if (y > height/4-5 && y < height/4+5) {
      // we are moving the slider for y
      slidery = (x - (width/2+10))*360.0/(width/2-20);
      if (slidery < 0.0)
	slidery = 0.0;
      if (slidery > 360.0)
	slidery = 360.0;
      glutPostRedisplay ();
    }
    else if (y > 3*height/8-5 && y < 3*height/8+5) {
      // we are moving the slider for z
      sliderz = (x - (width/2+10))*360.0/(width/2-20);
      if (sliderz < 0.0)
	sliderz = 0.0;
      if (sliderz > 360.0)
	sliderz = 360.0;
      glutPostRedisplay ();
    }
  }
}

void mouse (int button, int state, int x, int y)
{
  // just call the motion function here as it does all we need
  motion (x, y);
}

/******************************************************************************
Read in a PLY file.
******************************************************************************/

void read_test(char *filename)
{
  int i,j,k;
  PlyFile *ply;
  int nelems;
  char **elist;
  int file_type;
  float version;
  int nprops;
  PlyProperty **plist;
  char *elem_name;
  int num_comments;
  char **comments;
  int num_obj_info;
  char **obj_info;

  /* open a PLY file for reading */
  ply = ply_open_for_reading(filename, &nelems, &elist, &file_type, &version);

#ifdef DEBUG
  /* print what we found out about the file */
  printf ("version %f\n", version);
  printf ("type %d\n", file_type);
#endif

  /* go through each kind of element that we learned is in the file */
  /* and read them */

  for (i = 0; i < nelems; i++) {

    /* get the description of the first element */
    elem_name = elist[i];
    plist = ply_get_element_description (ply, elem_name, &num_elems, &nprops);

#ifdef DEBUG
    /* print the name of the element, for debugging */
    printf ("element %s %d\n", elem_name, num_elems);
#endif

    /* if we're on vertex elements, read them in */
    if (equal_strings ("vertex", elem_name)) {

      /* create a vertex list to hold all the vertices */
      vlist = (Vertex **) malloc (sizeof (Vertex *) * num_elems);

      /* set up for getting vertex elements */

      ply_get_property (ply, elem_name, &vert_props[0]);
      ply_get_property (ply, elem_name, &vert_props[1]);
      ply_get_property (ply, elem_name, &vert_props[2]);

      /* grab all the vertex elements */
      for (j = 0; j < num_elems; j++) {

        /* grab and element from the file */
        vlist[j] = (Vertex *) malloc (sizeof (Vertex));
        ply_get_element (ply, (void *) vlist[j]);

#ifdef DEBUG
        /* print out vertex x,y,z for debugging */
        printf ("vertex: %g %g %g\n", vlist[j]->x, vlist[j]->y, vlist[j]->z);
#endif
      }
    }

    /* if we're on face elements, read them in */
    if (equal_strings ("face", elem_name)) {

      /* create a list to hold all the face elements */
      flist = (Face **) malloc (sizeof (Face *) * num_elems);

      /* set up for getting face elements */

      ply_get_property (ply, elem_name, &face_props[0]);
      ply_get_property (ply, elem_name, &face_props[1]);

      /* grab all the face elements */
      for (j = 0; j < num_elems; j++) {

        /* grab and element from the file */
        flist[j] = (Face *) malloc (sizeof (Face));
        ply_get_element (ply, (void *) flist[j]);

#ifdef DEBUG
        /* print out face info, for debugging */
        printf ("face: %d, list = ", flist[j]->intensity);
        for (k = 0; k < flist[j]->nverts; k++)
          printf ("%d ", flist[j]->verts[k]);
        printf ("\n");
#endif
      }
    }

#ifdef DEBUG
    /* print out the properties we got, for debugging */
    for (j = 0; j < nprops; j++)
      printf ("property %s\n", plist[j]->name);
#endif
  }

  /* grab and print out the comments in the file */
  comments = ply_get_comments (ply, &num_comments);
#ifdef DEBUG
  for (i = 0; i < num_comments; i++)
    printf ("comment = '%s'\n", comments[i]);
#endif

  /* grab and print out the object information */
  obj_info = ply_get_obj_info (ply, &num_obj_info);
#ifdef DEBUG
  for (i = 0; i < num_obj_info; i++)
    printf ("obj_info = '%s'\n", obj_info[i]);
#endif

  /* close the PLY file */
  ply_close (ply);
}

int main (int argc, char **argv) {

  // read the ply file
  if (argc == 2)
    read_test (argv[1]);
  else
    read_test ("icosahedron.ply");

  // initialize GLUT and create window
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (400, 300);
  glutCreateWindow ("Project 0");

  // enable the depth testing
  glEnable(GL_DEPTH_TEST);

  init ();

  // set display callback
  glutDisplayFunc (display);
  // set resize callback
  glutReshapeFunc (reshape);
  // set key-press callback
  glutKeyboardFunc (parsekey);
  // set the mouse motion function
  glutMotionFunc (motion);
  // set the mouse motion function
  glutMouseFunc (mouse);

  // enter GLUT's main loop
  glutMainLoop();

  return 0;
}
