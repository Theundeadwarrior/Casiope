#pragma once

#include "Engine/Component/Component.h"
#include "Renderer/Mesh/Mesh.h"

namespace Engine
{
	class StaticMeshComponent : public Component
	{
	public:
		StaticMeshComponent();
		virtual ~StaticMeshComponent();

	private:
		Renderer::Mesh m_Mesh;
	};
}
