#pragma once

#include <vector>

#include "Engine\Object\Object.h"
#include "Engine\Entity\Component.h"

namespace Engine
{
	class Entity : public Object
	{
	public:
		Entity();
		~Entity();

	private:
		std::vector<Component*> m_Components;
	};
}
