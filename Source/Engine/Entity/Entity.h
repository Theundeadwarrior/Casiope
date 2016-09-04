#pragma once

#include <vector>

#include "Engine/Object/Object.h"
#include "Engine/Component/Component.h"

namespace Engine
{
	class Entity : public Object
	{
	public:
		Entity();
		~Entity();

		void AddComponent(Component* component)
		{
			m_Components.push_back(component);
		}

	private:
		std::vector<Component*> m_Components;
	};
}
