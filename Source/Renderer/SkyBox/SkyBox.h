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
		void SetImage(SkyBoxFaces face, const Core::Image<unsigned char>& image)
		{
			m_Images[(unsigned int)face] = image;
		}

		Core::Image<unsigned char>& GetImage(SkyBoxFaces face)
		{
			return m_Images[(unsigned int)face];
		}

	private:
		Core::Image<unsigned char> m_Images [SkyBoxFaces::e_FaceCount];
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



