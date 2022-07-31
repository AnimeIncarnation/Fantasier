#pragma once
#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include "../Geometry/Matrix.hpp"

class Transform
{
public:
	Point position;
	Direction right;
	Direction up;
	Direction forward;
	//采用Opengl坐标系
	Transform(const Point& pos,
			  const Direction& r = Direction(1, 0, 0), 
			  const Direction& u = Direction(0, 1, 0), const Direction& f = Direction(0, 0, 1))
		:position(pos),right(r),up(u),forward(f)
	{
		localToWorld = {
			right[0],up[0],forward[0],-position.x,
			right[1],up[1],forward[1],-position.y,
			right[2],up[2],forward[2],-position.z,
			0,0,0,1
		};
		worldToLocal = localToWorld.inverse();
	}

	const Matrix4f& WorldToLocal()const { return worldToLocal; }
	const Matrix4f& LocalToWorld()const { return localToWorld; }
	
private:
	Matrix4f worldToLocal;
	Matrix4f localToWorld;
	
};

#endif