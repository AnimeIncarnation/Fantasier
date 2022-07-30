#pragma once
#ifndef _BUFFER_HPP
#define _BUFFER_HPP

#include <limits>
#include "../Geometry/Vector.hpp"
#include "../Macros.hpp"
#include "../Output/tgaimage.hpp"

class DoubleBuffer
{
private:
	Color frontBuffer[WIDTH][HEIGHT];
	Color backBuffer[WIDTH][HEIGHT];
public:

	DoubleBuffer()
	{
		for (int i = 0;i < WIDTH;i++)
		{
			for (int j = 0;j < HEIGHT;j++)
			{
				frontBuffer[i][j] = Color();
				frontBuffer[i][j] = Color();
			}
		}
	}
	bool swaped{ false };
	Color* operator[](int x)
	{
		if (swaped)	return frontBuffer[x];
		else		return backBuffer[x];
	}
	void Swap()
	{
		swaped = !swaped;
	}
	void ClearBack()
	{
		for (int i = 0; i < WIDTH;i++)
		{
			for (int j = 0;j < HEIGHT;j++)
			{
				if (swaped)	frontBuffer[i][j] = Color();
				else		backBuffer[i][j] = Color();
			}
		}
	}
	void Draw(TGAImage& img)
	{
		for (int i = 0;i < WIDTH;i++)
		{
			for (int j = 0;j < HEIGHT;j++)
			{
				if (swaped)	img.set(i, j, backBuffer[i][j]);
				else		img.set(i, j, frontBuffer[i][j]);
			}
		}
		img.flip_vertically(); // i want to have the origin at the left bottom corner of the image
		img.write_tga_file("output.tga");
	}
};		  


class ZBuffer
{
public:
	float zBuffer[WIDTH][HEIGHT];
	ZBuffer()
	{
		for (int i = 0;i < WIDTH;i++)
		{
			for (int j = 0;j < HEIGHT;j++)
			{
				zBuffer[i][j] = -std::numeric_limits<float>::max();
			}
		}
	}

	void Clear()
	{
		for (int i = 0; i < WIDTH;i++)
		{
			for (int j = 0;j < HEIGHT;j++)
			{
				zBuffer[i][j] = -std::numeric_limits<float>::max();
			}
		}
	}
	float* operator[](int x)
	{
		return zBuffer[x];
	}
};


#endif