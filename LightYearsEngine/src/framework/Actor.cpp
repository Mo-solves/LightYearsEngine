#include "framework/Actor.h"
#include "framework/AssetManager.h"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		:mOwningWorld{owningWorld},
		mHasBeganPlay{false},
		mSprite{},
		mTexture{}
	{
		SetTexture(texturePath);
	}
	Actor::~Actor()
	{
		LOG("Actor Destroyed");
	}
	void Actor::BeginPlayInterval()
	{
		if (!mHasBeganPlay)
		{
			mHasBeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
		{
			Tick(deltaTime);
		}
	}

	// This is for the child class to override
	void Actor::BeginPlay()
	{
	}

	// This is for the child class to override
	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::SetTexture(const std::string& texturePath)
	{

		mTexture = AssetManager::Get().LoadTexture(texturePath);
		if (!mTexture) return;

		mSprite.setTexture(*mTexture);

		int textureWidth = mTexture->getSize().x;
		int textureHeight = mTexture->getSize().y;

		mSprite.setTextureRect(sf::IntRect(sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight}));
	}
	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(mSprite);
	}
}
