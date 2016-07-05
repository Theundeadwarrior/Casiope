#include "Shader.h"

#include <iostream>
#include <fstream>
#include <assert.h>

namespace GraphicsCore
{
	Shader::Shader(ShaderType type, ShaderId shaderId)
	{
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
		ShaderId vShaderId = ShaderCompiler::CompileShader(ShaderType::e_VertexShader, vertexShaderCode, args);
		m_VertexShader = new Shader(ShaderType::e_VertexShader, vShaderId);

		ShaderId fShaderId = ShaderCompiler::CompileShader(ShaderType::e_FragmentShader, fragmentShaderCode, args);
		m_FragmentShader = new Shader(ShaderType::e_FragmentShader, fShaderId);

		m_ShaderProgramId = ShaderCompiler::CreateShaderProgram(vShaderId, fShaderId);
	}

	ShaderProgram::~ShaderProgram()
	{
		if (m_FragmentShader)
			delete m_FragmentShader;
		if (m_VertexShader)
			delete m_VertexShader;
	}

}

