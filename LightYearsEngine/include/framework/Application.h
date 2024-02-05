#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
	class World;
	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title,
			sf::Uint32 style);
		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

	private:
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Tick(float deltaTime);
		virtual void Render();

		sf::RenderWindow mWindow;
		float mTargerFrameRate;
		sf::Clock mTickClock;

		shared<World> currentWorld;
		sf::Clock mCleanCycleClock;
		float mCleanCycleInterval;
	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld{ new WorldType{this} };
		currentWorld = newWorld;
		currentWorld->BeginPlayInterval();
		return newWorld;
	}
}