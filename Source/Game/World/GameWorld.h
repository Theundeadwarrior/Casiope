#pragma once

#include <vector>

#include "Engine/World/WorldManager.h"
#include "Game/Player/Player.h"

#include "Core/Input/KeyboardEvent.h"

namespace Game
{
	class GameWorld : public Engine::World, public Core::KeyboardInputListener
	{
	public:
		void SetCurrentPlayer(Player* player);

	private:
		Player* m_CurrentPlayer;

		// Inherited via InputKeyboardListener
		virtual void OnKeyboardInputEvent(const Core::KeyboardInputEvent & event) override;
	};
}
