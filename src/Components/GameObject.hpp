#pragma once

#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP

#include "Material.hpp"
#include "Mesh.hpp"
#include "Transform.hpp"

class GameObject
{
public:
	Transform transform;
	Material material;
	std::vector<Mesh> mesh;
	GameObject():transform(Point()) { };
	GameObject(const Material& ma,const std::vector<Mesh>& me):transform(Point()),material(ma),mesh(me) {  };
	GameObject(const Transform& t,
			   const Material& ma,const std::vector<Mesh>& me)
		:transform(t),material(ma),mesh(me) {  };
};




#endif