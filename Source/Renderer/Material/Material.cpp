#include "Renderer/Material/Material.h"

namespace Renderer
{
	void PhongMaterial::BindShaderParameters()
	{

	}

	void TextureMaterial::BindShaderParameters()
	{
		PhongMaterial::BindShaderParameters();

	}
}
