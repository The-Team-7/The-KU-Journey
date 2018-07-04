#include "SplashState.h"
#include <iostream>
#include "DEFINITIONS.h"
#include "Mainmenu.h"

namespace sg {

	SplashState::SplashState(GameDataRef data)
	{
		this->_data = data;
	}


	SplashState::~SplashState()
	{
	}

	void sg::SplashState::Init()
	{
		sf::Texture texture;


		this->_data->_asset.LoadTexture("Splash_State_bg", SPLASH_SCREEN_BG_PATH);
		_bg.setTexture(this->_data->_asset.GetTexture("Splash_State_bg"));
		this->_data->_asset.LoadSoundBuffer("typing", TYPEWRITER_typing);
		this->_data->_asset.LoadSoundBuffer("typing-enter", TYPEWRITER_enter);
	}

	void sg::SplashState::HandleInput()
	{
		sf::Event event;
		while (this->_data->_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->_data->_window.close();

			}

		}
	}

	void sg::SplashState::Update(float dt)
	{
		if (this->clock.getElapsedTime().asSeconds()>2.0f) {
			this->_data->_machine.AddState(StateRef(new MainMenu(this->_data)),true);
		}
	}

	void sg::SplashState::Draw(float dt)
	{
		this->_data->_window.clear();
		this->_data->_window.draw(this->_bg);
		this->_data->_window.display();
	}

	void sg::SplashState::Pause()
	{
	}

	void sg::SplashState::Resume()
	{
	}
}
