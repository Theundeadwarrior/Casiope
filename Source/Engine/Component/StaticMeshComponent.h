#pragma once

#include "Engine/Component/Component.h"
#include "Renderer/Model/Model.h"

namespace Engine
{
	class StaticModelComponent : public Component
	{
	public:
		StaticModelComponent();
		virtual ~StaticModelComponent();

	private:
		Renderer::Model m_Model;
	};
}
