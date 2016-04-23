#include "Model.h"
#include "GL/glut.h"
#include "GL/gl.h"

void Model::quaternion(char ch,int angle){
    float quaternionRotateMatrix[16]={ 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    float vx = 0.0,vy = 0.0,vz = 0.0,qCOS,qSINx,qSINy,qSINz;
	switch(ch)
	{
	    case 'x':   vx = 1.0;
                    vy = 0.0;
                    vz = 0.0;
                    break;
		case 'y':   vx = 0.0;
                    vy = 1.0;
                    vz = 0.0;
                    break;
		case 'z':   vx = 0.0;
                    vy = 0.0;
                    vz = 1.0;
                    break;
	}
	float radAngle = M_PI * angle/180;
    qCOS = cos(radAngle/2);
	qSINx = sin(radAngle/2) * vx;
	qSINy = sin(radAngle/2) * vy;
	qSINz = sin(radAngle/2) * vz;

	quaternionRotateMatrix[0] = 1.0f - 2.0f * qSINy * qSINy - 2.0f * qSINz * qSINz ;
	quaternionRotateMatrix[4] = 2.0f * qSINx * qSINy - 2.0f * qCOS * qSINz;
	quaternionRotateMatrix[8] = 2.0f * qSINx * qSINz + 2.0f * qCOS * qSINy;
	quaternionRotateMatrix[12] = 0.0f;

	quaternionRotateMatrix[1] = 2.0f * qSINx * qSINy + 2.0f * qCOS * qSINz;
	quaternionRotateMatrix[5] = 1.0f - 2.0f * qSINx * qSINx - 2.0f * qSINz * qSINz;
	quaternionRotateMatrix[9] = 2.0f * qSINy * qSINz - 2.0f * qCOS * qSINx;
	quaternionRotateMatrix[13] = 0.0f;

	quaternionRotateMatrix[2] = 2.0f * qSINx * qSINz - 2.0f * qCOS * qSINy;
	quaternionRotateMatrix[6] = 2.0f * qSINy * qSINz + 2.0f * qCOS * qSINx;
	quaternionRotateMatrix[10] = 1.0f - 2.0f * qSINx * qSINx - 2.0f * qSINy * qSINy;
	quaternionRotateMatrix[14] = 0.0f;

	quaternionRotateMatrix[3] = 0.0f;
	quaternionRotateMatrix[7] = 0.0f;
	quaternionRotateMatrix[11] = 0.0f;
	quaternionRotateMatrix[15] = 1.0f;

    glMultMatrixf(quaternionRotateMatrix);
	//glutPostRedisplay();
}
