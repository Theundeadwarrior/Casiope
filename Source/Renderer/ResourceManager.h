#pragma once
#include <map>

#include "Core\File\ImageUtilities.h"

#include "GraphicsCore\GraphicsType.h"
#include "GraphicsCore\Textures\Texture.h"

// TODO!!!!!
// Need to figure out how to not have duplicate of textures or shaders loaded in memory!!!!
namespace GraphicsCore { class Texture; }

namespace Renderer
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
}
