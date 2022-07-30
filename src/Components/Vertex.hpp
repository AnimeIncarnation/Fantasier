#pragma once
#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_


#include "../Geometry/Geometry.hpp"

class Vertex
{
public:
	Vec4f position;
	Vec4f normal;
	Vec2f uv;
	Vec4f color;


	Vertex() :position(), normal() {}
	Vertex(const Vec4f& p,const Vec4f& n) :position(p), normal(n) {}
	Vertex(const Vertex& v) :position(v.position), normal(v.normal) {}
};



#endif 