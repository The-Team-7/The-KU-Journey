#include "SplashScreen.h"
#include "DEFINITIONS.h"

namespace sg {

	SplashScreen::SplashScreen(GameDataRef data) : _data(data)
	{
	}


	SplashScreen::~SplashScreen()
	{
	}

	void sg::SplashScreen::Init()
	{
		this->_data->_asset.LoadTexture("splashScreen", SPLASH_SCREEN_FILEPATH);
		bg.setTexture(this->_data->_asset.getTexture("splashScreen"));
		//sound
		this->_data->_asset.LoadSoundBuffer("typing", TYPEWRITER_typing);
		this->_data->_asset.LoadSoundBuffer("typing-enter", TYPEWRITER_enter);

		this->typingSound.setBuffer(this->_data->_asset.getSoundBuffer("typing"));
		this->enterSound.setBuffer(this->_data->_asset.getSoundBuffer("typing-enter"));
		
		//typewriter effect
		this->clock = new sf::Clock();
		this->msg = "This is a tale of Kale who found a mysterious\nbook and now has to save his college KU.";
		count = 0;
		this->_data->_asset.LoadFont("narratorFont",FONT);		
		this->text.setFont(this->_data->_asset.getFont("narratorFont"));
		this->text.setFillColor(sf::Color(136, 136, 136,255));
		this->text.setCharacterSize(60);
		this->text.setPosition(400,200);


	}

	void sg::SplashScreen::HandleInput()
	{
		sf::Event event;
		if (this->_data->_window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->_window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					this->_data->_window.close();
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				this->_data->_machine.AddState(StateRef(new MainMenu(_data, MainMenu::Menu::mainMenu)), true);
			}
		}
	}

	void sg::SplashScreen::Update(float dt)
	{
		if (this->clock->getElapsedTime().asSeconds() >= SPLASH_SCREEN_TIME) {
			this->_data->_machine.AddState(StateRef(new MainMenu(_data,MainMenu::Menu::mainMenu)),true);
		}
		if (this->clock->getElapsedTime().asSeconds() >= .1f && count <= this->msg.length()) {
			count++;
			if (msg.substr(count-1, count) == " " || msg.substr(count - 1, count) == "\n") {
				this->enterSound.play();
			}
			else {
				this->typingSound.play();
			}
			text.setString(msg.substr(0, count));
			this->clock->restart();
		}
	}
	void sg::SplashScreen::Draw(float dt)
	{
		this->_data->_window.clear();
		this->_data->_window.draw(bg);
		this->_data->_window.draw(text);
		this->_data->_window.display();
	}
}