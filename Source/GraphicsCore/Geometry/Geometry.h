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
		VertexBufferResource m_Vbr;
	};

	class StaticGeometry
	{
	public:
		GeometryGPUParameters m_GPUParams;
	};

	class Geometry : public StaticGeometry
	{
	public:
		void UpdateGeometry(void* data, uint32_t count, GeometryGPUType type)
		{
			m_GPUParams.m_Vbr.InitBuffer(type, data, count);
			m_GPUParams.m_VertexCount = count;
		}
	};
}
