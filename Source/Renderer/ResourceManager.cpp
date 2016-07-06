#include "ResourceManager.h"

namespace Renderer
{
	TextureId TextureManager::InsertTexture(GraphicsCore::Texture* const texture)
	{
		TextureId id = texture->GetID();
		m_TextureBank[id] = texture;
		return id;
	}

	TextureId TextureManager::AddTextureFromImage(const Core::Image<unsigned char>& image, const GraphicsCore::TextureFormat& format)
	{
		GraphicsCore::Texture* texture = new GraphicsCore::Texture(image, format);
		return InsertTexture(texture);
	}
}
