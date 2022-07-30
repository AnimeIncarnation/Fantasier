#pragma once
#ifndef __GEOMETRY_HPP__
#define __GEOMETRY_HPP__

#include "Vector.hpp"
#include "Matrix.hpp"



/*
 * Saturate
 */
template <class T>	  inline
T saturate(T value)
{
	static_assert(false);
}	  

template <>			inline
float saturate<float>(float value)
{
	if (value >= 1) return 1;
	else if (value <= 0) return 0;
	return value;
}
template <>			   inline
double saturate<double>(double value)
{
	if (value >= 1) return 1;
	else if (value <= 0) return 0;
	return value;
}

/* 
 * Lerp
 */
template<class T>  inline
T lerp(T left,T right ,T weight)
{
	static_assert(false);
}	

template<>			  inline
float lerp<float>(float left,float right ,float weight)
{
	return left + (right - left) * weight;
}

template<>			   inline
double lerp<double>(double left, double right, double weight)
{
	return left + (right - left) * weight;
}




/*
 * Barycentric Coordinate Calculation
 */
inline
Vec3f Barycentric(const Vec4f(&v)[3], const Vec2i& p)
{
	Vec3f cross = Vec3f(v[1].x - v[0].x, v[2].x - v[0].x, v[0].x - p.x) ^
				  Vec3f(v[1].y - v[0].y, v[2].y - v[0].y, v[0].y - p.y);
	if (cross.z == 0) { return Vec3f(-1, 1, 1); }//随便return一个带有负值的即可
	//注意重心坐标算出来的u是B的v是C的，1-u-v才是A的，所以要按照这样的顺序return
	return Vec3f(1. - (cross.x + cross.y) / (float)cross.z, cross.x / (float)cross.z, cross.y / (float)cross.z);
}




#endif 