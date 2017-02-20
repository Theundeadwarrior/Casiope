#pragma once

#include "GraphicsCore/GraphicsType.h"

#include "Core/Math/Vector.h"

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

	// Maybe for this we would have multiple set of vertex and VBO for the different passes we need to make to render everything
	// One pass would be for everything static, another one could be for animated blocks, another one for entities.
	class MinecraftWorldGeometry
	{
	public:
		std::vector<Core::Vector3> m_Vertex;
		std::vector<uint8_t> m_TextureNumber;

	private:
		BufferId m_VertexBO;
		BufferId m_TextureBO;
	};
}
