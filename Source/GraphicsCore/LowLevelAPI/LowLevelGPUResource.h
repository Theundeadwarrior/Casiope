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

	static BufferId BuildVertexBufferFromVertexArray(GeometryGPUType type, void * buffer, uint32_t count)
	{
		GLuint VAO;
		GLuint VBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);


		if (type == GeometryGPUType::V3FT2F)
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, count, buffer, GL_STATIC_DRAW);

			// Position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			// TexCoord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
		}
		else if (type == GeometryGPUType::V4B)
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, count, buffer, GL_STATIC_DRAW);

			// Position attribute
			glVertexAttribPointer(0, 4, GL_UNSIGNED_BYTE, GL_FALSE, 4 * sizeof(GL_UNSIGNED_BYTE), (GLvoid*)0);
			glEnableVertexAttribArray(0);
		}

		glBindVertexArray(0); // Unbind VAO
		return VAO;
	}
}

