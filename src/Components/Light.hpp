#pragma once

#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "../Geometry/Geometry.hpp"

class DirectionalLight
{
public:
	
	Direction dir;		//Vec3f
	Color color;		//Vec4f

	DirectionalLight() {}
	DirectionalLight(const Direction& d,const Color& c = Color(1,1,1,1)):dir(d),color(c) {}
	DirectionalLight(const DirectionalLight& l) : dir(l.dir),color(l.color) {}
};

typedef DirectionalLight Light;


class PointLight
{
public:
	Point pos;				//Vec3f
	Color color;			//Vec4f
	float intensity;

	PointLight() :pos(0,0,0), color(1,1,1,1),intensity(1) {}
	PointLight(const Point& p, const Direction& d, const Color c = Vec4f()) :pos(p), color(c) {}
	PointLight(const PointLight& l) :pos(l.pos), color(l.color) {}
};


#endif