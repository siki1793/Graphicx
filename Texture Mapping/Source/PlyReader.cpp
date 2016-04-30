#include "PlyReader.h"


PlyReader::PlyReader(void)
{

    noOfVertices=0;

    noOfFaces=0;

    centroid[0]=0.0;
    centroid[1]=0.0;
    centroid[2]=0.0;

/* list of the kinds of elements in the user's object */
    elem_names[0]=(char*)"vertex";
    elem_names[1]=(char*)"face";


/* list of property information for a vertex */

    //vertices x
    vert_props[0].name=(char*)"x";
    vert_props[0].external_type=PLY_FLOAT;
    vert_props[0].internal_type=PLY_FLOAT;
    vert_props[0].offset=offsetof(Vertex,x);
    vert_props[0].is_list=0;
    vert_props[0].count_external=0;
    vert_props[0].count_internal=0;
    vert_props[0].count_offset=0;

    //vertices y
    vert_props[1].name=(char*)"y";
    vert_props[1].external_type=PLY_FLOAT;
    vert_props[1].internal_type=PLY_FLOAT;
    vert_props[1].offset=offsetof(Vertex,y);
    vert_props[1].is_list=0;
    vert_props[1].count_external=0;
    vert_props[1].count_internal=0;
    vert_props[1].count_offset=0;

    //vertices z
    vert_props[2].name=(char*)"z";
    vert_props[2].external_type=PLY_FLOAT;
    vert_props[2].internal_type=PLY_FLOAT;
    vert_props[2].offset=offsetof(Vertex,z);
    vert_props[2].is_list=0;
    vert_props[2].count_external=0;
    vert_props[2].count_internal=0;
    vert_props[2].count_offset=0;


    /* list of property information for a vertex */

    face_props[0].name=(char*)"intensity";
    face_props[0].external_type=PLY_UCHAR;
    face_props[0].internal_type=PLY_UCHAR;
    face_props[0].offset=offsetof(Face,intensity);
    face_props[0].is_list=0;
    face_props[0].count_external=0;
    face_props[0].count_internal=0;
    face_props[0].count_offset=0;

    face_props[1].name=(char*)"vertex_indices";
    face_props[1].external_type=PLY_INT;
    face_props[1].internal_type=PLY_INT;
    face_props[1].offset=offsetof(Face,verts);
    face_props[1].is_list=1;
    face_props[1].count_external=PLY_UCHAR;
    face_props[1].count_internal=PLY_UCHAR;
    face_props[1].count_offset=offsetof(Face,nverts);

    xMax=INT_MIN;
    yMax=INT_MIN;
    zMax=INT_MIN;
    xMin=INT_MAX;
    yMin=INT_MAX;
    zMin=INT_MAX;

}


void PlyReader::readFile(char *filename)
{
    int i,j;

    // filename=(char*)"bunny.ply";
    printf("filename inside PlyReader %s\n",filename );
    /* open a PLY file for reading */
    ply = ply_open_for_reading(const_cast<char*>(filename), &nelems, &elist, &file_type, &version);

    printf ("version %f\n", version);
  printf ("type %d\n", file_type);
    /* go through each kind of element that we learned is in the file */
    /* and read them */

   
  for (i = 0; i < nelems; i++) {

    /* get the description of the first element */
    elem_name = elist[i];
    plist = ply_get_element_description (ply, elem_name, &num_elems, &nprops);

    /* if we're on vertex elements, read them in */
    if (equal_strings ((char *)"vertex", elem_name)) 
    {
            vertices = new Vertex*[num_elems];//memory allocation for vertices and normals
            setNoOfVertices(num_elems);
            /* create a vertex list to hold all the vertices */
 
            v = new Vertex*[num_elems];

            /* set up for getting vertex elements */

            ply_get_property (ply, elem_name, &vert_props[0]);
            ply_get_property (ply, elem_name, &vert_props[1]);
            ply_get_property (ply, elem_name, &vert_props[2]);

            /* grab all the vertex elements */
            for (j = 0; j < num_elems; j++) 
            {

                /* grab and element from the file */
                vertices[j] =new Vertex;
                v[j] =new Vertex;
                ply_get_element (ply, (void *) vertices[j]);

                //min max vertices
                if(getXMax()<vertices[j]->x)
                    setXMax(vertices[j]->x);
                if(getXMax()<vertices[j]->y)
                    setYMax(vertices[j]->y);
                if(getXMax()<vertices[j]->z)
                    setZMax(vertices[j]->z);

                if(getXMin()>vertices[j]->x)
                    setXMin(vertices[j]->x);
                if(getYMin()>vertices[j]->y)
                    setYMin(vertices[j]->y);
                if(getZMin()>vertices[j]->z)
                    setZMin(vertices[j]->z);
            }
        }

        /* if we're on face elements, read them in */
        if (equal_strings ((char*)"face", elem_name)) 
        {
            faces =new Face*[num_elems];
            setNoOfFaces(num_elems);
            /* create a list to hold all the face elements */
           normals = new Vector*[num_elems];
            /* set up for getting face elements */

            ply_get_property (ply, elem_name, &face_props[0]);
            ply_get_property (ply, elem_name, &face_props[1]);

            /* grab all the face elements */
            for (j = 0; j < num_elems; j++) 
            {

                /* grab and element from the file */
                faces[j] =new Face;
                normals[j] =new Vector;
                ply_get_element (ply, (void *) faces[j]);

            }
        }

    }

  ply_close (ply);
  

   for(int i = 0; i < noOfFaces; i++){
        PlyReader::getNormals(i);
        //printf("%d\n",i );
    }
}

void PlyReader::getNormals(int fc)
{
    float va[3], vb[3], vr[3], length;

   // find vector
   va[0] = vertices[faces[fc]->verts[1]]->x - vertices[faces[fc]->verts[0]]->x;
   va[1] = vertices[faces[fc]->verts[1]]->y - vertices[faces[fc]->verts[0]]->y;
   va[2] = vertices[faces[fc]->verts[1]]->z - vertices[faces[fc]->verts[0]]->z;

   vb[0] = vertices[faces[fc]->verts[2]]->x - vertices[faces[fc]->verts[1]]->x;
   vb[1] = vertices[faces[fc]->verts[2]]->y - vertices[faces[fc]->verts[1]]->y;
   vb[2] = vertices[faces[fc]->verts[2]]->z - vertices[faces[fc]->verts[1]]->z;

   //  cross product
   //vector va(x,y,z) and vector vb(x,y,z) == ||a||*||b||sin(theta)n>
   //ay*bz-az*by
   //az*bx-ax*bz
   //ax*by-ay*bx
   vr[0] = va[1] * vb[2] - va[2] * vb[1];
   vr[1] = va[2] * vb[0] - va[0] * vb[2];
   vr[2] = va[0] * vb[1] - va[1] * vb[0];

   // find normalization factor(normailzation) finding the direction of the normals
   // length = sqrt( vr[0]*vr[0] + vr[1]*vr[1] + vr[2]*vr[2] );

    // normals[fc]->x = vr[0]/length;
    // normals[fc]->y = vr[1]/length;
    // normals[fc]->z = vr[2]/length;
    normals[faces[fc]->verts[0]]->x += vr[0];
    normals[faces[fc]->verts[0]]->y += vr[1];
    normals[faces[fc]->verts[0]]->z += vr[2];
    normals[faces[fc]->verts[1]]->x += vr[0];
    normals[faces[fc]->verts[1]]->y += vr[1];
    normals[faces[fc]->verts[1]]->z += vr[2];
    normals[faces[fc]->verts[2]]->x += vr[0];
    normals[faces[fc]->verts[2]]->y += vr[1];
    normals[faces[fc]->verts[2]]->z += vr[2];
}


float PlyReader::scalePly(float dimension)
{
    float diff=0.0;
    std::cout<<"inside scale ply "<<dimension<<std::endl;
    std::cout<<" x min "<<getXMin()<<std::endl;
    std::cout<<" y min "<<getYMin()<<std::endl;
    std::cout<<" z min "<<getZMin()<<std::endl;
    std::cout<<" x max "<<getXMax()<<std::endl;
    std::cout<<" y max "<<getYMax()<<std::endl;
    std::cout<<" z max "<<getZMax()<<std::endl;
    float diffX=(getXMax()-getXMin())/1.0;
    float diffY=(getYMax()-getYMin())/1.0;
    float diffZ=(getZMax()-getZMin())/1.0;
std::cout<<"before diff "<<diff<<std::endl;
    if(diffX>diff)
    {

        if(diffX>diffZ)
        {
            diff=diffX;
            std::cout<<"inside diff xz "<<diff<<std::endl;
        }
        else
        {
            diff=diffZ;
            std::cout<<"inside diff xz else "<<diff<<std::endl;
        }
    }
    else
    {
        if(diffY>diffZ)
        {
            diff=diffY;
            std::cout<<"inside diff yz "<<diff<<std::endl;
        }
        else
        {
            diff=diffZ;
            std::cout<<"inside diff xz else "<<diff<<std::endl;
        }
    }
    std::cout<<"after diff "<<diff<<std::endl;
    std::cout<<"diffX "<<diffX<<std::endl;
    std::cout<<"diffY "<<diffY<<std::endl;
    std::cout<<"diffZ "<<diffZ<<std::endl;

return dimension/diff;
}

void PlyReader::Centroid(){

  setCentroid(((getXMax()+getXMin())/2.0),0);
  setCentroid(((getYMax()+getXMin())/2.0),1);
  setCentroid(((getZMax()+getXMin())/2.0),2);

}

void PlyReader::setXMax(float value)
{
    xMax=value;
}

void PlyReader::setYMax(float value)
{
    yMax=value;
}

void PlyReader::setZMax(float value)
{
    zMax=value;
}

void PlyReader::setXMin(float value)
{
    xMin=value;
}

void PlyReader::setYMin(float value)
{
    yMin=value;
}

void PlyReader::setZMin(float value)
{
    zMin=value;
}


float PlyReader::getXMax()
{
    return xMax;
}

float PlyReader::getYMax()
{
    return yMax;
}

float PlyReader::getZMax()
{
    return zMax;
}

float PlyReader::getXMin()
{
    return xMin;
}

float PlyReader::getYMin()
{
    return yMin;
}

float PlyReader::getZMin()
{
    return zMin;
}

void PlyReader::setCentroid(float value,int index)
{
    centroid[index]=value;
}

float PlyReader::getCentroid(int index)
{
    return centroid[index];
}

int PlyReader::getNoOfFaces(void){
    return noOfFaces;
}

int PlyReader::getNoOfVertices(void){
    return noOfVertices;
}

void PlyReader::setNoOfFaces(int F){
    noOfFaces = F;
}

void PlyReader::setNoOfVertices(int V){
    noOfVertices = V;
}

PlyReader::Face ** PlyReader::getFace(void){
    return faces;
}

PlyReader::Vertex ** PlyReader::getVertex(void){
    return vertices;
}

float PlyReader::getNormal(int index,int dimension)
{
    if(dimension==0)
        return normals[index]->x;
    if(dimension==1)
        return normals[index]->y;
    if(dimension==2)
        return normals[index]->z;
}

float PlyReader::getVertices(int index,int dimension)
{
    if(dimension==0)
        return vertices[index]->x;
    if(dimension==1)
        return vertices[index]->y;
    if(dimension==2)
        return vertices[index]->z;
}
float PlyReader::getFaces(int index,int dimension)
{
    return faces[index]->verts[dimension];
}

unsigned char PlyReader::getFacesVertices(int index)
{
    return faces[index]->nverts;
}

