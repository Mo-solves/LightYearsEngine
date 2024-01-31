#include <iostream>
#include "framework/Application.h"

namespace ly
{
	Application::Application()
		:mWindow{sf::VideoMode(900,900), "Light Years"},
		mTargerFrameRate{30.f},
		mTickClock{}
	{
		
	}
	void Application::Run()
	{
		mTickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / mTargerFrameRate;
		while (mWindow.isOpen())
		{
			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
				{
					mWindow.close();
				}
			}

			float frameDeltaTime = mTickClock.restart().asSeconds();
			accumulatedTime += frameDeltaTime;

			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				Tick(targetDeltaTime);
				RenderInternal();
			}
			std::cout << "ticking at framerate: " << 1.f / frameDeltaTime << '\n';

		}
	}
	void Application::TickInternal(float deltaTime)
	{
	}
	void Application::Tick(float deltaTime)
	{
	}
	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();
		
		mWindow.display();
	}
	void Application::Render()
	{
		// rectangle
	//sf::RectangleShape rect{ sf::Vector2f{100,100} };
		sf::CircleShape rect{ 50 };
		rect.setFillColor(sf::Color::Magenta);
		rect.setOrigin(50, 50);
		rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);

		mWindow.draw(rect);
	}
}