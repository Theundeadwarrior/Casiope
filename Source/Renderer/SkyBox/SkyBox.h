#pragma once

#include "Renderer/Model/Model.h"

#include <GL/glew.h>
#include <string>

namespace GraphicsCore
{
	class Mesh;
}

namespace Renderer
{
	class SkyBox : public Model
	{
	public:
		SkyBox();
		SkyBox(const std::string& textureFileName);
		~SkyBox();

		void Init(const std::string& textureFileName); // todo: Change it to reset

	private:
		bool m_IsInitialized;
	};
}



