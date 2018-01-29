#pragma once

#include "GraphicsCore/GraphicsType.h"

#include <string>
#include <vector>
#include <GL/glew.h>



namespace GraphicsCore
{
	class Shader;

	enum class ShaderType
	{
		e_VertexShader = GL_VERTEX_SHADER,
		e_FragmentShader = GL_FRAGMENT_SHADER,
		e_ComputeShader = GL_COMPUTE_SHADER,
	};

	class ShaderCompiler
	{
	public:
		static bool CompileShader(ShaderId& shaderIdOut, ShaderType type, const std::string& code, const std::string& args);
		static bool ShaderCompiler::LinkShadersIntoProgram(ShaderProgramId& shaderProgramIdOut, const std::vector<Shader>& shaders);
	};
}

