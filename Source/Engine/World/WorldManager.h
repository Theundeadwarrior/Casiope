#pragma once

#include <list>

namespace Renderer { class Model; }

namespace Engine
{
	class PerspectiveCamera;

	class World
	{
	public:
		World();
		virtual ~World() {};

		virtual void Update();

		virtual std::list<Renderer::Model*>* GetModels() { return nullptr; }
		PerspectiveCamera* GetCamera() const { return m_Camera; }

	protected:
		PerspectiveCamera* m_Camera; // todo: Move this to a player class!! We could have multiple players!
	};


	class WorldManager
	{
	public:
		WorldManager();
		~WorldManager();

		World* GetCurrentWorld() const { return m_CurrentWorld; }

		void SetCurrentWorld(World* world)
		{
			m_CurrentWorld = world;
		}

		void Update();
	private:
		World* m_CurrentWorld;
	};
}
