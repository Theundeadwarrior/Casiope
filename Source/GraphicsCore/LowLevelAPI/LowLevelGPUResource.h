#pragma once

#include "GraphicsCore/GraphicsType.h"
#include <GL/glew.h>
#include <glm/include/glm/glm.hpp>

namespace GraphicsCore
{
	enum class GeometryGPUType : uint8_t
	{
		V4B,
		V3BT2B,
		V3FT2F // V1, V2, V3, UV1, UV2
	};

	struct VertexBufferResource
	{
		VertexBufferResource();
		~VertexBufferResource();


		void InitBuffer(GeometryGPUType type, void* buffer, uint32_t count);
		void ReleaseBuffer();
		BufferId VAO;
		BufferId VBO;
		bool m_IsInitialized;
	};
}

