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

		void Init(GeometryGPUType type, void* buffer, uint32_t count);
		void Release();

		BufferId VAO;
		BufferId VBO;
		bool m_IsInitialized;
	};

	struct FrameBufferResource
	{
		FrameBufferResource();
		~FrameBufferResource();

		void Init(uint32_t sizeX, uint32_t sizeY);
		void Release();

		TextureId texId;
		BufferId FBO;
		bool m_IsInitialized;
	};

}

