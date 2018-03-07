#pragma once

#include "Engine/State/State.h"
#include "Engine/World/WorldManager.h"

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
		Engine::WorldManager m_WorldManager;
	};
}
