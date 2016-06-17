#pragma once

#include <vector>

namespace GraphicsCore
{
	typedef int ShaderParameterId;
	typedef unsigned int ShaderId;
	typedef unsigned int ShaderProgramId;

	enum class ShaderType
	{
		e_VertexShader,
		e_FragmentShader,
	};

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

