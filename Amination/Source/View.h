#ifndef VIEW_H
#define VIEW_H

#include <GL/glut.h>
#include <vector>
#include "arcball.h"

static bool lightList[5] = {1,1,1,1,1};


class View
{

public:
	
	void init(int,int);

	void resize(int , int);
	
};

#endif