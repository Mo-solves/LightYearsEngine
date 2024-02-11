#include "player/PlayerSpaceship.h"
#include <SFML/System.hpp>
#include "framework/MathUtility.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		: Spaceship{ owningWorld, path },
		mMoveInput{},
		mSpeed{ 200.f },
		mShooter{ new BulletShooter{this, 0.1f} }
	{
	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
	}

	void PlayerSpaceship::Shoot()
	{
		if (mShooter)
		{
			mShooter->Shoot();
		}
	}

	void PlayerSpaceship::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			mMoveInput.y = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			mMoveInput.y = 1.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			mMoveInput.x = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			mMoveInput.x = 1.f;
		}

		ClamInputOnEdge();
		NormalizeInput();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}
	}

	void PlayerSpaceship::NormalizeInput()
	{
		Normalize(mMoveInput);
	}

	void PlayerSpaceship::ClamInputOnEdge()
	{
		sf::Vector2f actorLocation = GetActorLocation();
		if (actorLocation.x < 0 && mMoveInput.x == -1)
		{
			mMoveInput.x = 0.f;
		}

		if (actorLocation.x > GetWindowSize().x && mMoveInput.x == 1.f)
		{
			mMoveInput.x = 0.f;
		}

		if (actorLocation.y < 0 && mMoveInput.y == -1.f)
		{
			mMoveInput.y = 0.f;
		}

		if (actorLocation.y > GetWindowSize().y && mMoveInput.y == 1.f)
		{
			mMoveInput.y = 0.f;
		}
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(mMoveInput * mSpeed);
		mMoveInput.x = mMoveInput.y = 0.f;
	}
}
