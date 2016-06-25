#pragma once

#ifdef _WIN32
#include <gl/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

namespace Renderer
{

	class SkyBoxParams
	{
		const char* front_texture_file_name;
		const char* back_texture_file_name;
		const char* top_texture_file_name;
		const char* bottom_texture_file_name;
		const char* left_texture_file_name;
		const char* right_texture_file_name;
	};

	enum SkyBoxFaces
	{
		e_FrontFace,
		e_BackFace,
		e_TopFace,
		e_BottomFace,
		e_LeftFace,
		e_RightFace
	};

	class SkyBox
	{
	public:
		SkyBox();
		SkyBox(const SkyBoxParams& params);
		~SkyBox();


	private:
		unsigned int m_TextureIds[6];
	};
}



