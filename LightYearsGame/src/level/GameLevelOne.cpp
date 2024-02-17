#include "level/GameLevelOne.h"
#include "enemy/Vanguard.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/VanguardStage.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "enemy/HexagonStage.h"
#include "player/PlayerSpaceship.h"

#include "enemy/UFO.h"


namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World{ owningApp }
	{
		testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
		testPlayerSpaceship.lock()->SetActorRotation(-90.f);
	}

	void GameLevelOne::BeginPlay()
	{
		weak<UFO> testUFO = SpawnActor<UFO>(sf::Vector2f{0.f, 0.f});
		testUFO.lock()->SetActorLocation({ GetWindowSize().x / 2.f, GetWindowSize().y / 2.f
			});
	}


	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
		AddStage(shared<VanguardStage>{new VanguardStage{this}});

		AddStage(shared<WaitStage>{new WaitStage{this, 15.f}});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});

		AddStage(shared<WaitStage>{new WaitStage{this, 15.f}});
		AddStage(shared<HexagonStage>{new HexagonStage{this}});
	}
}