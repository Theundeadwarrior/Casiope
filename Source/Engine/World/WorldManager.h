#pragma once


namespace Engine
{
	class Camera;

	class World
	{
	public:
		World();
		virtual ~World() {};
		virtual void Update();

		Camera* GetCamera() const { return m_Camera; }

	protected:
		Camera* m_Camera; // todo: Move this to a player class!! We could have multiple players!
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
