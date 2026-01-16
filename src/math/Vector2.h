#pragma once

#include <iostream>
#include <cmath>

namespace GeoMa {
template<class Type = double>
class Vector2{
public:
	Type x, y;

	static Vector2<Type> ZERO;
	static Vector2<Type> ONE;
	static Vector2<Type> UP;
	static Vector2<Type> DOWN;
	static Vector2<Type> RIGHT;
	static Vector2<Type> LEFT;


	Vector2() : x(0), y(0) {};
	Vector2(Type value) : x(value), y(value){}
	Vector2(Type _x, Type _y) : x(_x), y(_y) {}

	Vector2<Type> 				Add(const Vector2<Type>& another) const {
		return Vector2<Type>{x + another.x, y + another.y};
	}

	Vector2<Type> 				Add(const Type another) const { 
		return Vector2<Type>{x + another, y + another};
	}

	Vector2<Type> 				Sub(const Type another) const {
		return Vector2<Type>{x - another, y - another};
	}

	Vector2<Type> 				Sub(const Vector2<Type>& another) const {
		return Vector2<Type>{x - another.x, y - another.y};
	}

	Vector2<Type> 				Mul(const Type another) const {
		return Vector2<Type>{x * another, y * another};
	}

	Vector2<Type> 				Mul(const Vector2<Type>& another) const {
		return Vector2<Type>{x * another.x, y * another.y};
	}

	Vector2<Type> 				Div(const Type another) const {
		return Vector2<Type>{x / another, y / another};
	}

	Vector2<Type> 				Div(const Vector2<Type>& another) const {
		return Vector2<Type>{x / another.x, y / another.y};
	}

	static Vector2<Type> 		Add(const Vector2<Type>& first, const Vector2<Type>& second) {  
		return Vector2<Type>{first.x + second.x, first.y + second.y};
	}

	static Vector2<Type> 		Sub(const Vector2<Type>& first, const Vector2<Type>& second) {
		return Vector2<Type>{first.x - second.x, first.y - second.y};
	}

	static Vector2<Type> 		Mul(const Vector2<Type>& first, const Vector2<Type>& second) {
		return Vector2<Type>{first.x* second.x, first.y* second.y};
	}

	static Vector2<Type> 		Div(const Vector2<Type>& first, const Vector2<Type>& second) {
		return Vector2<Type>{first.x / second.x, first.y / second.y};
	}


	// impl operators
	Vector2<Type> operator+(const Vector2<Type>& another) const{
		return Vector2::Add(*this, another);
	}

	Vector2<Type> operator+(const Type another) const{
		return Add(another);
	}

	Vector2<Type> operator-(const Vector2<Type>& another) const{
		return Vector2::Sub(*this, another);
	}

	Vector2<Type> operator-(const Type another) const{
		return Sub(another);
	}

	Vector2<Type> operator*(const Vector2<Type>& another) const{
		return Vector2::Mul(*this, another);
	}

	Vector2<Type> operator*(const Type another) const{
		return Mul(another);
	}
	
	Vector2<Type> operator/(const Vector2<Type>& another) const{
		return Vector2::Div(*this, another);
	}

	Vector2<Type> operator/(const Type another) const{
		return Div(another);
	}

	bool operator==(const Vector2<Type>& another) const{
		return x == another.x && y == another.y;
	}

	bool operator!=(const Vector2<Type>& another) const{
		return !(x == another.x && y == another.y);
	}


	Vector2<Type>				xy() const { return Vector2{ x,y }; }
	Vector2<Type>				xx() const { return Vector2{ x,x }; }
	Vector2<Type>				yx() const { return Vector2{ y,x }; }
	Vector2<Type>				yy() const { return Vector2{ y,y }; }


	double						Length() const{
		return sqrt(x*x + y*y);
	}

	static double				Length(const Vector2<Type>& vec) {
		return sqrt(vec.x*vec.x + vec.y*vec.y);
	}

	double						LengthSquared() const{
		return x*x + y*y;
	}

	static double				LengthSquared(const Vector2<Type>& vec) {
		return vec.x*vec.x + vec.y*vec.y;
	}

	double						Magnitude() const{
		return sqrt(x*x + y*y);
	}

	double						MagnitudeSquared() const{
		return x*x + y*y;

	}

	double						Dot(const Vector2<Type>& another) const{
		return x*another.x + y*another.y;
	}

	static double				Dot(const Vector2<Type>& first, const Vector2<Type>& second){
		return first.x*second.x + first.y*second.y;
	}

	Type						Cross(const Vector2<Type>& another) const{
		return x*another.y - y*another.x;
	}

	static Type 				Cross(const Vector2<Type>& first, const Vector2<Type>& second){
		return first.x*second.y - first.y*second.x;
	}

	double						Distance(const Vector2& another) const{
		return Length(Sub(*this, another));
	}

	static double				Distance(const Vector2& first, const Vector2& second){
		return Length(Sub(first, second));
	}

	void						Normalize(){ 
		Type lenght = Length();
		x /= lenght, y /= lenght;
	}

	Vector2<Type>				Normalized() const{ 
		Vector2<Type> res{x,y};
		res.Normalize();
		return res;
	}

	
};

template<class Type>
std::ostream& operator<<(std::ostream& os, const Vector2<Type>& vec){
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

template<class Type>
Vector2<Type> Vector2<Type>::ZERO{ 0, 0 };
template<class Type>
Vector2<Type> Vector2<Type>::ONE{ 1, 1 };
template<class Type>
Vector2<Type> Vector2<Type>::UP{0, 1};
template<class Type>
Vector2<Type> Vector2<Type>::DOWN{ 0, -1 };
template<class Type>
Vector2<Type> Vector2<Type>::RIGHT{ 1, 0 };
template<class Type>
Vector2<Type> Vector2<Type>::LEFT{ -1, 0 };

using Vector2I = Vector2<int>;
using Vector2F = Vector2<float>;
using Point2I = Vector2<int>;
using Point2F = Vector2<float>;

}
