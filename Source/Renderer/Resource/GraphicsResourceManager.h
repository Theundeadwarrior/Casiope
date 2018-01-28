#pragma once
#include <map>

#include "Core/Singleton/Singleton.h"
#include "GraphicsCore/GraphicsType.h"
#include "GraphicsCore/Textures/Texture.h"
#include "GraphicsCore/Shaders/Shader.h"
#include "GraphicsCore/Mesh/Mesh.h"

// TODO!!!!!
// Need to figure out how to not have duplicate of textures or shaders loaded in memory!!!!
namespace GraphicsCore { class Texture; }
namespace Core { template<typename T> class Image; }

namespace Renderer
{
	typedef std::map<TextureId, GraphicsCore::Texture*> TextureBank;
	typedef std::map<ShaderProgramId, GraphicsCore::ShaderProgram*> ShaderBank;
	typedef std::map<MeshId, GraphicsCore::Mesh*> MeshBank;

	class MeshManager
	{
	public:
		~MeshManager();
		MeshId AddMesh(GraphicsCore::Mesh* const geometry);
		void RemoveMesh(MeshId geometryId);

		GraphicsCore::Mesh* GetMesh(MeshId geometryId);

	private:
		MeshBank m_MeshBank;
	};

	class TextureManager
	{
	public:
		~TextureManager();
		TextureId CreateTextureFromImage(const Core::Image<unsigned char>& image, GraphicsCore::TextureFormat format);
		TextureId CreateTextureFromFile(const char* pathToFile, GraphicsCore::TextureFormat format);
		void RemoveTexture(TextureId textureID);

	private:
		TextureId InsertTexture(GraphicsCore::Texture* const texture);
		TextureBank m_TextureBank;
	};


	class ShaderManager
	{
	public:
		~ShaderManager();
		ShaderProgramId CreateComputeShaderProgram(const char* csFileName);
		ShaderProgramId CreateVertexFragmentShaderProgram(const char* vsFileName, const char* psFileName); // todo lcharbonneau: add compile flags here std::bitset<MATERIALEFFECT_COUNT> shaderCompileFlags
		void RemoveShader(ShaderProgramId shaderId);
	
	private:
		ShaderBank m_ShaderBank;
	};

	class GraphicsResourceManager : public Core::Singleton<GraphicsResourceManager>
	{
	public: 
		SINGLETON_DECLARATION(GraphicsResourceManager);
	public:
		GraphicsResourceManager() {};
		GraphicsResourceManager(const GraphicsResourceManager& manager) = delete;
		GraphicsResourceManager operator=(const GraphicsResourceManager& manager) = delete;
		inline TextureManager& GetTextureManager() { return m_TextureManager; }
		inline MeshManager& GetGeometryManager() { return m_GeometryManager; }
		inline ShaderManager& GetShaderManager() { return m_ShaderManager; }

	private:
		TextureManager m_TextureManager;
		ShaderManager m_ShaderManager;
		MeshManager m_GeometryManager;
	};
}
