#pragma once

#include "GraphicsCore/GraphicsType.h"
#include <GL/glew.h>
#include <glm/include/glm/glm.hpp>

namespace GraphicsCore
{
	enum class VertexBufferType : uint8_t
	{
		V4B,
		V4F,
		V3BT2B,
		V3BN3BT2B,
		V3FT2F // V1, V2, V3, UV1, UV2
	};

	enum class BufferUsage
	{
		StreamDraw = GL_STREAM_DRAW,
		StreamRead = GL_STREAM_READ,
		StreamCopy = GL_STREAM_COPY,
		StaticDraw = GL_STATIC_DRAW,
		StaticRead = GL_STATIC_READ,
		StaticCopy = GL_STATIC_COPY,
		DynamicDraw = GL_DYNAMIC_DRAW,
		DynamicRead = GL_DYNAMIC_READ,
		DynamicCopy = GL_DYNAMIC_COPY
	};

	struct VertexBufferResource
	{
		VertexBufferResource();
		~VertexBufferResource();

		void Init(VertexBufferType type, void* vertices, uint32_t vertexCount, void* indices = nullptr, uint32_t indexCount = 0);
		void Release();

		bool IsInitialized() const { return m_IsInitialized; }
		bool IsUsingEBO() const { return m_IsUsingEBO; }

		BufferId VAO;
		BufferId VBO;
		BufferId EBO;
	
	private:
		bool m_IsInitialized;
		bool m_IsUsingEBO;
	};

	struct FrameBufferResource
	{
		FrameBufferResource();
		~FrameBufferResource();

		void Init(uint32_t sizeX, uint32_t sizeY);
		void Release();

		TextureId texId;
		BufferId FBO;

	private:
		bool m_IsInitialized;
	};

	struct ShaderStorageBufferResource
	{
		ShaderStorageBufferResource();
		~ShaderStorageBufferResource();

		void Init(size_t bufferSize, BufferUsage usage, void* buffer);
		void Release();

		BufferId SSBO;

	private:
		bool m_IsInitialized;
	};
}

