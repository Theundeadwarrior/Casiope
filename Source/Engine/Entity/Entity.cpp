#include "Entity.h"


namespace Engine
{
	Entity::Entity()
	{
	}


	Entity::~Entity()
	{
		for (auto* comp : m_Components)
		{
			delete comp;
		}
		m_Components.clear();
	}

}
