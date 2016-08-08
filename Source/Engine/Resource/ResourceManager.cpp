#include "Engine/Resource/ResourceManager.h"

#include "Core/File/ImageUtilities.h"


namespace Engine
{
	ResourceManager* ResourceManager::m_Instance = nullptr;

	TextureId TextureManager::InsertTexture(GraphicsCore::Texture* const texture)
	{
		TextureId id = texture->GetID();
		m_TextureBank[id] = texture;
		return id;
	}

	TextureId TextureManager::CreateTextureFromImage(const Core::Image<unsigned char>& image, GraphicsCore::TextureFormat format)
	{
		GraphicsCore::Texture* texture = new GraphicsCore::Texture(image, format);
		return InsertTexture(texture);
	}

	TextureId TextureManager::CreateTextureFromFile(const char * pathToFile, GraphicsCore::TextureFormat format)
	{
		Core::Image<unsigned char> img;
		Core::LoadImageFromFile(img, pathToFile);
		return CreateTextureFromImage(img, format);
	}

	void ResourceManager::CreateInstance()
	{
		assert(m_Instance == nullptr);
		m_Instance = new ResourceManager();
	}
	ResourceManager * ResourceManager::GetInstance()
	{
		return m_Instance;
	}
	void ResourceManager::DestroyInstance()
	{
		assert(m_Instance != nullptr);
		delete m_Instance;
	}
	TextureManager & ResourceManager::GetTextureManager()
	{
		return m_TextureManager;
	}
}
