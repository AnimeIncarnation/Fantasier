#pragma once
#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include "Texture.hpp"
#include "Shaders.hpp"

class Material
{
public:
	std::vector<Texture> textures;
	Shader shader;

	Material(){}
	Material(const std::string& fileName) { textures.push_back(Texture(fileName)); }
	Material(const Texture& tex):textures(),shader(){ textures.push_back(Texture(tex)); }
	Material(const Shader& tex):textures(),shader(tex){ }
	Material(const Texture& tex,const Shader &sh):textures(),shader(sh){ textures.push_back(Texture(tex)); }
	
};

#endif