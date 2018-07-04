#include "MainMenu.h"
#include "DEFINITIONS.h"
#include "EditorMenu.h"
#include "IntroLevel.h"
#include "LoadingScreen.h"



#include <iostream>
namespace sg {

	MainMenu::MainMenu(GameDataRef data) : _data(data)
	{
		this->mouseClicked = false;
		this->state = MenuState::starting;
		n = 0;

		/*load these somewhere. for now i've put it here*/
		_data->_asset.LoadTexture("parallaxSky", BACKGROUND_sky);
		_data->_asset.LoadTexture("parallaxCloud1", BACKGROUND_cloud_1);
		_data->_asset.LoadTexture("parallaxCloud2", BACKGROUND_cloud_2);
		_data->_asset.LoadTexture("parallaxCloud3", BACKGROUND_cloud_3);
		_data->_asset.LoadTexture("parallaxMountain1", BACKGROUND_mountain_1);
		_data->_asset.LoadTexture("parallaxMountain2", BACKGROUND_mountain_2);
		_data->_asset.LoadTexture("parallaxMountain3", BACKGROUND_mountain_3);

		this->_data->_asset.LoadTexture("menu", MENU);
		this->_data->_asset.LoadTexture("pointer", POINTER);
		/*this->_data->_asset.LoadTexture("newGame", ICON_NEWGAME);
		this->_data->_asset.LoadTexture("continue", ICON_CONTINUE);
		this->_data->_asset.LoadTexture("controlls", ICON_CONTROLLS);
		this->_data->_asset.LoadTexture("about", ICON_ABOUT);
		*/
		this->_data->_asset.LoadTexture("soundOn", ICON_SOUNDON);
		this->_data->_asset.LoadTexture("soundOff", ICON_SOUNDOFF);
		this->_data->_asset.LoadTexture("musicplay", ICON_MUSIC_PLAY);
		this->_data->_asset.LoadTexture("musicstop", ICON_MUSIC_STOP);
		this->_data->_asset.LoadTexture("back", ICON_BACK);
		this->_data->_asset.LoadFont("Motira", "Resources/Motira.otf");
	}
	MainMenu::~MainMenu()
	{
	}
	void MainMenu::Init()
	{
		//parallax
		this->setParalax();


		this->SpriteClicked = false;
		this->pointerActive = false;

		this->typingSound.setBuffer(this->_data->_asset.GetSoundBuffer("typing"));
		this->enterSound.setBuffer(this->_data->_asset.GetSoundBuffer("typing-enter"));
		//music
		if (!mainMusic.openFromFile(MUSIC_MAIN)) {
			std::cout << "music not open";
		}
		isplaying = true;
		playSound = true;
		if (this->isplaying) {
			mainMusic.play();
		}
		this->LoadButtons();
	}
	void MainMenu::HandleInput()
	{
		sf::Event event;
		if (this->_data->_window.pollEvent(event)) {

			if(event.type==sf::Event::KeyPressed) {
				if (event.key.code==sf::Keyboard::Escape) {
					this->_data->_window.close();
				}
			}
			if (event.type == sf::Event::MouseMoved) {
				if (this->state == MenuState::starting) {

					//if (this->menuRect->contains(sf::Mouse::getPosition(_data->_window))) {
					for (auto i : _buttonsToPoint) {
						if (this->_data->_settings._mouse.getGlobalBounds().intersects(i->getGlobalBounds())) {
							this->pointerActive = true;
							this->pointer[0].setPosition(this->b.ornament1.getPosition().x - 10, i->getPosition().y - 5);
							this->pointer[1].setPosition(this->b.ornament1.getPosition().x + this->b.ornament1.getGlobalBounds().width - this->pointer[1].getGlobalBounds().width - 10, i->getPosition().y);
							//i->setColor(sf::Color(117, 195, 156));
							break;
						}
						else {
							//i->setColor(sf::Color(255, 255, 255));
							this->pointerActive = false;
						}
					}

					//}
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				mouseClicked = true;
				switch (this->state) {
				case(MenuState::starting):
				{
					for (auto i : _startingState) {
						if (this->_data->_inputManager.isSpriteClicked(*i, sf::Mouse::Left, this->_data->_window)) {
							if (playSound) {
								this->typingSound.play();
							}
							this->SpriteClicked = true;
							iconClicked = i;
							break;
						}
					}

					break;
				}
				case(MenuState::about):
				{
					for (auto i : _aboutState) {
						if (this->_data->_inputManager.isSpriteClicked(*i, sf::Mouse::Left, this->_data->_window)) {
							if (playSound) {
								this->typingSound.play();
							}
							this->SpriteClicked = true;
							iconClicked = i;
							break;
						}
					}
					break;
				}
				}
			}
		}
	}
	void MainMenu::Update(float dt)
	{

		//moving parallax
		{
			this->moveparallax();
		}

		if (this->SpriteClicked) {
			if (this->_buttonName[this->iconClicked] == buttonName::aboutButton) {
				this->pointerActive = false;
				this->state = MenuState::about;

			}
			if (this->_buttonName[this->iconClicked] == buttonName::back) {
				this->state = MenuState::starting;
			}
			if (this->_buttonName[this->iconClicked] == buttonName::music) {
				if (isplaying) {
					mainMusic.stop();
					this->iconClicked->setTexture(this->_data->_asset.GetTexture("musicstop"));
					isplaying = false;
				}
				else {
					mainMusic.play();
					this->iconClicked->setTexture(this->_data->_asset.GetTexture("musicplay"));
					isplaying = true;
				}
			}
			if (this->_buttonName[this->iconClicked] == buttonName::sound) {
				if (this->playSound) {
					this->playSound = false;
					(this->iconClicked)->setTexture(this->_data->_asset.GetTexture("soundOff"));
				}
				else {
					this->playSound = true;
					(this->iconClicked)->setTexture(this->_data->_asset.GetTexture("soundOn"));
				}
			}
			if (this->_buttonName[this->iconClicked] == buttonName::continueGame) {

			}
			if (this->_buttonName[this->iconClicked] == buttonName::newGame) {
				if (isplaying) {
					mainMusic.stop();
				}
				this->_data->_machine.AddState(StateRef(new LoadingScreen(this->_data)), true);
			}
			if (this->_buttonName[this->iconClicked] == buttonName::mapEditor) {
				if (isplaying) {
					mainMusic.stop();
				}
				this->_data->_machine.AddState(StateRef(new EditorMenu(this->_data)), true);
			}
			SpriteClicked = false;
		}
	}
	void MainMenu::Draw(float dt)
	{

		this->_data->_window.clear();
		//drawing the parallax
		this->drawParallax();

		switch (this->state) {
		case(MenuState::about): {
			this->_data->_window.draw(aboutText);
			for (auto i : _aboutState) {
				this->_data->_window.draw(*i);
			}
			break;
		}
		case(MenuState::starting): {
			this->_data->_window.draw(this->menuRect);
			if (pointerActive) {
				pointer[0].setColor(sf::Color(117, 195, 156));
				this->_data->_window.draw(pointer[0]);
			}
			for (auto j : _startingState) {
				this->_data->_window.draw(*j);
			}
			if (pointerActive) {

				this->_data->_window.draw(pointer[1]);
			}
			this->_data->_window.draw(b.ornament1);
			this->_data->_window.draw(b.ornament2);
			break;
		}
		}

		//this->_data->_window.draw(menu);
		this->_data->_window.display();
	}
	void MainMenu::LoadButtons() {
		sf::Vector2f pos(600, 300);

		//pointer
		pointer[0].setTexture(this->_data->_asset.GetTexture("pointer"));
		pointer[1].setTexture(this->_data->_asset.GetTexture("pointer"));
		menuRect.setTexture(this->_data->_asset.GetTexture("menu"));
		menuRect.setPosition(pos);
		//main menu
		b.ornament1.setTexture(this->_data->_asset.GetTexture("menu"));
		sf::IntRect i0(8, 648, 621, 103);
		b.ornament1.setTextureRect(i0);
		b.ornament1.setPosition(pos.x + 8, pos.y + 8);

		b.newGame.setTexture(this->_data->_asset.GetTexture("menu"));
		sf::IntRect i1(8/*149*/, 131, 621/*339*/, 117);
		b.newGame.setTextureRect(i1);
		b.newGame.setPosition(pos.x + 8/*149*/, pos.y + 131);
		this->_startingState.push_back(&b.newGame);
		this->_buttonsToPoint.push_back(&b.newGame);
		this->_buttonName[&b.newGame] = buttonName::newGame;

		b.Continue.setTexture(this->_data->_asset.GetTexture("menu"));
		sf::IntRect i2(8/*152*/, 266, 621/*283*/, 108);
		b.Continue.setTextureRect(i2);
		b.Continue.setPosition(pos.x + 8/*152*/, pos.y + 266);
		this->_startingState.push_back(&b.Continue);
		this->_buttonsToPoint.push_back(&b.Continue);
		this->_buttonName[&b.Continue] = buttonName::continueGame;

		b.mapeditor.setTexture(this->_data->_asset.GetTexture("menu"));
		sf::IntRect i3(8/*151*/, 394, 621/*363*/, 114);
		b.mapeditor.setTextureRect(i3);
		b.mapeditor.setPosition(pos.x + 8/*151*/, pos.y + 394);
		this->_startingState.push_back(&b.mapeditor);
		this->_buttonsToPoint.push_back(&b.mapeditor);
		this->_buttonName[&b.mapeditor] = buttonName::mapEditor;

		b.about.setTexture(this->_data->_asset.GetTexture("menu"));
		sf::IntRect i4(8 /*151*/, 530, 621/*220*/, 114);
		b.about.setTextureRect(i4);
		b.about.setPosition(pos.x + 8/*151*/, pos.y + 530);
		this->_startingState.push_back(&b.about);
		this->_buttonsToPoint.push_back(&b.about);
		this->_buttonName[&b.about] = buttonName::aboutButton;

		b.ornament2.setTexture(this->_data->_asset.GetTexture("menu"));
		sf::IntRect i5(8, 648, 621, 103);
		b.ornament2.setTextureRect(i5);
		b.ornament2.setPosition(pos.x + 8, pos.y + 648);
		//////////////////////////////////////////////////////////////////////////////////////

		b.back.setTexture(this->_data->_asset.GetTexture("back"));
		b.back.setPosition(SCREEN_WIDTH - b.back.getGlobalBounds().width - ICON_OFFSET, SCREEN_HEIGHT - b.back.getGlobalBounds().height - ICON_OFFSET);
		this->_aboutState.push_back(&b.back);
		this->_buttonName[&b.back] = buttonName::back;
		//text also done here
		aboutText.setString("The KU journey is a game made as a first sem project by students of KU. \n Hope you will enjoy it.\n Also dont forget to like subscribe and hit the bell icon.");
		aboutText.setFont(_data->_asset.GetFont("Motira"));
		aboutText.setCharacterSize(60);
		aboutText.setFillColor(sf::Color(18, 155, 153));
		aboutText.setPosition(300, 500);

		if (playSound) {
			b.sound.setTexture(this->_data->_asset.GetTexture("soundOn"));
		}
		else {
			b.sound.setTexture(this->_data->_asset.GetTexture("soundOff"));
		}
		b.sound.setPosition(SCREEN_WIDTH - b.sound.getGlobalBounds().width - ICON_OFFSET, ICON_OFFSET);
		this->_startingState.push_back(&b.sound);
		this->_aboutState.push_back(&b.sound);
		this->_buttonName[&b.sound] = buttonName::sound;


		if (isplaying) {
			b.music.setTexture(this->_data->_asset.GetTexture("musicplay"));
		}
		else {
			b.music.setTexture(this->_data->_asset.GetTexture("musicstop"));
		}
		b.music.setPosition(b.sound.getPosition().x, b.sound.getPosition().y + b.sound.getGlobalBounds().height + ICON_OFFSET + 5);
		this->_startingState.push_back(&b.music);
		this->_aboutState.push_back(&b.music);
		this->_buttonName[&b.music] = buttonName::music;
	}
	void MainMenu::setParalax()
	{
		this->bg.sky.setTexture(_data->_asset.GetTexture("parallaxSky"));
		for (int i = 0; i < 2; i++) {
			this->bg.p[i].cloud1.setTexture(_data->_asset.GetTexture("parallaxCloud1"));
			this->bg.p[i].cloud2.setTexture(_data->_asset.GetTexture("parallaxCloud2"));
			this->bg.p[i].cloud3.setTexture(_data->_asset.GetTexture("parallaxCloud3"));
			this->bg.p[i].mountain1.setTexture(_data->_asset.GetTexture("parallaxMountain1"));
			this->bg.p[i].mountain2.setTexture(_data->_asset.GetTexture("parallaxMountain2"));
			this->bg.p[i].mountain3.setTexture(_data->_asset.GetTexture("parallaxMountain3"));

			//if (i != 0) {
			this->bg.p[i].cloud1.setPosition(/*this->bg.p[i - 1].cloud1.getPosition().x*/ i * 1920, 0);
			this->bg.p[i].cloud2.setPosition(/*this->bg.p[i - 1].cloud2.getPosition().x*/  i * 1920, 0);
			this->bg.p[i].cloud3.setPosition(/*this->bg.p[i - 1].cloud3.getPosition().x */ i * 1920, 0);
			this->bg.p[i].mountain1.setPosition(/*this->bg.p[i - 1].mountain1.getPosition().x*/  i * 1920, 0);
			this->bg.p[i].mountain2.setPosition(/*this->bg.p[i - 1].mountain2.getPosition().x*/  i * 1920, 0);
			this->bg.p[i].mountain3.setPosition(/*this->bg.p[i - 1].mountain3.getPosition().x*/  i * 1920, 0);
			//}
		}
	}
	void MainMenu::drawParallax()
	{
		this->_data->_window.draw(bg.sky);
		for (int i = 0; i < 2; i++) {
			this->_data->_window.draw(bg.p[i].cloud1);
		}
		for (int i = 0; i < 2; i++) {
			this->_data->_window.draw(bg.p[i].cloud2);
		}
		for (int i = 0; i < 2; i++) {
			this->_data->_window.draw(bg.p[i].mountain1);
		}

		for (int i = 0; i < 2; i++) {
			this->_data->_window.draw(bg.p[i].mountain2);
		}
		for (int i = 0; i < 2; i++) {
			this->_data->_window.draw(bg.p[i].cloud3);
		}
		for (int i = 0; i < 2; i++) {
			this->_data->_window.draw(bg.p[i].mountain3);
		}
	}
	void MainMenu::moveparallax()
	{
		for (int i = 0; i < 2; i++) {
			bg.p[i].cloud1.move(-1.0f / 2, 0.0f);
			bg.p[i].cloud2.move(-1.5f / 2, 0.0f);
			bg.p[i].cloud3.move(-2.0f / 2, 0.0f);
			bg.p[i].mountain1.move(-1 / 2, 0);
			bg.p[i].mountain2.move(-2 / 2, 0);
			bg.p[i].mountain3.move(-3 / 2, 0);

			if (bg.p[i].cloud1.getPosition().x <= -1920) {
				bg.p[i].cloud1.setPosition(1920, 0);
			}
			if (bg.p[i].cloud2.getPosition().x <= -1920) {
				bg.p[i].cloud2.setPosition(1920, 0);
			}
			if (bg.p[i].cloud3.getPosition().x <= -1920) {
				bg.p[i].cloud3.setPosition(1920, 0);
			}
			if (bg.p[i].mountain1.getPosition().x <= -1920) {
				bg.p[i].mountain1.setPosition(1920, 0);
			}
			if (bg.p[i].mountain2.getPosition().x <= -1920) {
				bg.p[i].mountain2.setPosition(1920, 0);
			}
			if (bg.p[i].mountain3.getPosition().x <= -1920) {
				bg.p[i].mountain3.setPosition(1920, 0);
			}
		}
	}
}

