#pragma once

#include <glm/glm.hpp>
#include <bitset>

#include "GraphicsCore/GraphicsType.h"

namespace Renderer
{
	enum MaterialType
	{
	};

	class IMaterial
	{
	public:
		virtual void BindShaderParameters() = 0;
		ShaderProgramId m_ShaderProgram;
	};

	class PhongMaterial : public IMaterial
	{
	public:
		void BindShaderParameters() override;
		glm::vec4 m_AmbientColor;
		glm::vec4 m_DiffuseColor;
		glm::vec4 m_SpecularColor;
		float m_Shininess;
	};

	class TextureMaterial : public PhongMaterial
	{
	public:
		void BindShaderParameters() override;
		TextureId m_Texture;
	};
}



