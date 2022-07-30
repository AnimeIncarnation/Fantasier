#pragma once

#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP

#include "Material.hpp"
#include "Mesh.hpp"

class GameObject
{
public:
	Material material;
	std::vector<Mesh> mesh;
	GameObject() { };
	GameObject(const Material& ma,const std::vector<Mesh>& me):material(ma),mesh(me) {  };
};




#endif