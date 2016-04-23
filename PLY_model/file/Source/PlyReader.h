#ifndef PLYREADER_H
#define PLYREADER_H
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "rply.h"
#define INF 100000007
static int vi=0,vj=0,fi=0,fj=0;


class PlyReader{
    private:

    public:
        void ReadFile();
        int getNoOfFaces();
        float getVertices(int ,int );
        int getFaces(int ,int );
        void getNormal( int );
        float getNormals(int , int);
        float getV(int ,int );
        float getxMin();
        float getyMin();
        float getzMin();
        float getxMax();
        float getyMax();
        float getzMax();
        static int vertex_cb(p_ply_argument argument);
        static int face_cb(p_ply_argument argument);
        static int read_vertex_cb(p_ply_argument argument);
        static int read_face_cb(p_ply_argument argument);
        static long noOfVertices,noOfFaces;
        static float **vertices;
        static int **faces;
        static float **normals,**v;
//        float xMin,xMax,yMin,yMax,zMin,zMax;
        FILE *fp;


};
#endif
