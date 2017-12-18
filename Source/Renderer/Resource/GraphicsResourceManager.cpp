#include "Renderer/Resource/GraphicsResourceManager.h"

#include "Core/File/ImageUtilities.h"
#include "Core/File/FileSystem.h"

#include <malloc.h>

namespace
{
	uint32_t Hash64to32(uint64_t key)
	{
		key = (~key) + (key << 18); // key = (key << 18) - key - 1;
		key = key ^ (key >> 31);
		key = key * 21; // key = (key + (key << 2)) + (key << 4);
		key = key ^ (key >> 11);
		key = key + (key << 6);
		key = key ^ (key >> 22);
		return (uint32_t)key;
	}
}

namespace Renderer
{
	MeshManager::~MeshManager()
	{
		for (auto& it : m_MeshBank)
		{
			delete it.second;
		}
		m_MeshBank.clear();
	}

	MeshId MeshManager::AddMesh(GraphicsCore::Mesh* const mesh)
	{
		// todo refactor this to have better uid
		uint64_t meshAddr = reinterpret_cast<uint64_t>(mesh);
		MeshId meshId = static_cast<MeshId>(Hash64to32(meshAddr));
		m_MeshBank[meshId] = mesh;
		return meshId;
	}

	void MeshManager::RemoveMesh(MeshId geometryId)
	{
		auto it = m_MeshBank.find(geometryId);
		if (it != m_MeshBank.end()) //id exists!
		{
			delete (*it).second;
			m_MeshBank.erase(it);
		}
	}

	GraphicsCore::Mesh* MeshManager::GetMesh(MeshId geometryId)
	{
		return m_MeshBank[geometryId];
	}

	TextureId TextureManager::InsertTexture(GraphicsCore::Texture* const texture)
	{
		TextureId id = texture->GetID();
		m_TextureBank[id] = texture;
		return id;
	}

	TextureManager::~TextureManager()
	{
		for (auto& it : m_TextureBank)
		{
			delete it.second;
		}
		m_TextureBank.clear();
	}

	TextureId TextureManager::CreateTextureFromImage(const Core::Image<unsigned char>& image, GraphicsCore::TextureFormat format)
	{
		GraphicsCore::Texture* texture = new GraphicsCore::Texture(image, format);
		return InsertTexture(texture);
	}

	TextureId TextureManager::CreateTextureFromFile(const char * pathToFile, GraphicsCore::TextureFormat format)
	{
		Core::Image<unsigned char> img;
		Core::LoadImageFromFile(img, pathToFile);
		return CreateTextureFromImage(img, format);
	}

	void TextureManager::RemoveTexture(TextureId textureID)
	{
		auto it = m_TextureBank.find(textureID);
		if (it != m_TextureBank.end()) //id exists!
		{
			delete (*it).second;
			m_TextureBank.erase(it);
		}
	}

	ShaderManager::~ShaderManager()
	{
		for (auto& it : m_ShaderBank)
		{
			delete it.second;
		}
		m_ShaderBank.clear();
	}

	ShaderId ShaderManager::LinkShadersIntoProgram(const char * vsFileName, const char * psFileName)
	{
		auto* fsInstance = Core::FileSystem::GetInstance();
		auto* vsFile = fsInstance->OpenRead(vsFileName);
		size_t vsBufferSize = vsFile->GetSize() + 1;
		char* vsCode = static_cast<char*>(malloc(vsBufferSize));
		vsFile->Read(reinterpret_cast<uint8*>(vsCode), vsBufferSize);
		vsCode[vsBufferSize - 1] = '\0';
		fsInstance->CloseFile(vsFile);

		auto* psFile = fsInstance->OpenRead(psFileName);
		size_t psBufferSize = psFile->GetSize() + 1;
		char* psCode = static_cast<char*>(malloc(psBufferSize));
		psFile->Read(reinterpret_cast<uint8*>(psCode), psBufferSize);
		psCode[psBufferSize - 1] = '\0';
		fsInstance->CloseFile(psFile);

		auto* shaderProgram = new GraphicsCore::ShaderProgram(vsCode, psCode, "");
		auto shaderId = shaderProgram->GetProgramId();
		m_ShaderBank[shaderId] = shaderProgram;

		free(psCode);
		free(vsCode);

		return shaderId;
	}

	void ShaderManager::RemoveShader(ShaderProgramId shaderId)
	{
		auto it = m_ShaderBank.find(shaderId);
		if (it != m_ShaderBank.end()) //id exists!
		{
			delete (*it).second;
			m_ShaderBank.erase(it);
		}
	}
}

