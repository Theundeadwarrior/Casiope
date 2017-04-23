#pragma once

#include "GraphicsCore/GraphicsType.h"
#include "GraphicsCore/LowLevelAPI/LowLevelGPUResource.h"

#include "Core/Math/Vector.h"



#include <vector>

namespace GraphicsCore
{
	struct GeometryGPUParameters
	{
		uint32_t m_VertexCount;
		uint32_t m_TexCoordCount;
		BufferId m_VAO;
		BufferId m_VBO;
		BufferId m_EBO;
	};

	class Geometry
	{
	public:
		GeometryGPUParameters m_GPUParams;
		std::vector<float> m_Vertex;
		std::vector<float> m_TextureCoordinates;
	};

	// Maybe for this we would have multiple set of vertex and VBO for the different passes we need to make to render everything
	// One pass would be for everything static, another one could be for animated blocks, another one for entities.
	class MinecraftChunkGeometry
	{
	public:
		void UpdateGeometry(void* data, uint32_t count)
		{
			m_VAO = GraphicsCore::BuildVertexBufferFromVertexArray(GraphicsCore::GeometryGPUType::V4B, data, count);
		}

	private:
		BufferId m_VAO;
	};
}
