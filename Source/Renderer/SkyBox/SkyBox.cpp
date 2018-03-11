#include "Renderer/SkyBox/SkyBox.h"


#include "Renderer/Model/Model.h"
#include "Renderer/Material/Material.h"
#include "GraphicsCore/Mesh/Mesh.h"
#include "Renderer/Resource/GraphicsResourceManager.h"

namespace Renderer
{
	struct Float5Data
	{
		Float5Data() {};
		Float5Data(float x1, float x2, float x3, float x4, float x5)
			: m_x1(x1)
			, m_x2(x2)
			, m_x3(x3)
			, m_x4(x4)
			, m_x5(x5)
		{}

		float m_x1, m_x2, m_x3, m_x4, m_x5;
	};

	SkyBox::SkyBox()
		: m_IsInitialized(false)
	{
	}


	SkyBox::SkyBox(const std::string& textureFileName)
		: m_IsInitialized(false)
	{
		Init(textureFileName);
	}

	SkyBox::~SkyBox()
	{
	}

	void SkyBox::Init(const std::string& textureFileName)
	{
		if (m_IsInitialized)
		{
			delete m_Material;
			delete m_Mesh;
		}
		
		auto* material = new TextureMaterial();
		material->m_Texture = Renderer::GraphicsResourceManager::GetInstance()->GetTextureManager().CreateTextureFromFile(textureFileName.c_str(), GraphicsCore::e_TexFormatRGBA);
		material->m_ShaderProgram = Renderer::GraphicsResourceManager::GetInstance()->GetShaderManager().CreateVertexFragmentShaderProgram("shaders/skybox.vert.glsl", "shaders/skybox.frag.glsl");

		m_Material = material;


		// Left
		Float5Data vertices[36];
		uint32_t currentVertex = 0;

		// East Side
		vertices[currentVertex++] = Float5Data(-1, -1, -1, 3, 0);
		vertices[currentVertex++] = Float5Data(1, 1, -1, 2, 1);
		vertices[currentVertex++] = Float5Data(1, -1, -1, 2, 0);
		vertices[currentVertex++] = Float5Data(-1, 1, -1, 3, 1);
		vertices[currentVertex++] = Float5Data(1, 1, -1, 2, 1);
		vertices[currentVertex++] = Float5Data(-1, -1, -1, 3, 0);
		//// West Side				
		vertices[currentVertex++] = Float5Data(-1, -1, 1, 0, 0);
		vertices[currentVertex++] = Float5Data(1, -1, 1, 1, 0);
		vertices[currentVertex++] = Float5Data(1, 1, 1, 1, 1);
		vertices[currentVertex++] = Float5Data(-1, -1, 1, 0, 0);
		vertices[currentVertex++] = Float5Data(1, 1, 1, 1, 1);
		vertices[currentVertex++] = Float5Data(-1, 1, 1, 0, 1);
		//// North Side				
		vertices[currentVertex++] = Float5Data(-1, 1, 1, 4, 1);
		vertices[currentVertex++] = Float5Data(-1, 1, -1, 3, 1);
		vertices[currentVertex++] = Float5Data(-1, -1, -1, 3, 0);
		vertices[currentVertex++] = Float5Data(-1, 1, 1, 4, 1);
		vertices[currentVertex++] = Float5Data(-1, -1, -1, 3, 0);
		vertices[currentVertex++] = Float5Data(-1, -1, 1, 4, 0);
		//// South Side
		vertices[currentVertex++] = Float5Data(1, 1, 1, 1, 1);
		vertices[currentVertex++] = Float5Data(1, -1, -1, 2, 0);
		vertices[currentVertex++] = Float5Data(1, 1, -1, 2, 1);
		vertices[currentVertex++] = Float5Data(1, -1, 1, 1, 0);
		vertices[currentVertex++] = Float5Data(1, -1, -1, 2, 0);
		vertices[currentVertex++] = Float5Data(1, 1, 1, 1, 1);
		//// Bottom
		vertices[currentVertex++] = Float5Data(-1, -1, -1, 5, 0);
		vertices[currentVertex++] = Float5Data(1, -1, -1, 6, 0);
		vertices[currentVertex++] = Float5Data(1, -1, 1, 6, 1);
		vertices[currentVertex++] = Float5Data(-1, -1, -1, 5, 0);
		vertices[currentVertex++] = Float5Data(1, -1, 1, 6, 1);
		vertices[currentVertex++] = Float5Data(-1, -1, 1, 5, 1);
		//// Bottom					
		vertices[currentVertex++] = Float5Data(-1, 1, -1, 4, 1);
		vertices[currentVertex++] = Float5Data(1, 1, 1, 5, 0);
		vertices[currentVertex++] = Float5Data(1, 1, -1, 5, 1);
		vertices[currentVertex++] = Float5Data(-1, 1, 1, 4, 0);
		vertices[currentVertex++] = Float5Data(1, 1, 1, 5, 0);
		vertices[currentVertex++] = Float5Data(-1, 1, -1, 4, 1);

		m_Mesh = new GraphicsCore::Mesh();
		m_Mesh->UpdateGeometry(vertices, currentVertex * 5 * sizeof(float), GraphicsCore::VertexBufferType::V3FT2F);

		m_IsInitialized = true;
	}

}
