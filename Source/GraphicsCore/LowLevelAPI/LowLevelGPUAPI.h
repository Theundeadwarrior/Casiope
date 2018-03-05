#pragma once

#include "GraphicsCore/Shaders/Shader.h"

namespace GraphicsCore
{
	class Mesh;
}

namespace GraphicsCore
{
	namespace GPUAPI
	{
		void UseShader(ShaderProgramId shaderProgram);
		void DrawCall(const Mesh* mesh);
	}

}
