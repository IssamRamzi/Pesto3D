#pragma once

#include <iostream>
#include <cmath>

namespace GeoMa {
template<class Type = double>
class Vector3{
public:
	Type x, y, z;

	static Vector3<Type> ZERO;
	static Vector3<Type> ONE;
	static Vector3<Type> UP;
	static Vector3<Type> DOWN;
	static Vector3<Type> RIGHT;
	static Vector3<Type> LEFT;
	static Vector3<Type> FRONT;
	static Vector3<Type> BACK;


	Vector3() : x(0), y(0), z(0) {};
	Vector3(Type value) : x(value), y(value), z(value){}
	Vector3(Type _x, Type _y, Type _z) : x(_x), y(_y), z(_z) {}
    
    Vector3<Type> 				Add(const Type another) const { 
        return Vector3<Type>{x + another, y + another, z + another};
    }

	Vector3<Type> 				Add(const Vector3<Type>& another) const {
		return Vector3<Type>{x + another.x, y + another.y, z + another.z};
	}

	Vector3<Type> 				Sub(const Type another) const {
		return Vector3<Type>{x - another, y - another, z - another};
	}

	Vector3<Type> 				Sub(const Vector3<Type>& another) const {
		return Vector3<Type>{x - another.x, y - another.y, z - another.z};
	}

	Vector3<Type> 				Mul(const Type another) const {
		return Vector3<Type>{x * another, y * another, z * another};
	}

	Vector3<Type> 				Mul(const Vector3<Type>& another) const {
		return Vector3<Type>{x * another.x, y * another.y, z * another.z};
	}

	Vector3<Type> 				Div(const Type another) const {
		return Vector3<Type>{x / another, y / another, z / another};
	}

	Vector3<Type> 				Div(const Vector3<Type>& another) const {
		return Vector3<Type>{x / another.x, y / another.y, z / another.z};
	}

	static Vector3<Type> 		Add(const Vector3<Type>& first, const Vector3<Type>& second) {  
		return Vector3<Type>{first.x + second.x, first.y + second.y, first.z + second.z};
	}

	static Vector3<Type> 		Sub(const Vector3<Type>& first, const Vector3<Type>& second) {
		return Vector3<Type>{first.x - second.x, first.y - second.y, first.z - second.z};
	}

	static Vector3<Type> 		Mul(const Vector3<Type>& first, const Vector3<Type>& second) {
		return Vector3<Type>{first.x* second.x, first.y* second.y, first.z * second.z};
	}

	static Vector3<Type> 		Div(const Vector3<Type>& first, const Vector3<Type>& second) {
		return Vector3<Type>{first.x / second.x, first.y / second.y, first.z / second.z};
	}


	// implement operators
	Vector3<Type> operator+(const Vector3<Type>& another) const{
		return Vector3::Add(*this, another);
	}

    Vector3<Type> operator+(const Type another) const{
		return Add(another);
	}

	Vector3<Type> operator-(const Vector3<Type>& another) const{
		return Vector3::Sub(*this, another);
	}

    Vector3<Type> operator-(const Type another) const{
		return Sub(another);
	}

	Vector3<Type> operator*(const Vector3<Type>& another) const{
		return Vector3::Mul(*this, another);
	}

    Vector3<Type> operator*(const Type another) const{
		return Mul(another);
	}
	
	Vector3<Type> operator/(const Vector3<Type>& another) const{
		return Vector3::Div(*this, another);
	}

    Vector3<Type> operator/(const Type another) const{
		return Div(another);
	}

	bool operator==(const Vector3<Type>& another) const{
		return x == another.x && y == another.y && z == another.z;
	}

	bool operator!=(const Vector3<Type>& another) const{
		return !(x == another.x && y == another.y && z == another.z);
	}


	Vector3<Type>				xxx() const { return Vector3{ x,x,x }; }
	Vector3<Type>				yyy() const { return Vector3{ y,y,y }; }
	Vector3<Type>				zzz() const { return Vector3{ z,z,z }; }


	double						Length() const{
		return sqrt(x*x + y*y + z*z);
	}

	static double				Length(const Vector3<Type>& vec) {
		return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	}

	double						LengthSquared() const{
		return x*x + y*y + z*z;
	}

	static double				LengthSquared(const Vector3<Type>& vec) {
		return vec.x*vec.x + vec.y*vec.y + vec.z*vec.z;
	}

	double						Magnitude() const{
		return sqrt(x*x + y*y + z*z);
	}

	double						MagnitudeSquared() const{
		return x*x + y*y + z*z;

	}

	double						Dot(const Vector3<Type>& another) const{
		return x*another.x + y*another.y + z*another.z;
	}

    static double				Dot(const Vector3<Type>& first, const Vector3<Type>& second){
		return first.x*second.x + first.y*second.y + first.z*second.z;
	}

    // TODO
	Type						Cross(const Vector3<Type>& another) const{
		return x*another.y - y*another.x;
	}

    // TODO
	static Type 				Cross(const Vector3<Type>& first, const Vector3<Type>& second){
		return first.x*second.y - first.y*second.x;
	}

	double						Distance(const Vector3& another) const{
		return Length(Sub(*this, another));
	}

    static double				Distance(const Vector3& first, const Vector3& second){
		return Length(Sub(first, second));
	}

	void						Normalize(){ 
		Type lenght = Length();
		x /= lenght, y /= lenght, z /= lenght;
	}

	Vector3<Type>				Normalized() const{ 
		Vector3<Type> res{x,y,z};
		res.Normalize();
		return res;
	}

	
};

template<class Type>
std::ostream& operator<<(std::ostream& os, const Vector3<Type>& vec){
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

template<class Type>
Vector3<Type> Vector3<Type>::ZERO{ 0, 0, 0 };
template<class Type>
Vector3<Type> Vector3<Type>::ONE{ 1, 1, 1 };
template<class Type>
Vector3<Type> Vector3<Type>::UP{0, 1, 0};
template<class Type>
Vector3<Type> Vector3<Type>::DOWN{ 0, -1, 0 };
template<class Type>
Vector3<Type> Vector3<Type>::RIGHT{ 1, 0, 0 };
template<class Type>
Vector3<Type> Vector3<Type>::LEFT{ -1, 0, 0 };
template<class Type>
Vector3<Type> Vector3<Type>::FRONT{ 0, 0, 1 };
template<class Type>
Vector3<Type> Vector3<Type>::BACK{ 0, 0, -1 };

using Vector3I = Vector3<int>;
using Vector3F = Vector3<double>;
using Point3I = Vector3<int>;
using Point3F = Vector3<double>;

}
