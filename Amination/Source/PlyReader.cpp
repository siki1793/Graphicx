#include "PlyReader.h"
#include "arcball.h"


PlyReader::PlyReader(void)
{

    noOfVertices=0;

    noOfFaces=0;

    centroid[0]=0.0;
    centroid[1]=0.0;
    centroid[2]=0.0;

    spot[0]=0.0;
    spot[0]=0.0;
    spot[0]=0.2;

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

    // texture[0] = LoadGLTextures(const_cast<char*>("textures/brickwall.bmp"));
    // texture[1] = LoadGLTextures(const_cast<char*>("textures/world.bmp"));
    // texture[2] = LoadGLTextures(const_cast<char*>("textures/apple.bmp"));
}

void PlyReader::init() {
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    printf("=======================================================here\n");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

}

void PlyReader::readFile(char *filename,char *texFile)
{
    int i,j;

    // filename=(char*)"bunny.ply";
    printf("filename inside PlyReader %s\n",filename );
    /* open a PLY file for reading */
    ply = ply_open_for_reading(const_cast<char*>(filename), &nelems, &elist, &file_type, &version);

    texture[2]=LoadGLTextures(const_cast<char*>(texFile));

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
            // vertices = new Vertex*[num_elems];
            vertices = (Vertex **) malloc (sizeof (Vertex *) * num_elems);//memory allocation for vertices and normals

            setNoOfVertices(num_elems);
            /* create a vertex list to hold all the vertices */
 
            // v = new Vertex*[num_elems];
            v = (Vertex **) malloc (sizeof (Vertex *) * num_elems);

            /* set up for getting vertex elements */

            ply_get_property (ply, elem_name, &vert_props[0]);
            ply_get_property (ply, elem_name, &vert_props[1]);
            ply_get_property (ply, elem_name, &vert_props[2]);

            /* grab all the vertex elements */
            for (j = 0; j < num_elems; j++) 
            {

                /* grab and element from the file */
                // vertices[j] =new Vertex;
                vertices[j] = (Vertex *) malloc (sizeof (Vertex));
                // v[j] =new Vertex;
                v[j] = (Vertex *) malloc (sizeof (Vertex));

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
            // faces =new Face*[num_elems];
            faces = (Face **) malloc (sizeof (Face *) * num_elems);
            setNoOfFaces(num_elems);
            /* create a list to hold all the face elements */
           // normals = new Vector*[num_elems];
            normals = (Vector **) malloc (sizeof (Vector *) * num_elems);
            /* set up for getting face elements */

            ply_get_property (ply, elem_name, &face_props[0]);
            ply_get_property (ply, elem_name, &face_props[1]);

            /* grab all the face elements */
            for (j = 0; j < num_elems; j++) 
            {

                /* grab and element from the file */
                // faces[j] =new Face;
                faces[j] = (Face *) malloc (sizeof (Face));
                // normals[j] =new Vector;
                normals[j] = (Vector *) malloc (sizeof (Vector));
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

   vr[0] = va[1] * vb[2] - va[2] * vb[1];
   vr[1] = va[2] * vb[0] - va[0] * vb[2];
   vr[2] = va[0] * vb[1] - va[1] * vb[0];

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

    float diffX=(getXMax()-getXMin())/1.0;
    float diffY=(getYMax()-getYMin())/1.0;
    float diffZ=(getZMax()-getZMin())/1.0;

    if(diffX>diff)
    {

        if(diffX>diffZ)
        {
            diff=diffX;

        }
        else
        {
            diff=diffZ;
     
        }
    }
    else
    {
        if(diffY>diffZ)
        {
            diff=diffY;
     
        }
        else
        {
            diff=diffZ;
     
        }
    }

return dimension/diff;
}


void PlyReader::drawScene(int tex,int id){
    //Objects of corresponding classes
    GLuint myTexture;
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &myTexture);
    glBindTexture(GL_TEXTURE_2D, myTexture); //the title screen
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    if(tex==1)
    {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture[1]->sizeX, texture[1]->sizeY, 1, 
                        GL_RGB, GL_UNSIGNED_BYTE, texture[1]->data);
    }
    if(tex==2)
    {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture[2]->sizeX, texture[2]->sizeY, 1, 
                        GL_RGB, GL_UNSIGNED_BYTE, texture[2]->data);
    }
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        std::cout<<" ----------->inside ply Draw scene scale value <-------------------"<<std::endl<<" is ================="<<scalePly(0.5)<<std::endl;
        originX=0.0;
        originY=0.0;
        originZ=0.0;
        errorY=0.0;
        errorY=(getYMax()-getYMin())/2.0;

        if(id==2)
            glScalef(scalePly(0.2),scalePly(0.2),scalePly(0.2));
        else
            glScalef(scalePly(0.2),scalePly(0.2),scalePly(0.2));
        glTranslatef((-getCentroid(0)-originX),(-getCentroid(1)+errorY-originY),(-getCentroid(2)-originZ));
        if(id==0)
            drawBoundingBox(5.2);

        if(id==1)
        {

            glRotatef(-90.0, 1.0, 0.0, 0.0);
            glRotatef(90.0, 0.0, 0.0, 1.0);
        }
        else if(id == 0)
        {
        GLfloat light7_position[] = {spot[0],spot[1], spot[2], 1.0f};
        GLfloat light7_ambient[] =  {0.0f, 0.0f, 1.0f, 0.0f};
        GLfloat light7_diffuse[] =  {0.0f, 0.0f, 1.0f, 0.0f};
    // GLfloat qaSpecularLight[]    = {1.0, 0.0, 0.0, 0.0};
        GLfloat dirVector7[]={  spot[0], spot[1], spot[2], 0.0};
        glLightfv(GL_LIGHT2, GL_POSITION, light7_position);
        glLightfv(GL_LIGHT2, GL_AMBIENT, light7_ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light7_diffuse);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 70.0);
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 4.0);
        glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,dirVector7);
        // glEnable(GL_LIGHT7);
    }
    else if(id == 2)
    {
            glRotatef(-90.0, 1.0, .0, 0.0);
        GLfloat light7_position[] = {spot[0],spot[1], spot[2], 1.0f};
        GLfloat light7_ambient[] =  {1.0f, 0.0f, 0.0f, 0.0f};
        GLfloat light7_diffuse[] =  {1.0f, 0.0f, 0.0f, 0.0f};
    // GLfloat qaSpecularLight[]    = {1.0, 0.0, 0.0, 0.0};
        GLfloat dirVector7[]={  -spot[0], -spot[1], -spot[2], 0.0};
        glLightfv(GL_LIGHT3, GL_POSITION, light7_position);
        glLightfv(GL_LIGHT3, GL_AMBIENT, light7_ambient);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light7_diffuse);
        glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 70.0);
        glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 4.0);
        glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,dirVector7);
        // glEnable(GL_LIGHT7);
    }
        drawPly(2);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
}

void PlyReader::drawBoundingBox(float dim)
{

    ver[0][0] = ver[1][0] = ver[2][0] = ver[3][0] = -dim/2;
    ver[4][0] = ver[5][0] = ver[6][0] = ver[7][0] = dim/2;
    ver[0][1] = ver[1][1] = ver[4][1] = ver[5][1] = -dim/2;
    ver[2][1] = ver[3][1] = ver[6][1] = ver[7][1] = dim/2;
    ver[0][2] = ver[3][2] = ver[4][2] = ver[7][2] = dim/2;
    ver[1][2] = ver[2][2] = ver[5][2] = ver[6][2] = -dim/2;

    glMatrixMode(GL_MODELVIEW);

    glColor3f(1.0,1.0,1.0);


    for (int i = 0; i < 4 ; i++) {
        glBegin(GL_LINES);

        glVertex3f(ver[i][0],ver[i][1],ver[i][2]);
        glVertex3f(ver[(i+1)%4][0],ver[(i+1)%4][1],ver[(i+1)%4][2]);

        glVertex3f(ver[i][0],ver[i][1],ver[i][2]);
        glVertex3f(ver[i+4][0],ver[i+4][1],ver[i+4][2]);

        glVertex3f(ver[i+4][0],ver[i+4][1],ver[i+4][2]);
        if((i+5)%8!=0)
            glVertex3f(ver[(i+5)%8][0],ver[(i+5)%8][1],ver[(i+5)%8][2]);
        else
            glVertex3f(ver[4][0],ver[4][1],ver[4][2]);

        glEnd();


    }

}


//Draws Bunny
void PlyReader::drawPly(int shape){
    for(int i = 0; i < getNoOfFaces(); i++){
        glBegin(GL_POLYGON);
            for(int j = 0; j < (int)getFacesVertices(i); j++){
                int f=getFaces(i,j);
                glNormal3f(getNormal(f,0), getNormal(f,1), getNormal(f,2));
                GLfloat x=getVertices(getFaces(i,j),0);
                GLfloat y=getVertices(getFaces(i,j),1);
                GLfloat z=getVertices(getFaces(i,j),2);

                if(shape==1)
                {
                    double u=((atan2(x,z))/(2*M_PI))+.5;
                    double v=(y/getZMax())+.5;

                glTexCoord2f(u,v);
                }
                else if(shape==2)
                {
                    
                    double lenght=sqrt((x-getCentroid(0))*(x-getCentroid(0))+
                        (y-getCentroid(1))*(y-getCentroid(1))+(z-getCentroid(2))*(z-getCentroid(2)));

                    //normalization
                    double normX=(x-getCentroid(0))/lenght;
                    double normY=(y-getCentroid(1))/lenght;
                    double normZ=(z-getCentroid(2))/lenght;

                    double u=0.5+(atan2(normX,normZ)/(2*M_PI));
                    double v=0.5+(asin(normY)/M_PI);

                    glTexCoord2f(u,v);
                }
                //getUVCoord(3*getVertices(getFaces(i,j),0),
                //    3*getVertices(getFaces(i,j),1),3*getVertices(getFaces(i,j),2));
                glVertex3f(x,y,z);

            }
        glEnd();
    }
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

