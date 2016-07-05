#pragma once

#include "GraphicsCore\GraphicsType.h"

#include <string>
#include <GL\glew.h>


namespace GraphicsCore
{
	enum class ShaderType
	{
		e_VertexShader = GL_VERTEX_SHADER,
		e_FragmentShader = GL_FRAGMENT_SHADER,
	};

	class ShaderCompiler
	{
	public:
		static ShaderId CompileShader(ShaderType type, const std::string& code, const std::string& args);
		static ShaderProgramId CreateShaderProgram(ShaderId vertexId, ShaderId fragmentId);
		std::string ShaderLog(ShaderId shaderId);

	};
}

