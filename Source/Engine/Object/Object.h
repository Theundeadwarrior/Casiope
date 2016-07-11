#pragma once
#include <glm/glm.hpp>

namespace Engine
{
	class Object
	{
	public:
		Object();
		~Object();

	private:
		glm::mat4 m_Transform;
	};
}

