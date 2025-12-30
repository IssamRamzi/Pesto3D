#include <memory>
#include "Vector2.h"
#include "Utils.h"

#pragma once

#ifndef MATRIX2_H
#define MATRIX2_H

namespace GeoMa{
template<class Type = double >
class Matrix2
{
private:
    Type data[2 * 2];
    unsigned int rows = 2, cols = 2;
public:
    Matrix2(){
        ToZero();
    }
    Matrix2(Type _value){
        ToIdentity();
        data[0] = _value;
        data[3] = _value;
    }
    Matrix2(const Type _data[4]){
        memcpy(data, _data, 4 * sizeof(Type));
    }
    Matrix2(const Vector2<Type>& v1, const Vector2<Type>& v2, bool columns = false){
        if(columns){
            data[0] = v1.x, data[1] = v2.x;
            data[2] = v1.y, data[3] = v2.y;
        }
        else{
            data[0] = v1.x, data[1] = v1.y;
            data[2] = v2.x, data[3] = v2.y;
        }
    }
    Type operator[](unsigned int index) const{
        if(index < 4)
            return data[index];
    }
    Type& operator[](unsigned int index){
        if(index < 4)
            return data[index];
    }
    Type operator()(unsigned int row, unsigned int col) const{
        return data[row + col * 2];
    }
    Type& operator()(unsigned int row, unsigned int col) {
        return data[row + col * 2];
    }
    Matrix2<Type> operator+(Type value){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] + value;
        }
        return *this;
    }
    Matrix2<Type> operator+(Matrix2<Type> matrix){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] + matrix[i];
        }
        return *this;
    }
    Matrix2<Type> operator-(Type value){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] - value;
        }
        return *this;
    }
    Matrix2<Type> operator-(Matrix2<Type> matrix){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] - matrix[i];
        }
        return *this;
    }
    Matrix2<Type> operator*(Type value){
        for(int i = 0; i < rows*cols; i++){
            data[i] = data[i] * value;
        }
        return *this;
    }
    
    Matrix2<Type> operator*(const Matrix2<Type>& matrix) const {
        Matrix2<Type> res{};
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                Type value = 0;
                for(int k = 0; k < 2; k++){
                    value += (*this)(i, k) * matrix(k, j);
                }
                res(i, j) = value;
            }
        }
        return res;
    }

    Vector2<Type> operator*(const Vector2<Type>& v) const {
        return Vector2<Type>(
            data[0]*v.x + data[1]*v.y,
            data[2]*v.x + data[3]*v.y
        );
    }
    
    void ToZero() {
        for(int i = 0; i < 4; i++) data[i] = 0;
    }
    
    void ToIdentity() {
        ToZero();
        data[0] = 1, data[3] = 1;
    }
    
    Matrix2<Type> Transpose() const{
        Matrix2<Type> result;
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                result(i, j) = (*this)(j, i);
            }
        }
        return result;
    }
    
    static Matrix2<Type> Rotation(double degrees) {
        double radians = GeoMa::ToRadians(degrees);
        Matrix2<Type> result;
        result[0] = cos(radians), result[3] = cos(radians);
        result[1] = -sin(radians), result[2] = sin(radians);
        return result;
    }
    
    static Matrix2<Type> Scale(Vector2<Type> axis){
        Matrix2<Type> result;
        result[0] = axis.x;
        result[3] = axis.y;
        return result;
    }
};

template<class Type>
std::ostream& operator<<(std::ostream& os, Matrix2<Type> mat){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            os << mat(i,j) << " ";
        }
        std::cout << std::endl;
    }
    return os;
}

using Matrix2F = Matrix2<double>;
using Matrix2I = Matrix2<int>;
}
#endif // MATRIX2_H