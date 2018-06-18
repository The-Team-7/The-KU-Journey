#pragma once
#include "State.h"
#include "Game.h"
#include "MainMenu.h"
#include <iostream>


namespace sg {
	class SplashScreen  : public State
	{
	public:
		SplashScreen(GameDataRef data);
		~SplashScreen();

		virtual void Init() override;

		virtual void HandleInput() override;

		virtual void Update(float dt) override;

		virtual void Draw(float dt) override;

	private:
		GameDataRef _data;
		sf::Clock* clock;
		std::string msg;

		sf::Sprite bg;
		sf::Sprite logo;
		sf::Text text;
		sf::Sound typingSound;
		sf::Sound enterSound;
		int count;

	};
}

