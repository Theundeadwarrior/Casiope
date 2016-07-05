#pragma once

#include <vector>

#include "GraphicsCore\GraphicsType.h"
#include "GraphicsCore\Shaders\ShaderCompiler.h"

namespace GraphicsCore
{


	class Shader
	{
	public:
		Shader(ShaderType type, ShaderId shaderId);
		~Shader();

	private:
		ShaderType m_Type;
		ShaderId m_ShaderId;
	};

	class ShaderProgram
	{
	public:
		ShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode, const std::string& args);
		~ShaderProgram();

		ShaderProgramId GetProgramId() const { return m_ShaderProgramId; }

	private:
		std::vector<ShaderParameterId> m_ShaderParameterIds;
		Shader* m_VertexShader;
		Shader* m_FragmentShader;
		ShaderProgramId m_ShaderProgramId;
	};

	class ShaderResource
	{
	public:
		ShaderResource();
		~ShaderResource();
	};
}

