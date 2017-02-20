#pragma once

#include "GraphicsCore/Geometry/Geometry.h"
#include "GraphicsCore/Shaders/Shader.h"

namespace GraphicsCore
{
	namespace GPUAPI
	{
		void DrawCall(const Geometry* const geometry, const ShaderProgram* const shaderProgram)
		{
			glUseProgram(shaderProgram->GetProgramId());
			glBindVertexArray(geometry->m_GPUParams.m_VAO);

			glDrawArrays(GL_TRIANGLES, 0, 36);

			glBindVertexArray(0);
		}
	}

}
