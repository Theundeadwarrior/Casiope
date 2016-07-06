#pragma once
#include <string>
#include "Core/File/ImageUtilities.h"

#ifdef _WIN32
#include <gl/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif
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

		unsigned int GetID() { return m_id; }
	private:
		unsigned int m_id;
	};
}
