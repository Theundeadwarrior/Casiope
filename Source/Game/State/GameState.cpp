#include "Game/State/GameState.h"

#include "Game/World/GameWorld.h"
#include "Game/Player/Player.h"
#include "Engine/Camera/PerspectiveCamera.h"

#include "Engine/GameEngine.h"

void Game::GameState::OnEnter()
{
	Game::GameWorld* world = new Game::GameWorld();
	Game::Player* player = new Game::Player();
	player->GetCamera()->SetPosition(glm::vec3(5, 2, 5));
	world->SetCurrentPlayer(player); // we're leaking this!!
	m_World = world;
}

void Game::GameState::OnExit()
{
	delete m_World;
}

void Game::GameState::Update()
{
	m_World->Update();

	auto& renderer = Engine::GameEngine::GetInstance()->GetRenderer();
	renderer.StartRendering();
	renderer.RenderWorld(m_World);
	renderer.EndRendering();
}
