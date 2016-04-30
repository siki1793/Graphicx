#ifndef PLYREADER_H
#define PLYREADER_H

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "ply.h"
// #include "Vector.h"
#include <limits.h>
#include <GL/glu.h>
// #include <data.h>




class PlyReader{

public:
    typedef struct Vertex {
        float x,y,z;             /* the usual 3-space position of a vertex */
    } Vertex;

    typedef struct Vector {
        float x,y,z;             /* the usual 3-space position of a vertex */
    } Vector;

    typedef struct Face {
      unsigned char intensity; /* this user attaches intensity to faces */
      unsigned char nverts;    /* number of vertex indices in list */
      int *verts;              /* vertex index list */
    } Face;

	char* elem_names[2];

    PlyProperty vert_props[3];
    PlyProperty face_props[2];

PlyReader();

void readFile(char *);
int getNoOfFaces(void);
Face ** getFace(void);
Vertex ** getVertex(void);
unsigned char getFacesVertices(int);
int getNoOfVertices(void);
void setNoOfVertices(int);
void setNoOfFaces(int);
void getNormals(int);
float getNormal(int,int);
float getFaces(int,int);
float getVertices(int,int);
void Centroid(void);
float scalePly(float);
void setCentroid(float,int);
float getCentroid(int);
void setXMax(float value);
void setYMax(float value);
void setZMax(float value);
void setXMin(float value);
void setYMin(float value);
void setZMin(float value);
float getXMax(void);
float getYMax(void);
float getZMax(void);
float getXMin(void);
float getYMin(void);
float getZMin(void);

private:

float xMax,yMax,zMax;
float xMin,yMin,zMin;


int noOfVertices;
int noOfFaces;

float centroid[3];

PlyFile *ply;
int nelems;
char **elist;
int file_type;
float version;
int nprops;
int num_elems;
PlyProperty **plist;
Vertex **vertices;
Vertex **v;
Face **faces;
Vector **normals;
char *elem_name;
int num_comments;
char **comments;
int num_obj_info;
char **obj_info;


};


#endif





