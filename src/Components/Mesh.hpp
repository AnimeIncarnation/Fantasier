#pragma once
#ifndef __Mesh_HPP__
#define __Mesh_HPP__

#include <vector>
#include "../Geometry/Vector.hpp"

class Mesh 
{
private:
	//Homogeneous Coords
	std::vector<Vec4f> verts;
	std::vector<Vec4f> norms;
	std::vector<Vec2f> texcoords;

	//Per Triangle
	std::vector<std::vector<int> > vertInds;
	std::vector<std::vector<int> > normInds;
	std::vector<std::vector<int> > texcoordInds;

public:
	//Only support .obj files
	Mesh();
	Mesh(std::string filename);
	void SetMesh(std::string filename);
	int VertexNum();
	int IndiceNum();
	Vec4f& GetVerts(int i);
	Vec4f& GetNorms(int i);
	Vec2f& GetTexcoords(int i);
	std::vector<int> GetVInds(int idx) const;
	std::vector<int> GetNInds(int idx) const;
	std::vector<int> GetTInds(int idx) const;
	void Clear();
};


#endif //__Mesh_H__