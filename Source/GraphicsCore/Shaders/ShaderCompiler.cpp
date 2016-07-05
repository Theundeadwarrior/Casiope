#include "Shaders\ShaderCompiler.h"

#include <GL/glew.h>
#include <assert.h>


namespace GraphicsCore
{
	ShaderId ShaderCompiler::CompileShader(ShaderType type, const std::string & code, const std::string & args)
	{
		// build VertexShader
		std::string shaderCode = args + code;
		const char* shaderCodeChar = shaderCode.c_str();

		ShaderId shaderId = glCreateShader((GLenum)type);
		glShaderSource(shaderId, 1, &shaderCodeChar, NULL);
		glCompileShader(shaderId);

		int compilationStatus = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationStatus);
		assert(compilationStatus, "Shader failed to compiled");
		return shaderId;
	}

	ShaderProgramId ShaderCompiler::CreateShaderProgram(ShaderId vertexId, ShaderId fragmentId)
	{
		//Create the shader program and attach the two shaders to it.
		ShaderProgramId programId = glCreateProgram();
		glAttachShader(programId, vertexId);
		glAttachShader(programId, fragmentId);

		// todo lcharbonneau: Reactivate later
		//glBindAttribLocation(programId, 0, "position");
		//glBindAttribLocation(programId, 1, "normal");
		//glBindAttribLocation(programId, 2, "texCoords");

		//Link the shader program
		glLinkProgram(programId);

		int linkStatus = 0;
		glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
		assert(linkStatus, "Shaders couldn't be linked to the program");

		return programId;
	}

	inline std::string ShaderCompiler::ShaderLog(ShaderId shaderId)
	{
		int LogLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &LogLength);

		char *Log = new char[LogLength];

		int ReturnedLength = 0;
		glGetShaderInfoLog(shaderId, LogLength, &ReturnedLength, Log);

		std::string RetStr(Log);
		delete[] Log;

		return RetStr;
	}

}

