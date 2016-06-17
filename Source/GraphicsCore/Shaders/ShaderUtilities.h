#pragma once

#include <GL\glew.h>

#include <vector>
#include <string>
#include "Shader.h"

namespace GraphicsCore
{
	ShaderProgramId CreateShaderProgram(ShaderId vertexId, ShaderId fragmentId);

	//-----------------------------------------------------------------------------
	std::string ShaderLog(ShaderId shaderId);

}

