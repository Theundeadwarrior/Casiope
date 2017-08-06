#include "Renderer/Resource/GraphicsResourceManager.h"

#include "Core/File/ImageUtilities.h"
#include "Core/File/FileSystem.h"

#include <malloc.h>


namespace Renderer
{
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
		TextureBank::iterator it(m_TextureBank.find(textureID));
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

	ShaderId ShaderManager::CreateShaderProgram(const char * vsFileName, const char * psFileName)
	{
		auto* fsInstance = Core::FileSystem::GetInstance();
		auto* vsFile = fsInstance->OpenRead(vsFileName);
		size_t vsFileSize = vsFile->GetSize();
		char* vsCode = static_cast<char*>(malloc(vsFileSize));
		vsFile->Read(reinterpret_cast<uint8*>(vsCode), vsFileSize);
		fsInstance->CloseFile(vsFile);

		auto* psFile = fsInstance->OpenRead(psFileName);
		size_t psFileSize = psFile->GetSize();
		char* psCode = static_cast<char*>(malloc(psFileSize));
		psFile->Read(reinterpret_cast<uint8*>(psCode), psFileSize);
		fsInstance->CloseFile(psFile);

		auto* shaderProgram = new GraphicsCore::ShaderProgram(vsCode, psCode, "");
		auto shaderId = shaderProgram->GetProgramId();
		m_ShaderBank[shaderId] = shaderProgram;

		return shaderId;
	}

}

