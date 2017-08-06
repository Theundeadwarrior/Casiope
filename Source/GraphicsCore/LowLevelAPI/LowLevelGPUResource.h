#pragma once

#include "GraphicsCore/GraphicsType.h"
#include <GL/glew.h>
#include <glm/include/glm/glm.hpp>

namespace GraphicsCore
{
	enum class GeometryGPUType : uint8_t
	{
		V4B,
		V3FT2F // V1, V2, V3, UV1, UV2
	};

	BufferId BuildVertexBufferFromVertexArray(GeometryGPUType type, void * buffer, uint32_t count);
}

