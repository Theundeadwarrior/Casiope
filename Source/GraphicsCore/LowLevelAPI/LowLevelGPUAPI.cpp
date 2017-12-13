#include "LowLevelGPUAPI.h"

#include "GraphicsCore/Mesh/Mesh.h"

namespace GraphicsCore
{
	void GPUAPI::DrawCall(const Mesh* const geometry, ShaderProgramId shaderProgramId)
	{
		glUseProgram(shaderProgramId);
		glBindVertexArray(geometry->m_GPUParams.m_Vbr.VAO);

		glDrawArrays(GL_TRIANGLES, 0, geometry->m_GPUParams.m_VertexCount);

		glBindVertexArray(0);
	}
}
