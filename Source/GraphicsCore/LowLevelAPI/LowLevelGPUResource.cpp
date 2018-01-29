#include "LowLevelGPUResource.h"


namespace GraphicsCore
{
	VertexBufferResource::VertexBufferResource()
		: m_IsInitialized(false)
	{
	}

	VertexBufferResource::~VertexBufferResource()
	{
		Release();
	}

	void VertexBufferResource::Init(VertexBufferType type, void * buffer, uint32_t count)
	{
		Release();
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		if (type == VertexBufferType::V3FT2F)
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
		else if (type == VertexBufferType::V3BT2B)
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
		else if (type == VertexBufferType::V4B)
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

	void VertexBufferResource::Release()
	{
		if (m_IsInitialized)
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}
		m_IsInitialized = false;
	}

	FrameBufferResource::FrameBufferResource()
		: m_IsInitialized(false)
	{
	}

	FrameBufferResource::~FrameBufferResource()
	{
		Release();
	}

	void FrameBufferResource::Init(uint32_t sizeX, uint32_t sizeY)
	{
		Release();

		glGenFramebuffers(1, &FBO);

		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, sizeX, sizeY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		GLfloat borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texId, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_IsInitialized = true;
	}

	void FrameBufferResource::Release()
	{
		if (m_IsInitialized)
		{
			glDeleteTextures(1, &texId);
			glDeleteFramebuffers(1, &FBO);
		}
	}

	ShaderStorageBufferResource::ShaderStorageBufferResource()
		: m_IsInitialized(false)
	{
	}

	ShaderStorageBufferResource::~ShaderStorageBufferResource()
	{
		Release();
	}

	void ShaderStorageBufferResource::Init(size_t bufferSize, BufferUsage usage, void* buffer = nullptr)
	{
		Release();

		glGenBuffers(1, &SSBO);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO);
	
		if (buffer == nullptr)
		{
			glBufferData(GL_SHADER_STORAGE_BUFFER, bufferSize, 0, (GLenum)usage);
		}
		else
		{
			glBufferData(GL_SHADER_STORAGE_BUFFER, bufferSize, buffer, (GLenum)usage);
		}

		m_IsInitialized = true;
	}

	void ShaderStorageBufferResource::Release()
	{
		if (m_IsInitialized)
		{
			glDeleteBuffers(1, &SSBO);
		}
	}
}
