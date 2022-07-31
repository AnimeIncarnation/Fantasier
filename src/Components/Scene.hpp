#pragma once
#ifndef _SCENE_HPP
#define _SCENE_HPP

#include "GameObject.hpp"
#include "Light.hpp"
class Scene
{
private:
	std::vector<GameObject> gameObjects;
	std::vector<Light> lights;
	std::vector<Camera> cameras;

public:
	Scene(const Camera& mainCamera) 
	{ 
		cameras.push_back(mainCamera); 
	}


	Camera& GetMainCamera()
	{
		//Ö÷Ïà»ú
		return cameras.at(0);
	}
	std::vector<GameObject>& GetGO()
	{
		return gameObjects;
	}
	std::vector<Light>& GetLights()
	{
		return lights;
	}

	void PushGO(const GameObject& go)
	{
		gameObjects.push_back(go);
	}
	void PushLight(const Light& l)
	{
		lights.push_back(l);
	}
	void PushCamera(const Camera& c)
	{
		cameras.push_back(c);
	}
	void ChangeMainCamera(const Camera& c)
	{
		cameras.at(0) = c;
	}
};


#endif