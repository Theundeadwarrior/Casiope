#pragma once

#include <list>
#include <vector>

namespace Renderer 
{ 
	class Model; 
	class Light;
}

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
		virtual std::vector<Renderer::Light>* GetLights() { return nullptr; }
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
