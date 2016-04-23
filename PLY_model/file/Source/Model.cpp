#include "Model.h"
#include "GL/freeglut.h"
#include "GL/gl.h"

void Model::quaternion(char ch,int angle){
    float qRotateMatrix[16]={ 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
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

	qRotateMatrix[0] = 1.0f - 2.0f * qSINy * qSINy - 2.0f * qSINz * qSINz ;
	qRotateMatrix[4] = 2.0f * qSINx * qSINy - 2.0f * qCOS * qSINz;
	qRotateMatrix[8] = 2.0f * qSINx * qSINz + 2.0f * qCOS * qSINy;
	qRotateMatrix[12] = 0.0f;

	qRotateMatrix[1] = 2.0f * qSINx * qSINy + 2.0f * qCOS * qSINz;
	qRotateMatrix[5] = 1.0f - 2.0f * qSINx * qSINx - 2.0f * qSINz * qSINz;
	qRotateMatrix[9] = 2.0f * qSINy * qSINz - 2.0f * qCOS * qSINx;
	qRotateMatrix[13] = 0.0f;

	qRotateMatrix[2] = 2.0f * qSINx * qSINz - 2.0f * qCOS * qSINy;
	qRotateMatrix[6] = 2.0f * qSINy * qSINz + 2.0f * qCOS * qSINx;
	qRotateMatrix[10] = 1.0f - 2.0f * qSINx * qSINx - 2.0f * qSINy * qSINy;
	qRotateMatrix[14] = 0.0f;

	qRotateMatrix[3] = 0.0f;
	qRotateMatrix[7] = 0.0f;
	qRotateMatrix[11] = 0.0f;
	qRotateMatrix[15] = 1.0f;

    glMultMatrixf(qRotateMatrix);
	//glutPostRedisplay();
}
