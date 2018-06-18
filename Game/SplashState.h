#pragma once
#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "MainMenuState.h"
namespace sg {
	class SplashState :public State
	{
	public:
		SplashState(GameDataRef data);
		~SplashState();

		// Inherited via state
		virtual void Init() override;
		virtual void HandleInput() override;
		virtual void Update(float dt) override;
		virtual void Draw(float dt) override;
		virtual void Pause() override;
		virtual void Resume() override;
	private:

		GameDataRef _data;
		sf::Clock clock;
		sf::Sprite _bg;

	};

}
