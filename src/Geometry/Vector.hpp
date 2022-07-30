#pragma once
#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_


#include <cmath>
#include <iostream>



template <class T,int N>
struct Vector 
{
	union {
		struct { T x, y, z, w; };
		T raw[N];		 
	};

	float length() const { return std::sqrt(x * x + y * y + z * z); }
	Vector<T, N>& normalize(float l = 1) 
	{ 
		float leng; 
		if ((leng = length()) != 0)  
			*this = (*this) * (l / leng); 
		return *this; 
	}
	Vector<T, N>  normalize_result(float l = 1) const 
	{
		float leng;
		if ((leng = length()) != 0)
		{
			Vector<T,N> res = (*this) * (l / leng);
			return res; 
		}
		return Vector<T,N>();
	}


	Vector()					   : x(0),  y(0),  z(0),  w(0)  {}
	Vector(T _x, T _y)			   : x(_x), y(_y), z(0),  w(0)  {}
	Vector(T _x, T _y, T _z)	   : x(_x), y(_y), z(_z), w(0)  {}
	Vector(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
	Vector<T,N>  operator ^ (const Vector<T,N>& v) const { return Vector<T,N>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
	Vector<T,N>  operator + (const Vector<T,N>& v) const { return Vector<T,N>(x + v.x, y + v.y, z + v.z); }
	Vector<T,N>  operator +=(const Vector<T, N>& v)      { return *this = *this + v; }
	Vector<T,N>  operator - (const Vector<T,N>& v) const { return Vector<T,N>(x - v.x, y - v.y, z - v.z); }
	T            operator * (const Vector<T,N>& v) const { return x * v.x + y * v.y + z * v.z; }
	Vector<T,N>  operator * (float f)              const { return Vector<T,N>(x * f, y * f, z * f); }
	T&           operator [](int index);
	const T&     operator [](int index)const;

};


typedef Vector<int,   2> Vec2i;
typedef Vector<float, 2> Vec2f;
typedef Vector<int,   3> Vec3i;
typedef Vector<float, 3> Vec3f;
typedef Vector<int,   4> Vec4i;
typedef Vector<float, 4> Vec4f;

typedef Vec3f Point;
typedef Vec3f Direction;
typedef Vec4f Color;



template<class T,int N>
T& Vector<T,N>::operator [](int index)
{
	switch (index)
	{
	case 0:return x;break;
	case 1:return y;break;
	case 2:return z;break;
	case 3:return w;break;
	default: return raw[index];
	}
}

template<class T,int N>
const T& Vector<T,N>::operator [](int index)const
{
	switch (index)
	{
	case 0:return x;break;
	case 1:return y;break;
	case 2:return z;break;
	case 3:return w;break;
	default: return raw[index];
	}
}

template <class T>
std::ostream& operator<<(std::ostream& s, const Vector<T,2>& v)
{
	s << "(" << v.x << ", " << v.y << ")\n";
	return s;
}

template <class T>
std::ostream& operator<<(std::ostream& s, const Vector<T,3>& v)
{
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
	return s;
}			

template <class T>
std::ostream& operator<<(std::ostream& s, const Vector<T,4>& v)
{
	s << "(" << v.x << ", " << v.y << ", " << v.z << ", "<< v.w << ")\n";
	return s;
}


#endif 