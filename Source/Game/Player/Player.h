#pragma once

namespace Engine
{
	class Camera;
}

namespace Game
{
	class Player
	{
	public:
		Player();
		~Player();
		
		Engine::Camera* GetCamera();

	private:
		Engine::Camera* m_FPCamera;
	};
}
