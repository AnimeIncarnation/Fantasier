#include <iostream>
#include "Renderer.hpp"


int main()
{
	Renderer::GetInstance()->InitializeScene("default");
	Renderer::GetInstance()->InitializeBuffer();
	Renderer::GetInstance()->RenderScene();
	std::cout << "渲染流程已完成。" << std::endl;
	Renderer::GetInstance()->Deleter();
	return 0;
}