#pragma once
#include "framework/Object.h"
#include <SFML/Graphics.hpp>
#include "framework/Object.h"
#include "framework/Core.h"

class b2Body;
namespace ly
{
	class World;
	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();
		void BeginPlayInterval();
		void TickInternal(float deltaTime);
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void SetTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window);

		void SetActorLocation(const sf::Vector2f& newLoc);
		void SetActorRotation(float newRot);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(float offsetAmt);
		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;
		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;
		sf::FloatRect GetActorGlobalBounds() const;

		sf::Vector2u GetWindowSize() const;

		World* GetWorld() const { return mOwningWorld; }

		bool IsActorOutOfWindowBounds() const;

		void SetEnablePhysics(bool enable);

	private:
		void InitializedPhysics();
		void UnIntializedPhysics();
		void CenterPivot();
		void UpdatePhysicsBodyTransform();
		World* mOwningWorld;
		bool mHasBeganPlay;

		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;

		b2Body* mPhysicsBody;
		bool mPhysicsEnabled;
	};
}