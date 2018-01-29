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

	class StaticMesh
	{
	public:
		GeometryGPUParameters m_GPUParams;
	};

	class Mesh : public StaticMesh
	{
	public:
		virtual ~Mesh() {};
		void UpdateGeometry(void* data, uint32_t count, VertexBufferType type)
		{
			m_GPUParams.m_Vbr.Init(type, data, count);
			m_GPUParams.m_VertexCount = count;
		}
	};
}
