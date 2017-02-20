#pragma once

#include "GraphicsCore/GraphicsType.h"

#include "Core/Math/Vector.h"

#include <iostream>

#include <vector>
#include <GL/glew.h>
#include <glm/include/glm/glm.hpp>


namespace GraphicsCore
{
	struct GeometryGPUParameters
	{
		uint32_t m_VertexCount;
		uint32_t m_TexCoordCount;
		BufferId m_VAO;
		BufferId m_VBO;
		BufferId m_EBO;
	};

	class Geometry
	{
	public:
		GeometryGPUParameters m_GPUParams;
		std::vector<float> m_Vertex;
		std::vector<float> m_TextureCoordinates;
	};

	enum class GeometryGPUType : uint8_t
	{
		V3T2 // V1, V2, V3, UV1, UV2
	};

	class GeometryBuilder
	{
	public:
		GeometryBuilder(Geometry& geometry, GeometryGPUType type, GLfloat* buffer, uint32_t count)
		{
			auto& params = geometry.m_GPUParams;

			if (type == GeometryGPUType::V3T2)
			{
				GLuint VBO;
				glGenVertexArrays(1, &params.m_VAO);
				glGenBuffers(1, &VBO);

				glBindVertexArray(params.m_VAO);

				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, count, buffer, GL_STATIC_DRAW);

				// Position attribute
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
				glEnableVertexAttribArray(0);
				// TexCoord attribute
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
				glEnableVertexAttribArray(2);
				glBindVertexArray(0); // Unbind VAO
			}
		}
	};

	// Maybe for this we would have multiple set of vertex and VBO for the different passes we need to make to render everything
	// One pass would be for everything static, another one could be for animated blocks, another one for entities.
	class MinecraftWorldGeometry
	{
	public:
		std::vector<Core::Vector4> m_Vertex;

	private:
		BufferId m_VertexBO;
	};
}
