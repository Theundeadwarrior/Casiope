#include "Textures\Texture.h"

namespace GraphicsCore
{
	Texture::Texture(const Core::Image<unsigned char>& imageParameters, TextureFormat format)
	{
		//LowLevelAPI::GenerateTexture(m_id, imageParameters, format);
		//m_path = imageParameters.path;
	}

	Texture::~Texture()
	{
		//LowLevelAPI::DeleteTexture(m_id);
	}
}
