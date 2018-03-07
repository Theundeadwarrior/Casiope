#pragma once

namespace Engine
{
	class IState
	{
	public:
		virtual void OnEnter() = 0;

		virtual void OnExit() = 0;

		virtual void Update() = 0;
	};
}
