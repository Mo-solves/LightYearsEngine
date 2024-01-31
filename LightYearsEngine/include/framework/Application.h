#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
	class Application
	{
	public:
		Application();
		void Run();
	private:
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Tick(float deltaTime);
		virtual void Render();

		sf::RenderWindow mWindow;
		float mTargerFrameRate;
		sf::Clock mTickClock;
	};
}