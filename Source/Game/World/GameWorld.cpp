#include "GameWorld.h"


#include "Engine/Camera/PerspectiveCamera.h"
#include "Game/Player/Player.h"


namespace Game
{
	void GameWorld::SetCurrentPlayer(Player * player)
	{
		m_CurrentPlayer = player;
		m_Camera = m_CurrentPlayer->GetCamera();
	}

	void GameWorld::OnKeyboardInputEvent(const Core::KeyboardInputEvent & event)
	{
		//if (event.m_Key == )
	}
}
