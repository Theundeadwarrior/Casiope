#include "ResourceManager.h"

namespace Renderer
{
	TextureId TextureManager::InsertTexture(GraphicsCore::Texture* const texture)
	{
		TextureId id = texture->GetID();
		m_TextureBank[id] = texture;
		return id;
	}

	TextureId TextureManager::CreateTexture(const Core::ImageParameters<unsigned char>& imageParameters, const GraphicsCore::TextureFormat& format)
	{
		GraphicsCore::Texture* texture = new GraphicsCore::Texture(imageParameters, format);
		return InsertTexture(texture);
	}
}
