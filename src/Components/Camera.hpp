#pragma once
#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "../Macros.hpp"
#include "../Geometry/Geometry.hpp"
#include "Transform.hpp"

class Camera
{
public:
	Transform transform;
	Direction dir{0,0,-1};
	float aspect{1};
	float FOV{50};
	float nearZ{0};
	float farZ{20};
	Matrix4f viewMatrix;
	Matrix4f projectionMatrix;
	Vec2f& viewportTransformation(Vec2f& v)
	{
		v.x = (v.x + 1) / 2.f * WIDTH;
		v.y = (v.y + 1) / 2.f * HEIGHT;
		return v;
	}

	Camera(const Point& pos,const Direction& d = Direction(0,0,-1)):transform(pos),dir(d)
	{
		//Calculate Matrix......
		//viewMatrix = transform.WorldToLocal();
		viewMatrix = Matrix4f{
			1,0,0,0,
			0,1,0,0,
			0,0,1,-transform.position.z,
			0,0,0,1
		};
		projectionMatrix = Matrix4f{
			1/(aspect*std::tan(FOV/2)),0,0,0,
			0,1/std::tan(FOV/2),0,0,
			0,0,-(farZ+nearZ)/(farZ-nearZ),-2*farZ*nearZ/(farZ-nearZ),
			0,0,1,0
		};
	}
	Camera(const Camera& c) 
		:transform(c.transform),dir(c.dir),aspect(c.aspect), FOV(c.FOV) ,nearZ(c.nearZ),farZ(c.farZ),viewMatrix(c.viewMatrix),projectionMatrix(c.projectionMatrix){}
};


#endif 