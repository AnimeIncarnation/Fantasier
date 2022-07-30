////2022.7.5
////照着TinyRenderer构建你的第一个软渲染器项目把！
//
//
//
//#include <algorithm>
//#include "Output/tgaimage.hpp"
//#include "Geometry/geometry.hpp"
//#include "Components/Mesh.hpp"
//#include "Macros.hpp"
//#include "Renderer.hpp"
//#include "Components/Light.hpp"
//
//
//
//
//
//
//void line(int x0, int y0, int x1, int y1, TGAImage& image,const TGAColor& color)
//{
//	bool steep = false;
//	if (std::abs(x1 - x0) < std::abs(y1 - y0))
//	{
//		//把x值和y值均放在【x】的位置上进行处理，代码简洁化
//		std::swap(x0, y0);
//		std::swap(x1, y1);
//		steep = true;
//	}
//	//使x0位置一定小于x1位置
//	if (x0 >= x1)
//	{
//		std::swap(x0, x1);
//		std::swap(y0, y1);
//	};
//	const int dx = x1 - x0;			
//	const int dy = y1 - y0;
//	const int offsetChange = std::fabs(dy) * 2;
//	int offset = 0;
//	for (int x = x0,y=y0; x <= x1; x++)
//	{
//		//如果斜率大于1，以y为单位画线
//		if (steep)
//			image.set(y, x, color);
//		//如果斜率小于1，以x为单位画线
//		else
//			image.set(x, y, color);
//		offset += offsetChange;
//		if (offset >= dx)			  //2dy>=dx说明dy/dx>=0.5说明x+1后y大于0.5，y应当加一
//		{
//			offset -= 2 * dx;
//			y += (y1 > y0 ? 1 : -1);
//		}
//	}
//}
//
//void triangledge(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage& image, const TGAColor& color)
//{
//	line(v0.x, v0.y, v1.x, v1.y, image, color);
//	line(v1.x, v1.y, v2.x, v2.y, image, color);
//	line(v2.x, v2.y, v0.x, v0.y, image, color);
//}
//Vec3f barycentric(const Vec2i(&v)[3], const Vec2i& p)
//{
//	Vec3i cross = Vec3i(v[1].x - v[0].x, v[2].x - v[0].x, v[0].x - p.x) ^
//		Vec3i(v[1].y - v[0].y, v[2].y - v[0].y, v[0].y - p.y);
//	if (cross.z == 0) { return Vec3f(-1, 1, 1); }	  //随便return一个带有负值的即可
//	//注意重心坐标算出来的u是B的v是C的，1-u-v才是A的，所以要按照这样的顺序return
//	return Vec3f(1. - (cross.x + cross.y) / (float)cross.z, cross.x / (float)cross.z, cross.y / (float)cross.z);
//}			
//Vec3f barycentric(const Vec3f(&v)[3], const Vec2i& p)
//{
//	Vec3f cross = Vec3f(v[1].x - v[0].x, v[2].x - v[0].x, v[0].x - p.x) ^
//		Vec3f(v[1].y - v[0].y, v[2].y - v[0].y, v[0].y - p.y);
//	if (cross.z == 0) { return Vec3f(-1, 1, 1); }//随便return一个带有负值的即可
//	//注意重心坐标算出来的u是B的v是C的，1-u-v才是A的，所以要按照这样的顺序return
//	return Vec3f(1. - (cross.x + cross.y) / (float)cross.z, cross.x / (float)cross.z, cross.y / (float)cross.z);
//}
//void rasterizeTriangle1(Vec2i v[3], TGAImage& image, const TGAColor& color)
//{
//	//整体思路：按照三角形三个顶点的y进行排序，以012和02作为边界逐行画线。
//	//注意事项：boundings和对boundings的累加必须为float。右值除法计算的其中一员必须为float。
//	std::sort(v, v + 3, [](Vec2i& x, Vec2i& y)->bool {return x.y < y.y;});
//	if (v[0].y == v[2].y)	
//	{
//		std::cout << "ERROR: You're Not Rasterzing a Triangle!" << " at "
//		<<__FILE__ << ": " << __LINE__ << std::endl; __debugbreak(); 
//	}
//	float dx01;
//	if (v[1].y == v[0].y)	dx01 = v[1].x - v[0].x; 
//	else					dx01 = (v[1].x - v[0].x) / (float)(v[1].y - v[0].y);
//	float dx12 = (v[2].x - v[1].x) / (float)(v[2].y - v[1].y);
//	float dx02 = (v[2].x - v[0].x) / (float)(v[2].y - v[0].y);
//	float bound012 = v[0].x, bound02 = v[0].x;
//
//	for (int i = v[0].y;i <= v[2].y;i++)
//	{
//		if (i < v[1].y || i == v[0].y)
//		{
//			bound012 += dx01;
//			bound02  += dx02;
//			line(std::round(bound012),i,std::round(bound02),i,image,color);
//		}
//		else
//		{
//			bound012 += dx12;
//			bound02 += dx02;
//			line(std::round(bound012),i,std::round(bound02),i,image,color);
//		}
//	}
//}
//void rasterizeTriangle2(const Vec2i(&v)[3], TGAImage& image, const TGAColor& color)
//{
//	//Find the bounding box.
//	int x_min = std::min(std::min(v[0].x, v[1].x), v[2].x);
//	int x_max = std::max(std::max(v[0].x, v[1].x), v[2].x);
//	int y_min = std::min(std::min(v[0].y, v[1].y), v[2].y);
//	int y_max = std::max(std::max(v[0].y, v[1].y), v[2].y);
//	for (int i = x_min;i < x_max;i++)
//	{
//		for (int j = y_min;j < y_max;j++)
//		{
//			//Use barycentric coordinates to find fragments in the triangle.
//			Vec2i p(i, j);
//			Vec3f g = barycentric(v, p);
//			if (g.x < 0 || g.y < 0 || g.z < 0)	continue;
//			image.set(i, j, color);
//		}
//	}
//}
//void rasterize_triangle_orthographic(const Vec3f(&v)[3], float* zbuffer, TGAImage& image, const TGAColor& color)
//{
//	float x_min = std::min(std::min(v[0].x, v[1].x), v[2].x);
//	float x_max = std::max(std::max(v[0].x, v[1].x), v[2].x);
//	float y_min = std::min(std::min(v[0].y, v[1].y), v[2].y);
//	float y_max = std::max(std::max(v[0].y, v[1].y), v[2].y);
//	for (int i = x_min;i < x_max+.5f;i++)
//	{
//		for (int j = y_min;j < y_max+.5f;j++)
//		{
//			//Use barycentric coordinates to find fragments in the triangle.
//			Vec2i p(i, j);
//			Vec3f g = barycentric(v, p);
//			if (g.x < 0 || g.y < 0 || g.z < 0)	continue;
//
//
//
//			//Use barycentric coordinates to get z value interpolated.
//			float z_triangle = 0;
//			for (int k = 0;k < 3;k++) { z_triangle += g[k] * v[k].z; }
//
//
//			//Use the z-buffer to show the 遮挡关系
//			if (zbuffer[i + j * WIDTH] <  z_triangle)
//			{
//				//std::cout << color.r<<"，"<<color.g<<"，"<<color.b << std::endl;
//				zbuffer[i + j * WIDTH] = z_triangle;
//				image.set(i, j, color);
//			}
//		}
//	}
//}
//
//
//
//
//
//
//
//
//
//
//void drawGetVInds(TGAImage& image, const TGAColor& color)
//{
//	//遍历face的三角面
//	Mesh* mesh = new Mesh("models/african_head.obj");
//	for (int i = 0; i < mesh->VertexNum(); i++) 
//	{
//		//得到面部的每一个三角面的顶点index
//		std::vector<int> face = mesh->GetVInds(i);
//		for (int j = 0; j < 3; j++) 
//		{
//			//对于每个顶点，获取它和它后面那个顶点
//			Vec3f v0 = Vec3f(mesh->GetVerts(face[j])[0], mesh->GetVerts(face[j])[1], mesh->GetVerts(face[j])[2]);
//			Vec3f v1 = Vec3f(mesh->GetVerts(face[(j + 1) % 3])[0], mesh->GetVerts(face[(j + 1) % 3])[1], mesh->GetVerts(face[(j + 1) % 3])[2]);
//
//			//将顶点进行坐标转换，从NDC空间[-1,1],[-1,1]映射到[0,WIDTH],[0,hight]
//			int x0 = (v0.x + 1.)/2 * WIDTH ;
//			int y0 = (v0.y + 1.)/2 * HEIGHT;
//			int x1 = (v1.x + 1.)/2 * WIDTH ;
//			int y1 = (v1.y + 1.)/2 * HEIGHT;
//			line(x0, y0, x1, y1, image, color);
//		}
//	}
//	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
//	image.write_tga_file("output.tga");
//	delete mesh;
//
//}
//void drawface_solid_lambert(TGAImage& image)	//lambert的目的是进行伪遮挡剔除
//{
//	Vec3f lightdir(0,0,-1);
//
//	Mesh* mesh = new Mesh("models/african_head.obj");
//	for (int i = 0; i < mesh->VertexNum(); i++)
//	{
//		//得到面部的每一个三角面的顶点index
//		std::vector<int> face = mesh->GetVInds(i);
//		Vec3f world_coords[3]{};
//		Vec2i screen_coords[3]{};
//		for (int j = 0; j < 3; j++)
//		{
//			//根据index获取三角形顶点
//			world_coords[j] = Vec3f(mesh->GetVerts(face.at(j))[0], mesh->GetVerts(face.at(j))[1], mesh->GetVerts(face.at(j))[2]);
//			//从[-1,1]进行normalization
//			screen_coords[j].x = (world_coords[j].x + 1) * WIDTH / 2;
//			screen_coords[j].y = (world_coords[j].y + 1) * HEIGHT / 2;
//		}
//		//到这一步可以理解为坐标转换完毕，下一步进行进入到顶点着色器的Shading阶段
//		Vec3f normal = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
//		normal.normalize();
//		float light_intensity = lightdir * normal;
//#ifdef _HALF_LAMBERT_
//		light_intensity = light_intensity * 0.5 + 0.5;
//#endif
//		if (light_intensity > 0)
//		{
//			std::cout << "法线方向：" << normal << std::endl;
//			rasterizeTriangle2(screen_coords,image, TGAColor(rand() % 255 * light_intensity, rand() % 255 * light_intensity, rand() % 255 * light_intensity, 255));
//
//		}
//	}
//	delete mesh;
//}		 
//
//
//
//void drawface_solid_zbuffer(float* zbuffer, TGAImage& image, const TGAColor& color)
//{
//	DirectionalLight light({ 0, 0, -1 });
//	Mesh* mesh = new Mesh("models/african_head.obj");
//	for (int i = 0; i < mesh->IndiceNum(); i++)
//	{
//		//得到面部的每一个三角面的顶点index
//		std::vector<int> inds = mesh->GetVInds(i);
//		Vec3f world_coords[3]{};
//		Vec3f screen_coords[3]{};
//		for (int j = 0; j < 3; j++)
//		{
//			//根据index获取三角形顶点，此处获得的坐标是“模型空间”对吧
//			world_coords[j] = Vec3f(mesh->GetVerts(inds.at(j))[0], mesh->GetVerts(inds.at(j))[1], mesh->GetVerts(inds.at(j))[2]);;
//			//从[-1,1]进行normalize到[0,1]变换为屏幕坐标
//			screen_coords[j].x = (world_coords[j].x + 1) * WIDTH / 2;
//			screen_coords[j].y = (world_coords[j].y + 1) * HEIGHT / 2;
//		}
//		Vec3f normal = (world_coords[2]-world_coords[1])^(world_coords[1]-world_coords[0]);
//		normal.normalize();
//		float cos = light.dir * normal;
//
//		if (cos > 0)	//为什么正面看物体时明明开了z-buffer，还是需要背面剔除才能达到正确效果？？？？？？？？？？？？？？？？？？？？？？？？？？？？？、
//		{
//			rasterize_triangle_orthographic(screen_coords,zbuffer,image, TGAColor(255 * cos, 255 * cos, 255 * cos, 255));
//		}
//
//	}
//	delete mesh;
//}
//
//
//
//
//
//
//
//
//int main(int argc, char** argv)
//{
//	/*	tgaimage.h用法:
//	*	const TGAColor WHITE = TGAColor(255, 255, 255, 255);
//	*	const TGAColor red = TGAColor(255, 0, 0, 255);
//	*	TGAImage image(100, 100, TGAImage::RGB);	//创建一个100x100的tga图片文件
//	*	image.set(52, 41, red);						//画点（注意此时就是在image上画。image是逻辑图像，只需最后调用write_tga_file将逻辑图像复制到实际文件中即可）
//	*	image.flip_vertically();					// i want to have the origin at the left bottom corner of the image
//	*	image.write_tga_file("output.tga");
//	*/
//
//	//initialization stage
//	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);
//	float* zbuffer = new float[WIDTH * HEIGHT];
//
//
//
//	//working stage
//
//	
//	//drawface_solid_lambert(image);
//	drawface_solid_zbuffer(zbuffer, image, WHITE);
//
//
//	//final stage
//	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
//	image.write_tga_file("output.tga");
//	delete zbuffer;
//
//	return 0;
//}