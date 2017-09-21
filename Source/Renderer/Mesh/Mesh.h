#pragma once

#include "Renderer/Geometry/GeometryInstance.h"
#include "Renderer/Material/Material.h"

#include <glm/glm.hpp>

namespace Renderer
{
	class Mesh
	{
	public:
		Mesh();
		~Mesh();

	public: // todo lcharbonneau: move that back to protected
		GeometryId m_GeometryId;
		IMaterial* m_Material; 
	};
}



