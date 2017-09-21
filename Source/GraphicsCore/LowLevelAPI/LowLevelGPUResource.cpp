#include "LowLevelGPUResource.h"


namespace GraphicsCore
{
	VertexBufferResource::VertexBufferResource()
		: m_IsInitialized(false)
	{
	}

	VertexBufferResource::~VertexBufferResource()
	{
		ReleaseBuffer();
	}

	void VertexBufferResource::InitBuffer(GeometryGPUType type, void * buffer, uint32_t count)
	{
		ReleaseBuffer();
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
		else if (type == GeometryGPUType::V3BT2B)
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, count, buffer, GL_STATIC_DRAW);

			// Position attribute
			glVertexAttribPointer(0, 3, GL_BYTE, GL_FALSE, 5 * sizeof(GLbyte), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			// TexCoord attribute
			glVertexAttribPointer(2, 2, GL_BYTE, GL_FALSE, 5 * sizeof(GLbyte), (GLvoid*)(3 * sizeof(GLbyte)));
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
		m_IsInitialized = true;
	}

	void VertexBufferResource::ReleaseBuffer()
	{
		if (m_IsInitialized)
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}
		m_IsInitialized = false;
	}

}
