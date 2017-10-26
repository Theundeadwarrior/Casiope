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
		// todo P0: PASS IN A MESH INSTEAD OF A GEOM AND SHADERPROGRAM!!!
		void DrawCall(const Mesh* const geometry, ShaderProgramId shaderProgram);
	}

}
