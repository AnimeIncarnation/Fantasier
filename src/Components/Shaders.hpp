#pragma once
#ifndef _SHADERS_HPP_
#define _SHADERS_HPP_

#include "../Geometry/Vector.hpp"
#include "../Macros.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Vertex.hpp"
#include "Mesh.hpp"

struct v2f
{
	float z{ 0 };
	Vec4f normal;
	Vec2f uv;
	Vec4f color;
	Direction cameraDir;
	std::vector<Texture>* tex;
};


class Shader
{
public:
	virtual ~Shader() {}
	Shader() {}
	Shader(const v2f& res) {}
	Shader(const Shader& s){}
	virtual void  VS(Vec4f& v,const Transform& t ,const Camera& c) { std::cout << "Default Shader(Deleted)" << std::endl; __debugbreak(); }
	virtual Color FS(const v2f& f) { std::cout << "Default Shader(Deleted)" << std::endl;__debugbreak(); return Color(); }
	void CVVCulling()
	{

	}
	
	void MVPTransformation()
	{

	}

	void ViewPortTransformation()
	{

	}

	void ScreenMapping(Vec4f& coords)
	{
		//齐次除法

		//视口变换：从(-1, 1)映射到(WIDTH, HEIGHT)
		coords[0] = (coords[0] + 1.f) * WIDTH  * 0.5f;
		coords[1] = (coords[1] + 1.f) * HEIGHT * 0.5f;
		//std::cout<<"屏幕映射结束 "<<__FILE__ << " : " << __LINE__ << std::endl;
	}

	void VertexShader(Shader&& shader, Vec4f& v, const Transform& t, const Camera& c)
	{
		shader.VS(v,t,c);
	}
	Color FragmentShader(Shader&& shader, const v2f& f)
	{
		return shader.FS(f);
	}
};

class FlatShader : public Shader
{
public:
	void VS(Vec4f& v, const Transform& t, const Camera& c) override
	{
		//MVP变换

		
	}
	Color FS(const v2f& f) override
	{
		return Color{ 1,1,1,1 };
	}
};

class GouraudShader :public Shader
{
public:
	void VS(Vec4f& v, const Transform& t, const Camera& c) override
	{
		//std::cout << "GouraudShader" << __FILE__ << " : " << __LINE__ << std::endl;
	}
	Color FS(const v2f& f) override
	{
		
	}
};

class PhongShader :public Shader
{
public:
	void VS(Vec4f& v, const Transform& go_t, const Camera& c) override
	{
		//std::cout << "PhongShader" << __FILE__ << " : " << __LINE__ << std::endl;
		
		//MV变换
		v = go_t.LocalToWorld() * v;		  //目前效果等于无
		v = c.viewMatrix * v;				  //目前hack了一下
	}
	Color FS(const v2f& f) override
	{
		float intensity = f.cameraDir.normalize_result() * Vec3f(f.normal[0], f.normal[1], f.normal[2]).normalize_result();
		//采样texcoord
		Vec4f diffuse = (*f.tex).at(0).Sample(f.uv.x*(*f.tex).at(0).GetWidth(), f.uv.y* (*f.tex).at(0).GetHeight());
		//return diffuse * std::fabs(intensity);
		return diffuse * std::fabs(intensity);
	}
};


class PBRShader :public Shader
{
public:
	void VS(Vec4f& v, const Transform& t, const Camera& c) override
	{




	}
	Color FS(const v2f& f) override
	{

	}
};



#endif