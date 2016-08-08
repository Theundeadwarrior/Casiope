#pragma once

#include <vector>

#include "Engine/World/WorldManager.h"
#include "Game/Player/Player.h"

namespace Game
{
	class GameWorld : public Engine::World
	{
	public:
		void SetCurrentPlayer(Player* player);

		virtual void Update() override;

	private:
		Player* m_CurrentPlayer;
	};
}