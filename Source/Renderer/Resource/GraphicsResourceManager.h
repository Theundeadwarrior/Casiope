#pragma once
#include <map>

#include "Core/Singleton/Singleton.h"
#include "GraphicsCore/GraphicsType.h"
#include "GraphicsCore/Textures/Texture.h"
#include "GraphicsCore/Shaders/Shader.h"

// TODO!!!!!
// Need to figure out how to not have duplicate of textures or shaders loaded in memory!!!!
namespace GraphicsCore { class Texture; }
namespace Core { template<typename T> class Image; }

namespace Renderer
{
	typedef std::map<TextureId, GraphicsCore::Texture*> TextureBank;

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

	typedef std::map<ShaderProgramId, GraphicsCore::ShaderProgram*> ShaderBank;

	class ShaderManager
	{
	public:
		~ShaderManager();
		ShaderProgramId CreateShaderProgram(const char* vsFileName, const char* psFileName); // todo lcharbonneau: add compile flags here std::bitset<MATERIALEFFECT_COUNT> shaderCompileFlags
	
	private:
		ShaderBank m_ShaderBank;
	};

	class GraphicsResourceManager
	{
	public:
		GraphicsResourceManager() {};
		GraphicsResourceManager(const GraphicsResourceManager& manager) = delete;
		GraphicsResourceManager operator=(const GraphicsResourceManager& manager) = delete;
		inline TextureManager& GetTextureManager() { return m_TextureManager; }

	private:
		TextureManager m_TextureManager;
		ShaderManager m_ShaderManager;
	};
}
