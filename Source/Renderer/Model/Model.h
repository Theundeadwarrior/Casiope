#pragma once

#include "Renderer/Material/Material.h"
#include "GraphicsCore/GraphicsType.h"

namespace Renderer
{
	class Model
	{
	public:
		Model();
		~Model();

	public: // todo lcharbonneau: move that back to protected
		IMaterial* m_Material;
		MeshId m_GeometryId;
	};
}



