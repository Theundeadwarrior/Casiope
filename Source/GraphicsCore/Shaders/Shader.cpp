#include "Shader.h"

#include <GL\glew.h>

#include <iostream>
#include <fstream>
#include <assert.h>

#include "ShaderUtilities.h"


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
		// build VertexShader
		std::string shaderCode = args + vertexShaderCode;
		const char* shaderCodeChar = shaderCode.c_str();

		ShaderId vshaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vshaderId, 1, &shaderCodeChar, NULL);
		glCompileShader(vshaderId);

		int compilationStatus = 0;
		glGetShaderiv(vshaderId, GL_COMPILE_STATUS, &compilationStatus);
		assert(compilationStatus, "Shader failed to compiled");

		m_VertexShader = new Shader(ShaderType::e_VertexShader, vshaderId);

		shaderCode = args + fragmentShaderCode;
		shaderCodeChar = shaderCode.c_str();
		ShaderId fshaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fshaderId, 1, &shaderCodeChar, NULL);
		glCompileShader(fshaderId);

		compilationStatus = 0;
		glGetShaderiv(fshaderId, GL_COMPILE_STATUS, &compilationStatus);
		assert(compilationStatus, "Shader failed to compiled");

		m_FragmentShader = new Shader(ShaderType::e_FragmentShader, fshaderId);

		m_ShaderProgramId = CreateShaderProgram(vshaderId, fshaderId);
	}

	ShaderProgram::~ShaderProgram()
	{
		if (m_FragmentShader)
			delete m_FragmentShader;
		if (m_VertexShader)
			delete m_VertexShader;
	}

}

