#pragma once

#include "Renderer/Mesh/Mesh.h"

namespace Engine
{
	class VisualComponent
	{
	public:
		VisualComponent();
		virtual ~VisualComponent();

	private:
		Renderer::Mesh m_Mesh;
	};
}

