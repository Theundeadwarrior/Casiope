#pragma once
#include <map>
#include <assert.h>


#include "GraphicsCore\GraphicsType.h"
#include "GraphicsCore\Textures\Texture.h"

// TODO!!!!!
// Need to figure out how to not have duplicate of textures or shaders loaded in memory!!!!
namespace GraphicsCore { class Texture; }
namespace Core { template<typename T> class Image; }

namespace Engine
{

	typedef std::map<TextureId, GraphicsCore::Texture*> TextureBank;

	class TextureManager
	{
	public:
		TextureId AddTextureFromImage(const Core::Image<unsigned char>& image, const GraphicsCore::TextureFormat& format);

	private:
		TextureId InsertTexture(GraphicsCore::Texture* const texture);
		TextureBank m_TextureBank;

	};

	class ResourceManager
	{
	public:
		static void CreateInstance();
		static ResourceManager* GetInstance();
		static void DestroyInstance();

	public:
		TextureManager& GetTextureManager();

	private:
		ResourceManager() {};
		ResourceManager(const ResourceManager& manager) = delete;
		ResourceManager operator=(const ResourceManager& manager) = delete;

	private:
		static ResourceManager* m_Instance;

		TextureManager m_TextureManager;
	};
}
