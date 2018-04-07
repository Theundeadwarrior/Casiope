#include <assert.h>

#include "Core/File/ImageUtilities.h"
#include "GraphicsCore/Textures/Texture.h"

#include <Core/Core.h>

namespace GraphicsCore
{
	Texture::Texture(const Core::Image<unsigned char>& imageParameters, TextureFormat format)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, imageParameters.m_Width, imageParameters.m_Height, 0, format, GL_UNSIGNED_BYTE, imageParameters.m_ImageData.data());
		glGenerateTextureMipmap(m_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//LowLevelAPI::GenerateTexture(m_id, imageParameters, format);
		//m_path = imageParameters.path;
		glBindTexture(GL_TEXTURE_2D, 0);
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
			assert(!imageParameters[cubeSide].m_ImageData.empty(), "Texture data must not be null");

			glTexImage2D(targets[cubeSide], 0, format, imageParameters[cubeSide].m_Width, imageParameters[cubeSide].m_Height, 0, format, GL_UNSIGNED_BYTE, &imageParameters[cubeSide].m_ImageData[0]);
			assert(!glGetError(), "Failed to load texture");
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, 0);
		return textureId;

	}

}
