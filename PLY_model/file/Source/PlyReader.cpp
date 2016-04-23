#include "PlyReader.h"

long PlyReader::noOfVertices,PlyReader::noOfFaces;
float **PlyReader::vertices;
int **PlyReader::faces;
float **PlyReader::normals,**PlyReader::v;

float xMin=INF;
float yMin=INF;
float zMin=INF;

float xMax=0;
float yMax=0;
float zMax=0;


int PlyReader::vertex_cb(p_ply_argument argument) {
    long eol;
    ply_get_argument_user_data(argument, NULL, &eol);
    long length, value_index;
    ply_get_argument_property(argument, NULL, &length, &value_index);
    vertices[vi][vj]=ply_get_argument_value(argument);
   if (eol)
  {
    vi++;
    vj=0;
  }
  else{
     vj++;
  }
    return 1;
}

int PlyReader::face_cb(p_ply_argument argument) {
    long length, value_index;
    ply_get_argument_property(argument, NULL, &length, &value_index);
    switch (value_index) {
        case 0:
            faces[fi][fj]=ply_get_argument_value(argument);
            fj++;
            break;
        case 1:
            faces[fi][fj]=ply_get_argument_value(argument);
            fj++;
            break;
        case 2:
            faces[fi][fj]=ply_get_argument_value(argument);
            fi++;
            fj=0;
            break;
        default:
            break;
    }
    return 1;
}

void PlyReader::ReadFile(void){
    int i,j;

    p_ply ply = ply_open("../bunny.ply", NULL, 0, NULL);
    if (!ply) return;
    if (!ply_read_header(ply)) return;
    noOfVertices= ply_set_read_cb(ply, "vertex", "x", vertex_cb, NULL, 0);
    //noOfVertices= ply_set_read_cb(ply, "vertex", "x", vertex_cb, NULL, 0);
    //memory allocation for vertices
    vertices= (float **)malloc(noOfVertices * sizeof(float *));

    for (i=0; i<noOfVertices; i++)
        vertices[i] = (float *)malloc(3 * sizeof(float));
    ply_set_read_cb(ply, "vertex", "y", vertex_cb, NULL, 0);
    ply_set_read_cb(ply, "vertex", "z", vertex_cb, NULL, 1);
    noOfFaces = ply_set_read_cb(ply, "face", "vertex_indices", face_cb, NULL, 0);

    //memory allocation for faces
    faces= (int **)malloc(noOfFaces * sizeof(int *));

    for (i=0; i<noOfFaces ; i++)
        faces[i] = (int *)malloc(3 * sizeof(int));

    normals= (float **)malloc((noOfFaces) * sizeof(float *));
    for (i=0; i<noOfFaces; i++)
      normals[i] = (float *)malloc(3 * sizeof(float));

    v= (float **)malloc((noOfFaces) * sizeof(float *));
    for (i=0; i<noOfFaces; i++)
      v[i] = (float *)malloc(4 * sizeof(float));

    printf("vertices : %ld\nfaces : %ld\n", noOfVertices, noOfFaces);
    if (!ply_read(ply)) return;
    ply_close(ply);
    printf ("%lf\n", vertices[0][0]);
    printf ("%d\n", faces[0][0]);
    printf ("last-------%lf\n", vertices[noOfVertices-1][0]);
    printf ("last-------%d\n", faces[noOfFaces-1][0]);
    for(int i = 0; i < noOfFaces; i++){
        PlyReader::getNormal(i);
        //printf("%d\n",i );
    }
    for (i=0; i<noOfVertices; i++)
    {
        xMin=std::min(vertices[i][0],xMin);
        xMax=std::max(vertices[i][0],xMax);
        yMin=std::min(vertices[i][1],yMin);
        yMax=std::max(vertices[i][1],yMax);
        zMin=std::min(vertices[i][2],zMin);
        zMax=std::max(vertices[i][2],zMax);
    }

    std::cout<<"x min"<<xMin<<"y min"<<yMin<<"z min"<<zMin<<"x"<<xMax<<"y"<<yMax<<"z"<<zMax<<std::endl;
}
void PlyReader::getNormal( int fc){
    float va[3], vb[3], vr[3], length;

   // find vector
   va[0] = vertices[faces[fc][0]][0] - vertices[faces[fc][1]][0];
   va[1] = vertices[faces[fc][0]][1] - vertices[faces[fc][1]][1];
   va[2] = vertices[faces[fc][0]][2] - vertices[faces[fc][1]][2];

   vb[0] = vertices[faces[fc][2]][0] - vertices[faces[fc][1]][0];
   vb[1] = vertices[faces[fc][2]][1] - vertices[faces[fc][1]][1];
   vb[2] = vertices[faces[fc][2]][2] - vertices[faces[fc][1]][2];

   //  cross product
   vr[0] = va[1] * vb[2] - vb[1] * va[2];
   vr[1] = vb[0] * va[2] - va[0] * vb[2];
   vr[2] = va[0] * vb[1] - vb[0] * va[1];

   // find normalization factor
   length = sqrt( vr[0]*vr[0] + vr[1]*vr[1] + vr[2]*vr[2] );

	normals[fc][0] = vr[0]/length;
	normals[fc][1] = vr[1]/length;
	normals[fc][2] = vr[2]/length;

	//for averaging and per pixel shading
	v[faces[fc][0]][0]+=normals[fc][0];
	v[faces[fc][1]][0]+=normals[fc][0];
	v[faces[fc][2]][0]+=normals[fc][0];

	v[faces[fc][0]][1]+=normals[fc][1];
	v[faces[fc][1]][1]+=normals[fc][1];
 	v[faces[fc][2]][1]+=normals[fc][1];

	v[faces[fc][0]][2]+=normals[fc][2];
	v[faces[fc][1]][2]+=normals[fc][2];
	v[faces[fc][2]][2]+=normals[fc][2];

	v[faces[fc][0]][3]+=1.0;
	v[faces[fc][1]][3]+=1.0;
 	v[faces[fc][2]][3]+=1.0;
}

int PlyReader::getNoOfFaces(){
    return noOfFaces;
}
float PlyReader::getVertices(int i,int j){
    return vertices[i][j];
}
int PlyReader::getFaces(int i,int j){
    return faces[i][j];
}
float PlyReader::getNormals(int i,int j){
    return normals[i][j];
}
float PlyReader::getV(int i,int j){
    return v[i][j];
}

float PlyReader::getxMin()
{
    return xMin;
}

float PlyReader::getyMin()
{
    return yMin;
}

float PlyReader::getzMin()
{
    return zMin;
}

float PlyReader::getxMax()
{
    return xMax;
}

float PlyReader::getyMax()
{
    return yMax;
}

float PlyReader::getzMax()
{
    return zMax;
}
