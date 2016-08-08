#include <assert.h>

#include "Core/File/ImageUtilities.h"
#include "GraphicsCore/Textures/Texture.h"

#include <Core/Core.h>

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
	TextureId Texture::GenerateSkyBoxTexture(unsigned int& textureId, const Core::Image<unsigned char> imageParameters[6], const TextureFormat& format)
	{
		int targets[6];
		targets[0] = (GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB);
		targets[1] = (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB);
		targets[2] = (GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB);
		targets[3] = (GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB);
		targets[4] = (GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB);
		targets[5] = (GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, textureId);

		for (unsigned int cubeSide = 0; cubeSide < 6; ++cubeSide)
		{
			assert(!imageParameters[cubeSide].imageData.empty(), "Texture data must not be null");

			glTexImage2D(targets[cubeSide], 0, format, imageParameters[cubeSide].width, imageParameters[cubeSide].height, 0, format, GL_UNSIGNED_BYTE, &imageParameters[cubeSide].imageData[0]);
			assert(!glGetError(), "Failed to load texture");
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);
		return textureId;

	}

}
