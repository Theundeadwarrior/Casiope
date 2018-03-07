#pragma once

#include "Engine/State/State.h"

namespace Engine
{
	class World;
}

namespace Game
{
	class GameState : public Engine::IState
	{
	public:
		// Inherited via IState
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual void Update() override;

	private:
		Engine::World* m_World;
	};
}
