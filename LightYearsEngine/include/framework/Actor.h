#pragma once

namespace ly
{
	class World;
	class Actor
	{
	public:
		Actor(World* owningWorld);
		virtual ~Actor();
		void BeginPlayInterval();
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

	private:
		World* mOwningWorld;
		bool mHasBeganPlay;
	};
}