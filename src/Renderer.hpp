#pragma once
#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include "Components/FrameBuffer.hpp"
#include "Components/Scene.hpp"
#include "Components/GameObject.hpp"
#include "Components/Camera.hpp"
#include "Components/Light.hpp"
#include "Output/tgaimage.hpp"
#include "Macros.hpp"


class Renderer
{
private:
	Renderer() {}
	~Renderer();
public:
	static Renderer* instance;
	static Renderer* GetInstance() 
	{
		if (instance == nullptr) 
			instance = new Renderer();
		return instance;
	}
	
	std::vector<Scene> scenes;
	DoubleBuffer* dbuf;
	ZBuffer* zbuf;
	TGAImage image{WIDTH,HEIGHT,TGAImage::RGB};

	
	
	void InitializeScene(const std::string& description);	//�������񡢲��ʣ���װGO������Buffer������camera
	void InitializeBuffer();
	GameObject LoadGO(const std::vector<std::string>& meshSrc, const std::vector<std::string>& textureSrc);	 //����.obj�ļ����������񡢲��ʣ���װGO��
	bool BackfaceCulling(Mesh& mesh,const Camera& camera,int i)const ; //������Camera������ĳ����ĵ�i�������波�Ա����޳�
	void PostProecssing();
	void Rasterization(GameObject& mesh, int indice);
	void RenderScene();

};



#endif