#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"


namespace ly
{
	World::World(Application* owningApp)
		:mOwningApp{ owningApp },
		mBeganPlay(false),
		mActors{},
		mPendingActors{},
		mCurrentStage{mGameStages.end()},
		mGameStages{}
	{

	}

	void World::BeginPlayInterval()
	{
		if (!mBeganPlay)
		{
			mBeganPlay = true;
			BeginPlay();
			InitGameStages();
			StartStages();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		for (shared<Actor> actor : mPendingActors)
		{
			mActors.push_back(actor);
			actor->BeginPlayInterval();
		}
		mPendingActors.clear();

		// iterator
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			iter->get()->TickInternal(deltaTime);
			++iter;
		}

		if (mCurrentStage != mGameStages.end())
		{
			mCurrentStage->get()->TickStage(deltaTime);
		}

		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : mActors)
		{
			actor->Render(window);
		}

	}

	World::~World()
	{
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return mOwningApp->GetWindowSize();
	}

	void World::CleanCycle()
	{
		// iterator
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				iter = mActors.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	void World::AddStage(const shared<GameStage>& newStage)
	{
		mGameStages.push_back(newStage);
	}

	void World::BeginPlay()
	{

	}

	void World::Tick(float deltaTime)
	{

	}

	void World::InitGameStages()
	{

	}

	void World::AllGameStageFinished()
	{
		LOG("All Stage Finished");
	}

	void World::NextGameStage()
	{
		mCurrentStage = mGameStages.erase(mCurrentStage);

		if (mCurrentStage != mGameStages.end())
		{
			mCurrentStage->get()->StartStage();
			mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
		}
		else
		{
			AllGameStageFinished();
		}
	}

	void World::StartStages()
	{
		mCurrentStage = mGameStages.begin();
		mCurrentStage->get()->StartStage();
		mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
	}
}
