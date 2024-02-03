#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
	Actor::Actor(World* owningWorld)
		:mOwningWorld{owningWorld},
		mHasBeganPlay{false}
	{
	}
	Actor::~Actor()
	{
	}
	void Actor::BeginPlayInterval()
	{
		if (!mHasBeganPlay)
		{
			mHasBeganPlay = true;
			BeginPlay();
		}
	}

	// This is for the child class to override
	void Actor::BeginPlay()
	{
		LOG("Actor begin play");
	}

	// This is for the child class to override
	void Actor::Tick(float deltaTime)
	{
		LOG("Actor Ticking");
	}
}
