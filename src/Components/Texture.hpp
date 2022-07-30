#pragma once
#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "../Macros.hpp"
#include "../Geometry/Geometry.hpp"
#include "../Output/tgaimage.hpp"


class Texture
{
private:
	TGAImage texture;


public:
	Texture() {}
	Texture(const std::string& fileName);
	void LoadTexture(const std::string& path);
	Color Sample(float u, float v)const;
	int GetWidth()const { return texture.get_width(); }
	int GetHeight()const { return texture.get_height(); }

};

#endif