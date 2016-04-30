#ifndef VIEW_H
#define VIEW_H

#include <GL/glut.h>
#include "Model.h"

class View
{

public:
	
	void init(int,int);

	static void render();
    static void reshape(int, int);
	
};

#endif