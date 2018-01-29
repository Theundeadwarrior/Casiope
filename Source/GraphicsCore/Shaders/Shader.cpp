#include "Shader.h"

#include "Core/Logging/Logger.h"

#include <iostream>
#include <fstream>
#include <assert.h>

namespace GraphicsCore
{
	Shader::Shader(ShaderType type, const char* shaderCode, const std::string& args)
	{
		ShaderCompiler::CompileShader(m_ShaderId, type, shaderCode, args);
		m_Type = type;
	}

	Shader::~Shader()
	{
		glDeleteShader(m_ShaderId);
	}

	// todo: Move the shadercompile call to the constructor of the shader.
	VertexFragmentShaderProgram::VertexFragmentShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode, const std::string& args)
		: m_VertexShader(ShaderType::e_VertexShader, vertexShaderCode, args)
		, m_FragmentShader(ShaderType::e_FragmentShader, fragmentShaderCode, args)
	{
		ShaderCompiler::LinkShadersIntoProgram(m_ShaderProgramId, std::vector<Shader> { m_VertexShader, m_FragmentShader });
	}

	ComputeShaderProgram::ComputeShaderProgram(const char* computeShaderCode, const std::string& args)
		: m_ComputeShader(ShaderType::e_ComputeShader, computeShaderCode, args)
	{
		ShaderCompiler::LinkShadersIntoProgram(m_ShaderProgramId, std::vector<Shader>{ m_ComputeShader });
	}

}

