#include "Matrix4.h"


Matrix4::Matrix4() {
    
}

Matrix4 Matrix4::Translation(const Vec3f &Pos) {
    Matrix4 Result;
    Result._Entries[0][0] = 1.0f;
    Result._Entries[1][0] = 0.0f;
    Result._Entries[2][0] = 0.0f;
    Result._Entries[3][0] = Pos.x;

    Result._Entries[0][1] = 0.0f;
    Result._Entries[1][1] = 1.0f;
    Result._Entries[2][1] = 0.0f;
    Result._Entries[3][1] = Pos.y;

    Result._Entries[0][2] = 0.0f;
    Result._Entries[1][2] = 0.0f;
    Result._Entries[2][2] = 1.0f;
    Result._Entries[3][2] = Pos.z;

    Result._Entries[0][3] = 0.0f;
    Result._Entries[1][3] = 0.0f;
    Result._Entries[2][3] = 0.0f;
    Result._Entries[3][3] = 1.0f;
    return Result;
}

Matrix4 Matrix4::Rotation(const Vec3f &Axis, float Angle)
{
    float c = cosf(Angle);
    float s = sinf(Angle);
    float t = 1.0f - c;

    double lenght=sqrt((Axis.x*Axis.x)+
                        (Axis.y*Axis.y)+(Axis.z*Axis.z));

                    //normalization
                    double normX=(Axis.x)/lenght;
                    double normY=(Axis.y)/lenght;
                    double normZ=(Axis.z)/lenght;


    float x = normX;
    float y = normY;
    float z = normZ;

    Matrix4 Result;
    Result._Entries[0][0] = 1 + t*(x*x-1);
    Result._Entries[1][0] = z*s+t*x*y;
    Result._Entries[2][0] = -y*s+t*x*z;
    Result._Entries[3][0] = 0.0f;

    Result._Entries[0][1] = -z*s+t*x*y;
    Result._Entries[1][1] = 1+t*(y*y-1);
    Result._Entries[2][1] = x*s+t*y*z;
    Result._Entries[3][1] = 0.0f;

    Result._Entries[0][2] = y*s+t*x*z;
    Result._Entries[1][2] = -x*s+t*y*z;
    Result._Entries[2][2] = 1+t*(z*z-1);
    Result._Entries[3][2] = 0.0f;

    Result._Entries[0][3] = 0.0f;
    Result._Entries[1][3] = 0.0f;
    Result._Entries[2][3] = 0.0f;
    Result._Entries[3][3] = 1.0f;
    return Result;
}


Matrix4 Matrix4::Identity() {
    Matrix4 Result;
    for(int i = 0; i < 4; i++) {
        for(int i2 = 0; i2 < 4; i2++) {
            if(i == i2) {
                Result._Entries[i][i2] = 1.0f;
            } else {
                Result._Entries[i][i2] = 0.0f;
            }
        }
    }
    return Result;
}

void Matrix4::printMatrix() {
    for(int i = 0; i < 4; i++) {
        for(int i2 = 0; i2 < 4; i2++) {
            printf("%d %d %f\t",i,i2, _Entries[i][i2]);
        }
        printf("\n");
    }
}

Matrix4 Matrix4::RotationX(float Theta) {
    float CosT = cosf(Theta);
    float SinT = sinf(Theta);

    Matrix4 Result = Identity();
    Result._Entries[1][1] = CosT;
    Result._Entries[1][2] = SinT;
    Result._Entries[2][1] = -SinT;
    Result._Entries[2][2] = CosT;
    return Result;
}

Matrix4 Matrix4::RotationY(float Theta) {
    float CosT = cosf(Theta);
    float SinT = sinf(Theta);

    Matrix4 Result = Identity();
    Result._Entries[0][0] = CosT;
    Result._Entries[0][2] = SinT;
    Result._Entries[2][0] = -SinT;
    Result._Entries[2][2] = CosT;
    return Result;
}

Matrix4 Matrix4::RotationZ(float Theta) {
    float CosT = cosf(Theta);
    float SinT = sinf(Theta);

    Matrix4 Result = Identity();
    Result._Entries[0][0] = CosT;
    Result._Entries[0][1] = SinT;
    Result._Entries[1][0] = -SinT;
    Result._Entries[1][1] = CosT;
    return Result;
}

Vec3f Matrix4::multiVector(Vec3f v)
{
    Vec3f temp;
    temp.x=v.x * _Entries[0][0] + v.y * _Entries[1][0] + v.z * _Entries[2][0] + _Entries[3][0];
    temp.x=v.x * _Entries[0][1] + v.y * _Entries[1][1] + v.z * _Entries[2][1] + _Entries[3][1];
    temp.x=v.x * _Entries[0][2] + v.y * _Entries[1][2] + v.z * _Entries[2][2] + _Entries[3][2];

    return temp;
    // return Vec3f(location.x * _Entries[0][0] + location.y * _Entries[1][0] + location.z * _Entries[2][0],
    //             location.x * _Entries[0][1] + location.y * _Entries[1][1] + location.z * _Entries[2][1],
    //             location.x * _Entries[0][2] + location.y * _Entries[1][2] + location.z * _Entries[2][2]);
}