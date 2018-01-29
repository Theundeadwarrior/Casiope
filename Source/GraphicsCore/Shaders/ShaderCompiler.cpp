#include "GraphicsCore/Shaders/ShaderCompiler.h"

#include <GL/glew.h>
#include <assert.h>

#include "Core/Core.h"
#include "Core/Logging/Logger.h"
#include "GraphicsCore/Shaders/Shader.h"

#include <iostream>

namespace GraphicsCore
{
	std::string ShaderLog(ShaderId shaderId)
	{
		char log[1024];

		glGetShaderInfoLog(shaderId, sizeof(log), NULL, log);

		std::string RetStr(log);

		return RetStr;
	}

	std::string ProgramLog(ShaderProgramId programId)
	{
		char log[1024];

		glGetProgramInfoLog(programId, sizeof(log), NULL, log);

		std::string RetStr(log);

		return RetStr;
	}

	bool ShaderCompiler::CompileShader(ShaderId& shaderIdOut, ShaderType type, const std::string & code, const std::string & args)
	{
		// build VertexShader
		std::string shaderCode = args + code;
		const char* shaderCodeChar = shaderCode.c_str();

		shaderIdOut = glCreateShader((GLenum)type);
		glShaderSource(shaderIdOut, 1, &shaderCodeChar, NULL);
		glCompileShader(shaderIdOut);

		int compilationStatus = 0;
		glGetShaderiv(shaderIdOut, GL_COMPILE_STATUS, &compilationStatus);

		// todo: have better logging when shader compilation fails.
		if (compilationStatus != GL_TRUE)
		{
			std::cout << "Shader compilation failed: " << ShaderLog(shaderIdOut) << std::endl;
			return false;
		}

		return true;
	}

	bool ShaderCompiler::LinkShadersIntoProgram(ShaderProgramId& shaderProgramIdOut, const std::vector<Shader>& shaders)
	{
		shaderProgramIdOut = glCreateProgram();
		for (auto& shader : shaders)
		{
			glAttachShader(shaderProgramIdOut, shader.GetId());
		}

		glLinkProgram(shaderProgramIdOut);

		int linkStatus = 0;
		glGetProgramiv(shaderProgramIdOut, GL_LINK_STATUS, &linkStatus);

		if (linkStatus != GL_TRUE)
		{
			std::cout << "Shader program linking failed: " << ProgramLog(shaderProgramIdOut) << std::endl;
			return false;
		}

		return true;
	}
}

