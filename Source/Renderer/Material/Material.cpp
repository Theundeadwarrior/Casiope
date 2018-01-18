#include "Renderer/Material/Material.h"

#include <GL/glew.h>

namespace Renderer
{
	void PhongMaterial::BindShaderParameters()
	{

	}

	void TextureMaterial::BindShaderParameters()
	{
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		PhongMaterial::BindShaderParameters();
	}
}
