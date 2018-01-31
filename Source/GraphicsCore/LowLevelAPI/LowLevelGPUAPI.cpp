#include "LowLevelGPUAPI.h"

#include "GraphicsCore/Mesh/Mesh.h"

namespace GraphicsCore
{
	void GPUAPI::UseShader(ShaderProgramId shaderProgram)
	{
		glUseProgram(shaderProgram);
	}

	void GPUAPI::DrawCall(const Mesh* const geometry)
	{
		glBindVertexArray(geometry->m_GPUParams.m_Vbr.VAO);
		glDrawArrays(GL_TRIANGLES, 0, geometry->m_GPUParams.m_VertexCount);
		glBindVertexArray(0);
	}
}
