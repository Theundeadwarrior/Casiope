#pragma once

#include "GraphicsCore/Geometry/Geometry.h"
#include "GraphicsCore/Shaders/Shader.h"

namespace GraphicsCore
{
	namespace GPUAPI
	{
		// todo P0: PASS IN A MESH INSTEAD OF A GEOM AND SHADERPROGRAM!!!
		void DrawCall(const Geometry* const geometry, ShaderProgramId shaderProgram);
	}

}
