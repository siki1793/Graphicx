#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector.h"
#include "stdio.h"


class Matrix4 {
public:
    Matrix4();

    float _Entries[4][4];
    Matrix4 Translation(const Vec3f &Pos);
    Matrix4 Rotation(const Vec3f &Axis, float Angle);
    Matrix4 RotationX(float);
    Matrix4 RotationY(float);
    Matrix4 RotationZ(float);
    Vec3f multiVector(Vec3f v);
    static Matrix4 Identity();
    void printMatrix();

    inline Matrix4 operator * (const Matrix4 &Right) {
	    Matrix4 Result;
	    for(int i = 0; i < 4; i++)     {
	        for(int i2 = 0; i2 < 4; i2++) {
	            float Total = 0.0f;
	            for(int i3 = 0; i3 < 4; i3++) {
	                Total += this -> _Entries[i][i3] * Right._Entries[i3][i2];
	            }
	            Result._Entries[i][i2] = Total;
	        }
	    }
	    return Result;
	}

	inline Matrix4 operator = (const Matrix4 &Right) {
	    for(int Row = 0; Row < 4; Row++) {
	        for(int Col = 0; Col < 4; Col++) {
	            _Entries[Row][Col] = Right._Entries[Row][Col];
	        }
	    }
	    return (*this);
	}
};


#endif