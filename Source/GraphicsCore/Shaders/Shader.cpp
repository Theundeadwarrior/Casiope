#include "Shader.h"

#include <iostream>
#include <fstream>
#include <assert.h>

namespace GraphicsCore
{
	Shader::Shader(ShaderType type, const char* shaderCode, const std::string& args)
	{
		m_ShaderId = ShaderCompiler::CompileShader(type, shaderCode, args);
		m_Type = type;
	}

	Shader::~Shader()
	{
		glDeleteShader(m_ShaderId);
	}

	ShaderResource::ShaderResource()
	{
	}

	ShaderResource::~ShaderResource()
	{
	}

	// todo: Move the shadercompile call to the constructor of the shader.
	ShaderProgram::ShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode, const std::string& args)
		: m_VertexShader(nullptr)
		, m_FragmentShader(nullptr)
	{
		m_VertexShader = new Shader(ShaderType::e_VertexShader, vertexShaderCode, args);
		m_FragmentShader = new Shader(ShaderType::e_FragmentShader, fragmentShaderCode, args);

		m_ShaderProgramId = ShaderCompiler::CreateShaderProgram(*m_VertexShader, *m_FragmentShader);
	}

	ShaderProgram::~ShaderProgram()
	{
		if (m_FragmentShader)
			delete m_FragmentShader;
		if (m_VertexShader)
			delete m_VertexShader;
	}

}

