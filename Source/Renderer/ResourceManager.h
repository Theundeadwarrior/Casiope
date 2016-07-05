#pragma once
#include <map>

#include "Core\File\ImageUtilities.h"

#include "GraphicsCore\GraphicsType.h"
#include "GraphicsCore\Textures\Texture.h"


namespace GraphicsCore { class Texture; }

namespace Renderer
{
	typedef std::map<TextureId, GraphicsCore::Texture*> TextureBank;

	class TextureManager
	{
	public:
		TextureId CreateTexture(const Core::ImageParameters<unsigned char>& imageParameters, const GraphicsCore::TextureFormat& format);

	private:
		TextureId InsertTexture(GraphicsCore::Texture* const texture);
		TextureBank m_TextureBank;

	};
}
