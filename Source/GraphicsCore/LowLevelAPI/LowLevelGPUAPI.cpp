#include "LowLevelGPUAPI.h"

#include "GraphicsCore/Mesh/Mesh.h"

namespace GraphicsCore
{
	void GPUAPI::UseShader(ShaderProgramId shaderProgram)
	{
		glUseProgram(shaderProgram);
	}

	void GPUAPI::DrawCall(const Mesh* mesh)
	{
		glBindVertexArray(mesh->m_GPUParams.m_Vbr.VAO);
		if (mesh->m_GPUParams.m_Vbr.IsUsingEBO())
		{
			glDrawElements(GL_TRIANGLES, mesh->m_GPUParams.m_IndexCount, GL_UNSIGNED_INT, nullptr);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, mesh->m_GPUParams.m_VertexCount);
		}
		glBindVertexArray(0);
	}
}
