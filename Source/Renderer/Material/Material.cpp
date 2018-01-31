#include "Renderer/Material/Material.h"

#include <GL/glew.h>

namespace Renderer
{
	void PhongMaterial::BindShaderParameters()
	{

	}

	void PhongMaterial::UnBindShaderParameters()
	{
	}

	void TextureMaterial::BindShaderParameters()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		PhongMaterial::BindShaderParameters();
	}
	void TextureMaterial::UnBindShaderParameters()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
