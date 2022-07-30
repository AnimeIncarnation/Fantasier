#pragma once
#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_


#include "../Geometry/Geometry.hpp"
#include "../Geometry/Matrix.hpp"

class Camera
{
public:
	Point pos;
	Direction dir{0,0,-1};
	float aspect{1};
	float FOV{50};
	Matrix4f viewMatrix;
	Matrix4f projectionMatrix;
	Matrix4f viewportMatrix;

	Camera()
	{
		//Calculate Matrix......
	}
	Camera(const Point& p,const Direction& d,float a = 1,float f = 50):pos(p),dir(d),aspect(a),FOV(f) {}
	Camera(const Camera& c) :pos(c.pos),dir(c.dir),aspect(c.aspect), FOV(c.FOV) {}
	void SetPosition(const Point& p) { pos = p; }
	void SetDirection(const Direction& d) { dir = d; }
	void SetAspect(float a) { aspect = a; }
	void SetFOV(float f) {FOV = f; }



};


#endif 