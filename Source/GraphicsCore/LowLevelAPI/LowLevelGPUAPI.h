#pragma once

#include "GraphicsCore/Geometry/Geometry.h"
#include "GraphicsCore/Shaders/Shader.h"

namespace GraphicsCore
{
	namespace GPUAPI
	{
		void DrawCall(const Geometry* const geometry, const ShaderProgram* const shaderProgram);
	}

}
