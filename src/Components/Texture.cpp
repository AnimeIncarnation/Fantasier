#include "Texture.hpp"


Texture::Texture(const std::string& fileName)
{
	if (!texture.read_tga_file(fileName.c_str()))
		__debugbreak();
}
void Texture::LoadTexture(const std::string& fileName)
{
	if (!texture.read_tga_file(fileName.c_str()))
		__debugbreak();
}
Color Texture::Sample(float u, float v)const
{
	TGAColor temp(texture.get(u,v));
	Color res = Color(temp.r, temp.g, temp.b, temp.a);
	return res;
}
;