#include "MainMenu.h"
#include "DEFINITIONS.h"
#include "EditorMenu.h"
#include <iostream>

namespace sg {

	MainMenu::MainMenu(GameDataRef data, Menu type): _data(data)
	{
		this->type = type;
		this->plasmaGun = new Weapon(_data, Enums::WeaponType::plasmaGun);
		this->clock = new sf::Clock();
		this->mouseClicked = false;
		n = 0;

	}
	MainMenu::~MainMenu()
	{
	}
	void MainMenu::Init()
	{
		this->_data->_asset.LoadTexture("mainMenuBg",MAIN_MENU_FILEPATH);
		this->bg.setTexture(this->_data->_asset.getTexture("mainMenuBg"));
		this->SpriteClicked = false;
		
		this->typingSound.setBuffer(this->_data->_asset.getSoundBuffer("typing"));
		this->enterSound.setBuffer(this->_data->_asset.getSoundBuffer("typing-enter"));

		if (!mainMusic.openFromFile(MUSIC_MAIN)) {
			std::cout << "music not open";
		}
		mainMusic.play();
		isplaying = true;


		playSound = true;
		this->FillIcons();

	
	}
	void MainMenu::HandleInput()
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
				for (auto i : _icons) {
					if (this->_data->_inputManager.isSpriteClicked(i.second, sf::Mouse::Left, this->_data->_window)) {
						if (playSound) {
								this->typingSound.play();							
						}
						this->SpriteClicked = true;
						iconClicked = i.first;
						break;
					}
				}
				mouseClicked = true;
			}
		}
	}
	void MainMenu::Update(float dt)
	{
		if (mouseClicked) {
			if (clock->getElapsedTime().asSeconds() >= dt) {
				plasmaGun->fire(Enums::facing::right);
				this->clock->restart();
				mouseClicked = false;
			}
		}
		if (this->SpriteClicked) {
			if (this->iconClicked == MenuIcon::about) {
				_icons.clear();

				this->_data->_asset.LoadTexture("aboutDes", ABOUT_DES);
				this->_data->_asset.LoadTexture("back", ICON_BACK);

				sf::Sprite aboutDes;
				aboutDes.setTexture(this->_data->_asset.getTexture("aboutDes"));
				aboutDes.setPosition(SCREEN_WIDTH / 2 - aboutDes.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - aboutDes.getGlobalBounds().height / 2);
				this->_icons[MenuIcon::description] = aboutDes;

				sf::Sprite back;
				back.setTexture(this->_data->_asset.getTexture("back"));
				back.setPosition(aboutDes.getPosition().x + aboutDes.getGlobalBounds().width - back.getGlobalBounds().width, aboutDes.getPosition().y + aboutDes.getGlobalBounds().height + (2*ICON_OFFSET));
				this->_icons[MenuIcon::back] = back;
			}
			if (this->iconClicked == MenuIcon::back) {
				_icons.clear();

				this->FillIcons();
			}
			if (this->iconClicked == MenuIcon::music) {
				if (isplaying) {
					mainMusic.stop();
					_icons[MenuIcon::music].setTexture(this->_data->_asset.getTexture("musicstop"));
					isplaying = false;
				}
				else {
					mainMusic.play();
					_icons[MenuIcon::music].setTexture(this->_data->_asset.getTexture("musicplay"));
					isplaying = true;
				}
			}
			if (this->iconClicked == MenuIcon::sound){
				if (this->playSound) {
					this->playSound = false;
					_icons[MenuIcon::sound].setTexture(this->_data->_asset.getTexture("soundOff"));
				}
				else {
					this->playSound = true;
					_icons[MenuIcon::sound].setTexture(this->_data->_asset.getTexture("soundOn"));
				}
			}
			if (this->iconClicked == MenuIcon::newGame) {
				if (isplaying) {
					mainMusic.stop();
				}
				this->_data->_machine.AddState(StateRef(new LoadingState(this->_data)), true);
			}
			

			if (this->iconClicked==MenuIcon::mapeditor) {
				mainMusic.stop();
				this->_data->_machine.AddState(StateRef(new EditorMenu(this->_data)),true);

			}


		SpriteClicked = false;
		}
	}
	void MainMenu::Draw(float dt)
	{
		this->_data->_window.clear();

		this->_data->_window.draw(bg);
		//if (!_icons.empty()) {
			for (auto i : _icons) {
				this->_data->_window.draw(i.second);
			}
			//if (this->clock->getElapsedTime().asSeconds() >= dt) {
				this->plasmaGun->update();
				//this->clock->restart();
			//}
			
		//}
		
		this->_data->_window.display();
	}

	void MainMenu::FillIcons() {
		switch (this->type) {
			case Menu::mainMenu: {
				this->_data->_asset.LoadTexture("newGame", ICON_NEWGAME);
				this->_data->_asset.LoadTexture("continue", ICON_CONTINUE);
				this->_data->_asset.LoadTexture("controlls", ICON_CONTROLLS);
				this->_data->_asset.LoadTexture("about", ICON_ABOUT);
				this->_data->_asset.LoadTexture("soundOn", ICON_SOUNDON);
				this->_data->_asset.LoadTexture("soundOff", ICON_SOUNDOFF);
				this->_data->_asset.LoadTexture("musicplay", ICON_MUSIC_PLAY);
				this->_data->_asset.LoadTexture("musicstop", ICON_MUSIC_STOP);
				this->_data->_asset.LoadTexture("mapeditor",MAP_EDITOR);

				sf::Sprite newGame;
				newGame.setTexture(this->_data->_asset.getTexture("newGame"));
				newGame.setPosition(SCREEN_WIDTH/2 - newGame.getGlobalBounds().width/2,SCREEN_HEIGHT/2 - newGame.getGlobalBounds().height / 2);
				this->_icons[MenuIcon::newGame] = newGame;

				sf::Sprite Continue;
				Continue.setTexture(this->_data->_asset.getTexture("continue"));
				Continue.setPosition(newGame.getPosition().x , newGame.getPosition().y + newGame.getGlobalBounds().height + ICON_OFFSET);
				this->_icons[MenuIcon::Continue] = Continue;

				sf::Sprite controlls;
				controlls.setTexture(this->_data->_asset.getTexture("controlls"));
				controlls.setPosition(Continue.getPosition().x, Continue.getPosition().y + Continue.getGlobalBounds().height + ICON_OFFSET);
				this->_icons[MenuIcon::controlls] = controlls;

				sf::Sprite about;
				about.setTexture(this->_data->_asset.getTexture("about"));
				about.setPosition(controlls.getPosition().x, controlls.getPosition().y + controlls.getGlobalBounds().height + ICON_OFFSET);
				this->_icons[MenuIcon::about] = about;

				sf::Sprite mapeditor;
				mapeditor.setTexture(this->_data->_asset.getTexture("mapeditor"));
				mapeditor.setPosition(about.getPosition().x, about.getPosition().y + about.getGlobalBounds().height + ICON_OFFSET);
				this->_icons[MenuIcon::mapeditor] = mapeditor;

				sf::Sprite sound;
				if (playSound) {
					sound.setTexture(this->_data->_asset.getTexture("soundOn"));
				}
				else {
					sound.setTexture(this->_data->_asset.getTexture("soundOff"));
				}
				sound.setPosition(/*SCREEN_WIDTH-sound.getGlobalBounds().width-*/ICON_OFFSET, ICON_OFFSET);
				this->_icons[MenuIcon::sound] = sound;

				sf::Sprite music;
				if (isplaying) {
					music.setTexture(this->_data->_asset.getTexture("musicplay"));
				}else
				music.setTexture(this->_data->_asset.getTexture("musicstop"));

				music.setPosition(sound.getPosition().x, sound.getPosition().y + sound.getGlobalBounds().height + ICON_OFFSET);
				this->_icons[MenuIcon::music] = music;
			}
			case Menu::resumeMenu: {

			}
		}
	}
}

