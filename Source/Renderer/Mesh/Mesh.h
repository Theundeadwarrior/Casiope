#pragma once

#include "Renderer/Geometry/GeometryInstance.h"
#include "Renderer/Material/Material.h"

#include <glm/glm.hpp>

namespace Renderer
{
	class Mesh
	{
	public:
		Mesh() {};
		~Mesh() {};

	private:
		GeometryInstance m_GeometryInstance;
		IMaterial* m_Material; 
	};
}



