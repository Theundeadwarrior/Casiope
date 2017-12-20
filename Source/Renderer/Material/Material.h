#pragma once

#include <glm/glm.hpp>


namespace Renderer
{
	class IMaterial
	{

	};

	class BaseMaterial : public IMaterial
	{
		glm::vec4 m_AmbientColor;
		glm::vec4 m_DiffuseColor;
		glm::vec4 m_SpecularColor;
	};

	class TextureMaterial : public IMaterial
	{

	};
}



