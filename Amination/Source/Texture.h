#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include "GL/glut.h"
#include "GL/gl.h"

#define TITLE 0
#define BLOCK 1
#define GAME_END 2 
#define FONT 3
#define checkImageWidth 64
#define checkImageHeight 64
#define MAX_TEXTURES 4 

typedef struct Image_s {
    char *data;
	int bpp;
	int sizeX, sizeY;
	int id;
} Image;


int LoadTexture(char *, Image *);
unsigned int GetTexture( int texID );
void makeCheckImage(void);
// int LoadTGA(Image *image, char  *filename);
Image* LoadGLTextures( char *);

#endif