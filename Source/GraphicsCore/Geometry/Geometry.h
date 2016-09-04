#pragma once

#include "GraphicsCore/GraphicsType.h"

#include <vector>
#include <glm/include/glm/glm.hpp>

namespace GraphicsCore
{
	class Geometry
	{
	public:
		std::vector<float> m_Vertex;
		std::vector<float> m_Normal;
		std::vector<unsigned int> m_Index;
		std::vector<float> m_TextureCoordinates;

	private:
		BufferId m_VAO;
		BufferId m_VBO;
		BufferId m_EBO;
	};
}
