#pragma once
#include <string>

#include <GL/glew.h>

#include "GraphicsCore/GraphicsType.h"

namespace Core { template<typename T> class Image; }

namespace GraphicsCore
{
	enum TextureFormat
	{
		e_TexFormatLuminance = GL_LUMINANCE,
		e_TexFormatRGB = GL_RGB,
		e_TexFormatRGBA = GL_RGBA
	};


	class Texture
	{
	public:
		Texture(const Core::Image<unsigned char>& imageParameters, TextureFormat format);
		~Texture();

		static TextureId GenerateSkyBoxTexture(unsigned int& textureId, const Core::Image<unsigned char> imageParameters[6], const TextureFormat& format);
		unsigned int GetID() { return m_id; }
	private:
		unsigned int m_id;
	};
}
