#pragma once

#include "Core\File\ImageUtilities.h"

#ifdef _WIN32
#include <gl/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

namespace Renderer
{
	enum SkyBoxFaces
	{
		e_FaceFront,
		e_FaceBack,
		e_FaceTop,
		e_FaceBottom,
		e_FaceLeft,
		e_FaceRight,
		e_FaceCount
	};

	struct SkyBoxParams
	{
	public:
		void SetImageParam(SkyBoxFaces face, const Core::ImageParameters<unsigned char>& image)
		{
			m_Images[(unsigned int)face] = image;
		}

		Core::ImageParameters<unsigned char>& GetImageParam(SkyBoxFaces face)
		{
			return m_Images[(unsigned int)face];
		}

	private:
		Core::ImageParameters<unsigned char> m_Images [SkyBoxFaces::e_FaceCount];
	};



	class SkyBox
	{
	public:
		SkyBox();
		SkyBox(const SkyBoxParams& params);
		~SkyBox();

		void Init(const SkyBoxParams& params); // todo: Change it to reset


	private:
		unsigned int m_TextureId;
	};
}



