#include <memory>
#include "Vector3.h"
#include "Vector4.h"
#include "Utils.h"

#pragma once

#ifndef MATRIX4_H
#define MATRIX4_H

namespace GeoMa{
template<class Type = double >
class Matrix4
{
private:
    Type data[4 * 4];
    unsigned int rows = 4, cols = 4;
public:
    Matrix4(){
        ToZero();
    }

    Matrix4(Type _value){
        ToIdentity();
        data[0] = _value;
        data[5] = _value;
        data[10] = _value;
        data[15] = _value;
    }

    Matrix4(const Type _data[16]){
        memcpy(data, _data, 16 * sizeof(Type));
    }

    Matrix4(const Vector4<Type>& v1, const Vector4<Type>& v2, const Vector4<Type>& v3, const Vector4<Type>& v4, bool columns = false){
        if(columns){
            data[0] = v1.x, data[1] = v2.x, data[2] = v3.x, data[3] = v4.x;
            data[4] = v1.y, data[5] = v2.y, data[6] = v3.y, data[7] = v4.y;
            data[8] = v1.z, data[9] = v2.z, data[10] = v3.z, data[11] = v4.z;
            data[12] = v1.t, data[13] = v2.t, data[14] = v3.t, data[15] = v4.t;
        }
        else{
            data[0] = v1.x, data[1] = v1.y, data[2] = v1.z, data[3] = v1.t;
            data[4] = v2.x, data[5] = v2.y, data[6] = v2.z, data[7] = v2.t;
            data[8] = v3.x, data[9] = v3.y, data[10] = v3.z, data[11] = v3.t;
            data[12] = v4.x, data[13] = v4.y, data[14] = v4.z, data[15] = v4.t;
        }
    }

    Type operator[](unsigned int index) const{
        if(index < 16)
            return data[index];
    }

    Type& operator[](unsigned int index){
        if(index < 16)
            return data[index];
    }

    Type operator()(unsigned int row, unsigned int col) const{
        return data[row + col * 4];
    }

    Type& operator()(unsigned int row, unsigned int col) {
        return data[row + col * 4];
    }

    Matrix4<Type> operator+(Type value){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] + value;
        }
        return *this;
    }

    Matrix4<Type> operator+(Matrix4<Type> matrix){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] + matrix[i];
        }
        return *this;
    }

    Matrix4<Type> operator-(Type value){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] - value;
        }
        return *this;
    }

    Matrix4<Type> operator-(Matrix4<Type> matrix){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] - matrix[i];
        }
        return *this;
    }

    Matrix4<Type> operator*(Type value){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] * value;
        }
        return *this;
    }

    Matrix4<Type> operator*(const Matrix4<Type>& matrix) const {
        Matrix4<Type> res{};
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                Type value = 0;
                for(int k = 0; k < 4; k++){
                    value += (*this)(i, k) * matrix(k, j);
                }
                res(i, j) = value;
            }
        }
        return res;
    }

    Vector4<Type> operator*(const Vector4<Type>& v) const {
        return Vector4<Type>(
            data[0]*v.x + data[1]*v.y + data[2]*v.z + data[3]*v.t,
            data[4]*v.x + data[5]*v.y + data[6]*v.z + data[7]*v.t,
            data[8]*v.x + data[9]*v.y + data[10]*v.z + data[11]*v.t,
            data[12]*v.x + data[13]*v.y + data[14]*v.z + data[15]*v.t
        );
    }
    
    void ToZero() {
        for(int i = 0; i < 16; i++) data[i] = 0;
    }

    void ToIdentity() {
        ToZero();
        data[0] = 1, data[5] = 1, data[10] = 1, data[15] = 1;
    }

    Matrix4<Type> Transpose() const{
        Matrix4<Type> result;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                result(i, j) = (*this)(j, i);
            }
        }
        return result;
    }

    static Matrix4<Type> RotationX(float degrees){
        float radians = ToRadians(degrees);
        double c = cos(radians);
        double s = sin(radians);
        Matrix4<Type> rotationMatrix{};
        rotationMatrix[0] = 1; // r1 
        rotationMatrix[5] = c, rotationMatrix[6] = -s; // r2 
        rotationMatrix[9] = s, rotationMatrix[10] = c; // r3 
        rotationMatrix[15] = 1; // r4
        return rotationMatrix;
    }

    static Matrix4<Type> RotationY(float degrees){
        float radians = ToRadians(degrees);
        double c = cos(radians);
        double s = sin(radians);
        Matrix4<Type> rotationMatrix{};
        rotationMatrix[0] = c, rotationMatrix[2] = s; // r1 
        rotationMatrix[5] = 1; // r2 
        rotationMatrix[8] = -s, rotationMatrix[10] = c; // r3 
        rotationMatrix[15] = 1; // r4
        return rotationMatrix;
    }

    static Matrix4<Type> RotationZ(float degrees){
        float radians = ToRadians(degrees);
        double c = cos(radians);
        double s = sin(radians);
        Matrix4<Type> rotationMatrix{};
        rotationMatrix[0] = c, rotationMatrix[1] = -s; // r1 
        rotationMatrix[4] = s, rotationMatrix[5] = c; // r2 
        rotationMatrix[10] = 1; // r3 
        rotationMatrix[15] = 1; // r4
        return rotationMatrix;
    }

    static Matrix4<Type> Rotation(float degrees, Vector3F axis){
        axis.Normalize();
        float radians = ToRadians(degrees);
        float c = cos(radians);
        float s = sin(radians);
        float minus_c = 1 - c;

        Matrix4<Type> result;
        result[0] = c + axis.x * axis.x * minus_c;
        result[1] = axis.x * axis.y * minus_c - axis.z * s;
        result[2] = axis.x * axis.z * minus_c + axis.y * s;
        result[3] = 0;

        result[4] = axis.y * axis.x * minus_c + axis.z * s;
        result[5] = c + axis.y * axis.y * minus_c;
        result[6] = axis.y * axis.z * minus_c - axis.x * s;
        result[7] = 0;

        result[8] = axis.z * axis.x * minus_c - axis.y * s;
        result[9] = axis.z * axis.y * minus_c + axis.x * s;
        result[10] = c + axis.z * axis.z * minus_c;
        result[11] = 0;

        result[12] = 0;
        result[13] = 0;
        result[14] = 0;
        result[15] = 1;

        return result;
    }

    static Matrix4<Type> Scale(float scale, Vector3F axis){
        axis.Normalize();
        Matrix4<Type> result;
        float minus_scale = 1 - scale;

        result[0] = 1 + minus_scale * axis.x * axis.x;
        result[1] = minus_scale * axis.x * axis.y;
        result[2] = minus_scale * axis.x * axis.z;
        result[3] = 0;

        result[4] = minus_scale * axis.y * axis.x;
        result[5] = 1 + minus_scale * axis.y * axis.y;
        result[6] = minus_scale * axis.y * axis.z;
        result[7] = 0;

        result[8] = minus_scale * axis.z * axis.x;
        result[9] = minus_scale * axis.z * axis.y;
        result[10] = 1 + minus_scale * axis.z * axis.z;
        result[11] = 0;

        result[12] = 0;
        result[13] = 0;
        result[14] = 0;
        result[15] = 1;

        return result;
    }

    static Matrix4<Type> Translation(const Vector3F& translation){
        Matrix4<Type> result;
        result.ToIdentity();
        result[3] = translation.x;
        result[7] = translation.y;
        result[11] = translation.z;
        return result;
    }

    static Matrix4<Type> LookAt(const Vector3<Type>& eye, const Vector3<Type>& center, const Vector3<Type>& up) {
        Vector3<Type> f = (center - eye).Normalized();
        Vector3<Type> s = Vector3<Type>::Cross(f, up).Normalized();
        Vector3<Type> u = Vector3<Type>::Cross(s, f);

        Matrix4<Type> Result(1.0);
        Result(0, 0) = s.x;
        Result(0, 1) = s.y;
        Result(0, 2) = s.z;
        Result(1, 0) = u.x;
        Result(1, 1) = u.y;
        Result(1, 2) = u.z;
        Result(2, 0) = -f.x;
        Result(2, 1) = -f.y;
        Result(2, 2) = -f.z;
        Result(0, 3) = -Vector3<Type>::Dot(s, eye);
        Result(1, 3) = -Vector3<Type>::Dot(u, eye);
        Result(2, 3) = Vector3<Type>::Dot(f, eye);
        return Result;
    }

    static Matrix4<Type> Perspective(Type fovy, Type aspect, Type zNear, Type zFar) {
        Type const tanHalfFovy = tan(fovy / static_cast<Type>(2));
        Matrix4<Type> Result;
        Result.ToZero();
        Result(0, 0) = static_cast<Type>(1) / (aspect * tanHalfFovy);
        Result(1, 1) = static_cast<Type>(1) / (tanHalfFovy);
        Result(2, 2) = -(zFar + zNear) / (zFar - zNear);
        Result(3, 2) = -static_cast<Type>(1);
        Result(2, 3) = -(static_cast<Type>(2) * zFar * zNear) / (zFar - zNear);
        return Result;
    }
};

template<class Type>
std::ostream& operator<<(std::ostream& os, Matrix4<Type> mat){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            os << mat(i,j) << " ";
        }
        std::cout << std::endl;
    }
    return os;
}

using Matrix4F = Matrix4<float>;
using Matrix4I = Matrix4<int>;

}
#endif // MATRIX4_H