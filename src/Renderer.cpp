#include "Renderer.hpp"

//别忘了单例实例的类外定义
Renderer* Renderer::instance = nullptr;

//光栅化：图元装配，深度测试，片元着色器
void Renderer::Rasterization(GameObject& gameObject, int ind)
{
	//std::cout << "进入光栅化" << __FILE__ << " : " << __LINE__<< std::endl;
	//图元装配
	//获取三角形顶点
	std::vector<int> posInds = gameObject.mesh.at(0).GetVInds(ind);
	std::vector<int> texInds = gameObject.mesh.at(0).GetTInds(ind);
	std::vector<int> normInds = gameObject.mesh.at(0).GetNInds(ind);
	Vec4f triangle[3];
	for (int i = 0;i < 3;i++)
		triangle[i] = gameObject.mesh.at(0).GetVerts(posInds.at(i));

	//生成包围盒
	float x_min = std::min(triangle[0][0], std::min(triangle[1][0], triangle[2][0]));
	float y_min = std::min(triangle[0][1], std::min(triangle[1][1], triangle[2][1]));
	float x_max = std::max(triangle[0][0], std::max(triangle[1][0], triangle[2][0]));
	float y_max = std::max(triangle[0][1], std::max(triangle[1][1], triangle[2][1]));
	for (int x = x_min;x < x_max + .5f; x++)
	{
		for (int y = y_min; y < y_max + .5f; y++)
		{
			//std::cout << "x为 " << x << "y为 " << y <<__FILE__<<": "<<__LINE__ << std::endl;
			Vec2i screenCoord(x, y);
			Vec3f barycentricCoord = Barycentric(triangle,screenCoord);
			if (barycentricCoord.x < 0 || barycentricCoord.y < 0 || barycentricCoord.z < 0)	continue;
			
			//透视矫正插值：根据屏幕空间的重心坐标和三维坐标的z值获得。注意此处的z值不会趋于零
			float alpha = barycentricCoord[0] / triangle[0].z;
			float beta = barycentricCoord[1] / triangle[1].z;
			float gamma = barycentricCoord[2] / triangle[2].z;
			Vec3f bcChanged(alpha, beta, gamma);

			//根据获得v2f，重心坐标计算z和uv和法线插值
			v2f transfer;
			transfer.cameraDir = scenes[0].GetMainCamera().dir;
			transfer.tex = &gameObject.material.textures;
			for (int i = 0;i < 3;i++)
			{
				transfer.z += bcChanged[i] * triangle[i].z;
				Vec2f texcoords = gameObject.mesh.at(0).GetTexcoords(texInds[i]);
				transfer.uv += texcoords * bcChanged[i];
				Vec4f normals = gameObject.mesh.at(0).GetNorms(normInds[i]);
				transfer.normal +=  normals * bcChanged[i];
			}
			transfer.z = transfer.z * (1.f/(alpha + beta + gamma));
			transfer.uv = transfer.uv * (1.f/(alpha + beta + gamma));
			transfer.normal = transfer.normal * (1.f/(alpha + beta + gamma));

			//深度测试
			if (transfer.z > (*zbuf)[x][y])
			{
				//std::cout << "transfer.z："<<transfer.z << std::endl;
				//std::cout << "zbuffer："<<(*zbuf)[x][y] << std::endl;
				//std::cout << "通过深度测试" << __FILE__ << " : " << __LINE__ << std::endl;
				(*zbuf)[x][y] = transfer.z;
				//片元着色器
				(*dbuf)[x][y] = gameObject.material.shader.FragmentShader(PhongShader(),transfer);
			}
		}
	}
	

}

void Renderer::RenderScene()
{
	bool target = true;
	while (target)
	{
		dbuf->ClearBack();
		for (auto& presentScene : scenes)
		{
			std::cout << "进入场景。" << __FILE__ << " : " << __LINE__ << std::endl;
			for (auto& gameObject : presentScene.GetGO())
			{
				std::cout << "进入GO。" << __FILE__ << " : " << __LINE__ << std::endl;
				//逐顶点操作
				for (int i = 0; i < gameObject.mesh.at(0).VertexNum();i++)
				{
					Vec4f& vertPos  = gameObject.mesh.at(0).GetVerts(i);

					//顶点着色器：变换到裁剪空间
					gameObject.material.shader.VertexShader(PhongShader(),vertPos, gameObject.transform,presentScene.GetMainCamera());

					//裁剪：裁剪+剔除
					gameObject.material.shader.CVVCulling();

					//屏幕映射：齐次除法 + 视口变换
					gameObject.material.shader.ScreenMapping(vertPos);
				}
				std::cout << "逐顶点操作结束。" << __FILE__ << " : " << __LINE__ << std::endl;

				//生成片元并逐片元操作
				for (int i = 0; i < gameObject.mesh.at(0).IndiceNum();i++)
				{
//#ifdef BACKFACE_CULLING	//背面剔除：需要顶点坐标
//					if (BackfaceCulling(gameObject.mesh.at(0), presentScene.GetMainCamera(), i)) continue;
//#endif
					//光栅化：生成包围盒，图元装配，深度测试，片元着色器
					Rasterization(gameObject, i);
				}
				std::cout << "逐片元操作结束。" << __FILE__ << " : " << __LINE__ << std::endl;
#ifdef POST_PROCESSING
				PostProecssing();
#endif
				//交换缓冲并绘制
				dbuf->Swap();
				dbuf->Draw(image);
				
			}
		}
		target = false;
	}
}

bool Renderer::BackfaceCulling(Mesh& mesh, const Camera& camera, int i)  const
{
	//std::cout << "进入背面剔除 "<<__FILE__<<" : "<<__LINE__ << std::endl;
	std::vector<int> posInds = mesh.GetVInds(i);
	Vec4f pos[3];
	for (int iter = 0;iter < 3;iter++)
		pos[iter] = mesh.GetVerts(posInds[iter]);
	Vec4f normal = (pos[0] - pos[1]) ^ (pos[2] - pos[1]);
	Vec3f n{ normal[0],normal[1],normal[2] };
	n.normalize();
	//std::cout << "结束背面剔除" << __FILE__ << " : " << __LINE__<< std::endl;
	if (n * camera.dir.normalize_result() < 0) return true;
	return false;
}

void Renderer::PostProecssing()
{
}

GameObject Renderer::LoadGO(const std::vector<std::string>& meshSrc, const std::vector<std::string>& textureSrc)
{
	Material gouraudMaterial;
	for (auto& tex : textureSrc)
	{
		gouraudMaterial.textures.push_back(Texture(tex));
	}
	std::vector<Mesh> meshes;
	for (auto& mesh : meshSrc)
	{
		meshes.push_back(Mesh(mesh));
	}
	return GameObject(gouraudMaterial, meshes);
}


void Renderer::InitializeScene(const std::string& description)
{
	if (description == "default")
	{
		Scene s{ Camera(Point(0,0,3)) };
		std::vector<std::string> meshSrc(1, "models/african_head.obj");
		std::vector<std::string> textureSrc(1, "models/african_head_diffuse.tga");
		s.PushGO(LoadGO(meshSrc,textureSrc));
		s.PushLight({ {0.f,0.f,-1.f} });
		scenes.push_back(s);
		std::cout << "默认初始化场景。" << __FILE__ << " line: " << __LINE__ << std::endl; 
	}
	else
	{
		__debugbreak();
	}
}


void Renderer::InitializeBuffer()
{
	instance->dbuf = new DoubleBuffer();
	instance->zbuf = new ZBuffer();
}


Renderer::~Renderer()
{
	delete zbuf;
	delete dbuf;
}

void Renderer::Deleter()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}