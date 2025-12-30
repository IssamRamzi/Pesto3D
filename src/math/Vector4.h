#pragma once

#include <iostream>
#include <cmath>

namespace GeoMa {
template<class Type = double>
class Vector4{
public:
	Type x, y, z, t;

	static Vector4<Type> ZERO;
	static Vector4<Type> ONE;

	Vector4() : x(0), y(0), z(0), t(0) {};
	Vector4(Type value) : x(value), y(value), z(value), t(value) {}
	Vector4(Type _x, Type _y, Type _z, Type _t) : x(_x), y(_y), z(_z), t(_t) {}
    
    Vector4<Type> 				Add(const Type another) const { 
        return Vector4<Type>{x + another, y + another, z + another, t + another};
    }

	Vector4<Type> 				Add(const Vector4<Type>& another) const {
		return Vector4<Type>{x + another.x, y + another.y, z + another.z, t + another.t};
	}

	Vector4<Type> 				Sub(const Type another) const {
		return Vector4<Type>{x - another, y - another, z - another, t - another};
	}

	Vector4<Type> 				Sub(const Vector4<Type>& another) const {
		return Vector4<Type>{x - another.x, y - another.y, z - another.z, t - another.t};
	}

	Vector4<Type> 				Mul(const Type another) const {
		return Vector4<Type>{x * another, y * another, z * another, t * another};
	}

	Vector4<Type> 				Mul(const Vector4<Type>& another) const {
		return Vector4<Type>{x * another.x, y * another.y, z * another.z, t * another.t};
	}

	Vector4<Type> 				Div(const Type another) const {
		return Vector4<Type>{x / another, y / another, z / another, t / another};
	}

	Vector4<Type> 				Div(const Vector4<Type>& another) const {
		return Vector4<Type>{x / another.x, y / another.y, z / another.z, t / another.t};
	}

	static Vector4<Type> 		Add(const Vector4<Type>& first, const Vector4<Type>& second) {  
		return Vector4<Type>{first.x + second.x, first.y + second.y, first.z + second.z, first.t + second.t};
	}

	static Vector4<Type> 		Sub(const Vector4<Type>& first, const Vector4<Type>& second) {
		return Vector4<Type>{first.x - second.x, first.y - second.y, first.z - second.z, first.t - second.t};
	}

	static Vector4<Type> 		Mul(const Vector4<Type>& first, const Vector4<Type>& second) {
		return Vector4<Type>{first.x* second.x, first.y* second.y, first.z * second.z, first.t * second.t};
	}

	static Vector4<Type> 		Div(const Vector4<Type>& first, const Vector4<Type>& second) {
		return Vector4<Type>{first.x / second.x, first.y / second.y, first.z / second.z, first.t / second.t};
	}


	// implement operators
	Vector4<Type> operator+(const Vector4<Type>& another) const{
		return Vector4::Add(*this, another);
	}

    Vector4<Type> operator+(const Type another) const{
		return Add(another);
	}

	Vector4<Type> operator-(const Vector4<Type>& another) const{
		return Vector4::Sub(*this, another);
	}

    Vector4<Type> operator-(const Type another) const{
		return Sub(another);
	}

	Vector4<Type> operator*(const Vector4<Type>& another) const{
		return Vector4::Mul(*this, another);
	}

    Vector4<Type> operator*(const Type another) const{
		return Mul(another);
	}
	
	Vector4<Type> operator/(const Vector4<Type>& another) const{
		return Vector4::Div(*this, another);
	}

    Vector4<Type> operator/(const Type another) const{
		return Div(another);
	}

	bool operator==(const Vector4<Type>& another) const{
		return x == another.x && y == another.y && z == another.z && t == another.t;
	}

	bool operator!=(const Vector4<Type>& another) const{
		return !(x == another.x && y == another.y && z == another.z && t == another.t);
	}

	Vector4<Type>				xxxx() const { return Vector4{ x,x,x,x }; }
	Vector4<Type>				yyyy() const { return Vector4{ y,y,y,y }; }
	Vector4<Type>				zzzz() const { return Vector4{ z,z,z,z }; }
	Vector4<Type>				tttt() const { return Vector4{ t,t,t,t }; }

	double						Length() const{
		return sqrt(x*x + y*y + z*z + t*t);
	}

	static double				Length(const Vector4<Type>& vec) {
		return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z + vec.t*vec.t);
	}

	double						LengthSquared() const{
		return x*x + y*y + z*z + t*t;
	}

	static double				LengthSquared(const Vector4<Type>& vec) {
		return vec.x*vec.x + vec.y*vec.y + vec.z*vec.z + vec.t*vec.t;
	}

	double						Magnitude() const{
		return sqrt(x*x + y*y + z*z + t*t);
	}

	double						MagnitudeSquared() const{
		return x*x + y*y + z*z + t*t;

	}

	double						Dot(const Vector4<Type>& another) const{
		return x*another.x + y*another.y + z*another.z + t*another.t;
	}

    static double				Dot(const Vector4<Type>& first, const Vector4<Type>& second){
		return first.x*second.x + first.y*second.y + first.z*second.z + first.t*second.t;
	}

	double						Distance(const Vector4& another) const{
		return Length(Sub(*this, another));
	}

    static double				Distance(const Vector4& first, const Vector4& second){
		return Length(Sub(first, second));
	}

	void						Normalize(){ 
		Type lenght = Length();
		x /= lenght, y /= lenght, z /= lenght, t /= lenght;
	}

	Vector4<Type>				Normalized() const{ 
		Vector4<Type> res{x,y,z,t};
		res.Normalize();
		return res;
	}

	
};

template<class Type>
std::ostream& operator<<(std::ostream& os, const Vector4<Type>& vec){
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.t << ")";
    return os;
}

template<class Type>
Vector4<Type> Vector4<Type>::ZERO{ 0, 0, 0, 0 };
template<class Type>
Vector4<Type> Vector4<Type>::ONE{ 1, 1, 1, 1 };

using Vector4I = Vector4<int>;
using Vector4F = Vector4<double>;
using Point4I = Vector4<int>;
using Point4F = Vector4<double>;

}
