#pragma once

namespace ly
{
	class Application;
	class World
	{
	public:
		World(Application* owningApp);

		void BeginPlayInterval();
		void TickInternal(float deltaTime);

		virtual ~World();

	private:
		void BeginPlay();
		void Tick(float deltaTime);
		Application* mOwningApp;
		bool mBeganPlay;
	};
}