#include <memory>
#include "Vector3.h"
#include "Utils.h"

#pragma once

#ifndef MATRIX3_H
#define MATRIX3_H

namespace GeoMa{
template<class Type = double >
class Matrix3
{
private:
    Type data[3 * 3];
    unsigned int rows = 3, cols = 3;
public:
    Matrix3(){
        ToZero();
    }

    Matrix3(Type _value){
        ToIdentity();
        data[0] = _value;
        data[4] = _value;
        data[8] = _value;
    }

    Matrix3(const Type _data[9]){
        memcpy(data, _data, 9);
    }

    Matrix3(const Vector3<Type>& v1, const Vector3<Type>& v2, const Vector3<Type>& v3, bool columns = false){
        if(columns){
            data[0] = v1.x, data[1] = v2.x, data[2] = v3.x;
            data[3] = v1.y, data[4] = v2.y, data[5] = v3.y;
            data[6] = v1.z, data[7] = v2.z, data[8] = v3.z;
        }
        else{
            data[0] = v1.x, data[1] = v1.y, data[2] = v1.z;
            data[3] = v2.x, data[4] = v2.y, data[5] = v2.z;
            data[6] = v3.x, data[7] = v3.y, data[8] = v3.z;
        }

    }

    Type operator[](unsigned int index) const{
        if(index < 9)
            return data[index];
    }

    Type& operator[](unsigned int index){
        if(index < 9)
            return data[index];
    }

    Type operator()(unsigned int row, unsigned int col) const{
        return data[row + col * 3];
    }

    Type& operator()(unsigned int row, unsigned int col) {
        return data[row + col * 3];
    }

    Matrix3<Type> operator+(Type value){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] + value;
        }
        return *this;
    }

    Matrix3<Type> operator+(Matrix3<Type> matrix){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] + matrix[i];
        }
        return *this;
    }

    Matrix3<Type> operator-(Type value){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] - value;
        }
        return *this;
    }

    Matrix3<Type> operator-(Matrix3<Type> matrix){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] - matrix[i];
        }
        return *this;
    }

    Matrix3<Type> operator*(Type value){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] * value;
        }
        return *this;
    }

    // TODO
    Matrix3<Type> operator*(Matrix3<Type> matrix){
        Matrix3<Type> res{};
        for(int i = 0; i < 3; i++){
            for(int j = 0; i < 3; j++){
                Type value = 0;
                for(int k = 0; k < 3; k++){
                    value += (*this)(i, k) * matrix(k,j);
                }
                res(i,j) = value;
            }
        }
        return res;
    }
    
    void                        ToZero() {
        for(int i = 0; i < 9; i++) data[i] = 0;
    }

    void                        ToIdentity() {
        ToZero();
        data[0] = 1, data[4] = 1, data[8] = 1;
    }

    Matrix3<Type>               Transpose() const{
        Matrix3<Type> result;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                result(i, j) = (*this)(i, j);
            }
        }
        return result;
    }

    static Matrix3<Type>        RotationX(float degrees){
        float radians = ToRadians(degrees);
        double c = cos(radians);
        double s = sin(radians);
        Matrix3<Type> rotationMatrix{};
        rotationMatrix[0] = 1; // r1 
        rotationMatrix[4] = c, rotationMatrix[5] = -s; // r2 
        rotationMatrix[7] = s, rotationMatrix[8] = c; // r3 
        return rotationMatrix;
    }

    static Matrix3<Type>        RotationY(float degrees){
        float radians = ToRadians(degrees);
        double c = cos(radians);
        double s = sin(radians);
        Matrix3<Type> rotationMatrix{};
        rotationMatrix[0] = c, rotationMatrix[2] = s; // r1 
        rotationMatrix[4] = 1; // r2 
        rotationMatrix[6] = -s, rotationMatrix[8] = c; // r3 
        return rotationMatrix;
    }

    static Matrix3<Type>       RotationZ(float degrees){
        float radians = ToRadians(degrees);
        double c = cos(radians);
        double s = sin(radians);
        Matrix3<Type> rotationMatrix{};
        rotationMatrix[0] = c, rotationMatrix[1] = -s; // r1 
        rotationMatrix[3] = s, rotationMatrix[4] = c; // r2 
        rotationMatrix[8] = 1; // r3 
        return rotationMatrix;
    }


    static Matrix3<Type>        Rotation(float degrees, Vector3F axis){ // TODO : Test if no errors
        axis.Normalize();
        float radians = ToRadians(degrees);
        float c = cos(radians);
        float s = sin(radians);

        Matrix3<Type> result;
        result[0] = c + axis.x * axis.x * (1 - c);
        result[1] = axis.x * axis.y * (1 - c) - axis.z * s;
        result[2] = axis.x * axis.z * (1 - c) + axis.y * s;

        result[3] = axis.y * axis.x * (1 - c) + axis.z * s;
        result[4] = c + axis.y * axis.y * (1 - c);
        result[5] = axis.x * axis.z * (1 - c) + axis.x * s;

        result[6] = axis.z * axis.x * (1 - c) - axis.y * s;
        result[7] = axis.z * axis.y * (1 - c) + axis.x * s;
        result[8] = c + axis.z * axis.z * (1 - c);

        return result;
    }

    static Matrix3<Type>               Scale(float scale, Vector3F axis){
        axis.Normalize();
        Matrix3<Type> result;
        float minus_scale = 1 - scale;

        result[0] = 1 + minus_scale * axis.x * axis.x;
        result[1] = minus_scale * axis.x * axis.y;
        result[2] = minus_scale * axis.x * axis.z;

        result[3] = minus_scale * axis.y * axis.x;
        result[4] = 1 + minus_scale * axis.y * axis.y;
        result[5] = minus_scale * axis.y * axis.z;

        result[6] = minus_scale * axis.z * axis.x;
        result[7] = minus_scale * axis.z * axis.y;
        result[8] = 1 + minus_scale * axis.z * axis.z;

        return result;
    }

    



};
template<class Type>
std::ostream& operator<<(std::ostream& os, Matrix3<Type> mat){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            os << mat(i,j) << " ";
        }
        std::cout << std::endl;
    }
    return os;
}

using Matrix3F = Matrix3<float>;
using Matrix3I = Matrix3<int>;

}
#endif // MATRIX3_H