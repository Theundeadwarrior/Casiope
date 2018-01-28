#include "GraphicsCore/Shaders/ShaderCompiler.h"

#include <GL/glew.h>
#include <assert.h>

#include "Core/Core.h"
#include "Core/Logging/Logger.h"
#include "GraphicsCore/Shaders/Shader.h"

#include <iostream>

namespace GraphicsCore
{
	void CheckShaderCompilationStatus(ShaderId shaderId)
	{

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
			std::cout << ShaderLog(shaderIdOut) << std::endl;
			return false;
		}

		return true;
	}

	ShaderProgramId ShaderCompiler::LinkShadersIntoProgram(const std::vector<Shader>& shaders)
	{
		ShaderProgramId programId = glCreateProgram();
		for (auto& shader : shaders)
		{
			glAttachShader(programId, shader.GetId());
		}

		glLinkProgram(programId);

		int linkStatus = 0;
		glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
		assert(linkStatus, "Shaders couldn't be linked to the program");

		return programId;
	}

	inline std::string ShaderCompiler::ShaderLog(ShaderId shaderId)
	{
		int logLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

		char *log = new char[logLength];

		int returnedLength = 0;
		glGetShaderInfoLog(shaderId, logLength, &returnedLength, log);

		std::string RetStr(log);
		delete[] log;

		return RetStr;
	}

}

