#include "MainMenuState.h"
#include <iostream>
#include "DEFINITIONS.h"
#include"SplashState.h"
#include"IntroLevel.h"



namespace sg {

	MainMenuState::MainMenuState(GameDataRef data)
	{
		this->_data = data;
		this->dim = new sf::Vector2u(0, 0);
		this->_mstate = menuState::main_menu_state;
		this->check_sound = false;
		this->isPlaying = isPlaying;
		this->isDragging = false;
		this->isMouseClicked = false;


	}


	MainMenuState::~MainMenuState()
	{
	}

	void sg::MainMenuState::Init()
	{

		this->_data->_settings.SetViewToNormal(this->_data->_window);
		mouseRect.setSize(sf::Vector2f(5, 5));
		mouseRect.setFillColor(sf::Color::Transparent);

		KeyboardRect.setSize(sf::Vector2f(5, 5));
		KeyboardRect.setFillColor(sf::Color::Transparent);

		this->_data->_asset.LoadTexture("logo", LOGO);
		this->_data->_asset.LoadTexture("sky", SKY);
		this->_data->_asset.LoadTexture("clouds_1", CLOUDS1);
		this->_data->_asset.LoadTexture("clouds_2", CLOUDS2);
		this->_data->_asset.LoadTexture("clouds_3", CLOUDS3);
		this->_data->_asset.LoadTexture("mountain_1", ROCKS1);
		this->_data->_asset.LoadTexture("mountain_2", ROCKS2);



		this->_data->_asset.LoadTexture("Main_Menu_State_new_game", BUTTONS_NEW);
		new_game.setTexture(this->_data->_asset.GetTexture("Main_Menu_State_new_game"));
		new_game.setPosition(860, 500);

		//default position for selector
		KeyboardRect.setPosition(860, 400);


		this->_data->_asset.LoadTexture("Main_Menu_State_options", BUTTONS_OPTIONS);
		options.setTexture(this->_data->_asset.GetTexture("Main_Menu_State_options"));
		options.setPosition(855, new_game.getPosition().y + 100);


		this->_data->_asset.LoadTexture("Main_Menu_State_exit_game", BUTTONS_EXIT);
		exit_game.setTexture(this->_data->_asset.GetTexture("Main_Menu_State_exit_game"));
		exit_game.setPosition(855, options.getPosition().y + 100);


		if (music.openFromFile(CREDIT_MUSIC)) {
			std::cout << "playing..";
			music.play();
			music.setLoop(true);
			isPlaying = true;

		}
		else {
			std::cout << "failed to load";
		}
		//sound

		///////////////////////////////////////////animation////////////////////////////////////////////////
		logo.setTexture(_data->_asset.GetTexture("logo"));
		logo.setPosition(0, 0);
		for (int i = 0; i < 3; i++) {
			this->_bg[i].sky.setTexture(_data->_asset.GetTexture("sky"));
			this->_bg[i].clouds_1.setTexture(_data->_asset.GetTexture("clouds_1"));
			this->_bg[i].clouds_2.setTexture(_data->_asset.GetTexture("clouds_2"));
			this->_bg[i].mountain_1.setTexture(_data->_asset.GetTexture("mountain_1"));
			this->_bg[i].clouds_3.setTexture(_data->_asset.GetTexture("clouds_3"));
			this->_bg[i].mountain_2.setTexture(_data->_asset.GetTexture("mountain_2"));
			if (i != 0) {
				this->_bg[i].sky.setPosition(this->_bg[i].sky.getGlobalBounds().width, 0);
				this->_bg[i].clouds_1.setPosition(this->_bg[i].clouds_1.getGlobalBounds().width, 0);
				this->_bg[i].clouds_3.setPosition(this->_bg[i].clouds_3.getGlobalBounds().width, 0);

				this->_bg[i].clouds_2.setPosition(this->_bg[i].clouds_2.getGlobalBounds().width, 0);
				this->_bg[i].mountain_1.setPosition(this->_bg[i].mountain_1.getGlobalBounds().width, 0);
				this->_bg[i].mountain_2.setPosition(this->_bg[i].mountain_2.getGlobalBounds().width, 0);
			}
		}
		///////////////////////////////////////////end_of_animation/////////////////////////////////////////
		//optionstate assets//////////////////////
		this->_data->_asset.LoadTexture("Buttons_controls", BUTTONS_CONTROLS);

		controls.setTexture(this->_data->_asset.GetTexture("Buttons_controls"));
		controls.setPosition(830, 400);


		this->_data->_asset.LoadTexture("Buttons_sound", BUTTONS_SOUND);

		sounds.setTexture(this->_data->_asset.GetTexture("Buttons_sound"));
		sounds.setPosition(830, this->controls.getPosition().y + 100);

		this->_data->_asset.LoadTexture("Buttons_instructions", BUTTONS_INSTRUCTIONS);
		instructions.setTexture(this->_data->_asset.GetTexture("Buttons_instructions"));
		instructions.setPosition(830, this->sounds.getPosition().y + 100);

		this->_data->_asset.LoadTexture("Buttons_credits", BUTTONS_CREDITS);
		credits.setTexture(this->_data->_asset.GetTexture("Buttons_credits"));
		credits.setPosition(830, this->instructions.getPosition().y + 100);

		this->_data->_asset.LoadTexture("Buttons_map", BUTTONS_MAP);
		map.setTexture(this->_data->_asset.GetTexture("Buttons_map"));
		map.setPosition(830, this->credits.getPosition().y + 100);

		this->_data->_asset.LoadTexture("Sound_panel", SOUND_TEXTURE);
		this->_data->_asset.LoadFont("Sound_font", FONT);
		this->sound_panel.setTexture(this->_data->_asset.GetTexture("Sound_panel"));
		this->Sound_text.setFont(this->_data->_asset.GetFont("Sound_font"));
		this->Sound_text.setString("SOUND MENU");
		this->Sound_status.setFont(this->_data->_asset.GetFont("Sound_font"));
		this->Sound_status.setString("SOUND STATUS:");
		Sound_text.setCharacterSize(25);
		Sound_status.setCharacterSize(15);
		Sound_status.setFillColor(sf::Color::Red);
		Sound_status.setStyle(sf::Text::Bold);
		Sound_text.setStyle(sf::Text::Bold);
		Sound_text.setFillColor(sf::Color::Black);
		sound_panel.setPosition(1920 / 2, 1080 / 2);
		Sound_text.setPosition(sound_panel.getPosition().x + 25, sound_panel.getPosition().y + 15);
		Sound_status.setPosition(sound_panel.getPosition().x + 25, sound_panel.getPosition().y + 95);


		this->_data->_asset.LoadTexture("Music_On", MAIN_MENU_MUSIC_ON);
		this->_data->_asset.LoadTexture("Music_Off", MAIN_MENU_MUSIC_OFF);

		music_status.setTexture(this->_data->_asset.GetTexture("Music_On"));
		music_status.setPosition(sound_panel.getPosition().x + 185, sound_panel.getPosition().y + 90);


		////////end of option assets/////////////

	}

	void sg::MainMenuState::HandleInput()
	{
		sf::Event event;
		while (this->_data->_window.pollEvent(event)) {
			//////////////////////////////////option_state input handler////////////////////////////////
			if (this->_mstate == menuState::option_state) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape) {
						this->_mstate = menuState::main_menu_state;

					}
				}


				if (event.type == sf::Event::MouseMoved) {

					for (auto button : buttons) {

						if (button->getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
							button->setColor(sf::Color::Magenta);
							KeyboardRect.setPosition(button->getPosition().x, button->getPosition().y);

						}
						else {
							button->setColor(sf::Color::White);

						}

					}

				}
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {



							if (buttons[5]->getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
								this->_mstate = menuState::sound_state;

							}

							if (buttons[6]->getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
								music.stop();
								this->_data->_machine.AddState(sg::StateRef(new EditorMenu(this->_data)), true);
							}

						for (auto button : buttons) {

							if (button->getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {

								if (click_sound.loadFromFile(BUTTON_CLICK)) {
									sound_play.setBuffer(click_sound);
									std::cout << "loaded";
									this->sound_play.play();

								}
							}
							else {
								button->setColor(sf::Color::White);
							}
						}
					}

				}


			}
			//////////////////////////////////end_of_option_state///////////////////////////////////////
			if (this->_mstate == menuState::main_menu_state ) {
				if (event.type == sf::Event::Closed) {
					this->_data->_window.close();


				}


				if (event.type == sf::Event::MouseMoved) {

					for (auto button : buttons) {

						if (button->getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
							button->setColor(sf::Color::Magenta);
							KeyboardRect.setPosition(button->getPosition().x, button->getPosition().y);

						}
						else {
							button->setColor(sf::Color::White);

						}

					}

				}

				if (event.type == sf::Event::KeyPressed) {

			

					if (event.key.code == sf::Keyboard::Down) {

						KeyboardRect.setPosition(KeyboardRect.getPosition().x, KeyboardRect.getPosition().y + 100);
						keyChecker();

					}
					if (event.key.code == sf::Keyboard::Up) {

						KeyboardRect.setPosition(KeyboardRect.getPosition().x, KeyboardRect.getPosition().y - 100);
						keyChecker();
					}


					if (this->selected_sprite == Sprite::exitgame &&event.key.code == sf::Keyboard::Down) {
						KeyboardRect.setPosition(this->new_game.getPosition().x, this->new_game.getPosition().y);
						keyChecker();

					}
					if (this->selected_sprite == Sprite::play && event.key.code == sf::Keyboard::Up) {

						KeyboardRect.setPosition(this->new_game.getPosition().x, this->new_game.getPosition().y);
						keyChecker();
					}


					if (event.key.code == sf::Keyboard::Return) {
						if (this->selected_sprite == Sprite::option) {

							if (click_sound.loadFromFile(BUTTON_CLICK)) {
								sound_play.setBuffer(click_sound);
								this->sound_play.play();

							}
							this->_mstate = menuState::option_state;

						}
						if (this->selected_sprite == Sprite::exitgame) {
							if (click_sound.loadFromFile(BUTTON_CLICK)) {
								sound_play.setBuffer(click_sound);
								this->sound_play.play();

							}
							this->_data->_window.close();

						}

					}

				}
				///
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {

						if (buttons[0]->getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
							this->_data->_window.close();

						}
						if (buttons[2]->getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
							this->_mstate = menuState::option_state;
						}

						if (buttons[1]->getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
							music.stop();
							this->_data->_machine.AddState(sg::StateRef(new IntroLevel(this->_data)),true);
						}
						/*if (this->_mstate == menuState::option_state) {

							if (buttons[5]->getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
								this->_mstate = menuState::sound_state;

							}

							if (buttons[6]->getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
								music.stop();
								this->_data->_machine.AddState(sg::StateRef(new EditorMenu(this->_data)),true);
							}
						}*/

						for (auto button : buttons) {

							if (button->getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {

								if (click_sound.loadFromFile(BUTTON_CLICK)) {
									sound_play.setBuffer(click_sound);
									std::cout << "loaded";
									this->sound_play.play();

								}
							}
							else {
								button->setColor(sf::Color::White);
							}
						}
					}

				}
			}
	
			/////sound_panel///////////////////////////////////////////
			if (this->_mstate == menuState::sound_state) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape) {
						this->_mstate = menuState::option_state;
						sound_panel.setPosition(860, 600);
						this->Sound_text.setPosition(sound_panel.getPosition().x + 25, sound_panel.getPosition().y + 15);
						this->Sound_status.setPosition(sound_panel.getPosition().x + 25, sound_panel.getPosition().y + 95);
						music_status.setPosition(sound_panel.getPosition().x + 185, sound_panel.getPosition().y + 90);
					}
				}

				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						this->isMouseClicked = true;
						if (this->sound_panel.getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
							this->is_selected = true;
						}
						else {
							this->is_selected = false;
						}

						if (this->music_status.getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {

							if (isPlaying) {
								this->music.pause();
								isPlaying = false;
								music_status.setTexture(this->_data->_asset.GetTexture("Music_Off"));

							}
							else {

								this->music.play();
								isPlaying = true;
								music_status.setTexture(this->_data->_asset.GetTexture("Music_On"));
							}
						}

					}

				}

				if (event.type == sf::Event::MouseButtonReleased) {
					isMouseClicked = false;

				}



				if (event.type == sf::Event::MouseMoved) {
					if (isMouseClicked && is_selected) {
						this->isDragging = true;
					}
				}

			}
			///////////////end of sound-panel//////////////////////


		}
	}


	void sg::MainMenuState::Update(float dt)
	{

		mouseRect.setPosition(_settings.GetMousePosition(this->_data->_window));

		//animateMenu();
		if (isDragging) {
			Draghandler();
			isDragging = false;
		}

		this->bg_moveLeft();
		this->bg_moveRight();

		this->sprite_pos.y = KeyboardRect.getPosition().y;

		if (this->sprite_pos.y == 515 || this->sprite_pos.y == 500) {
			this->selected_sprite = Sprite::play;
		}
		if (this->sprite_pos.y == 615 || this->sprite_pos.y == 600) {
			this->selected_sprite = Sprite::option;
		}
		if (this->sprite_pos.y == 715 || this->sprite_pos.y == 700) {
			this->selected_sprite = Sprite::exitgame;
		}
	}


	void sg::MainMenuState::Draw(float dt)
	{
		this->_data->_window.clear();
		//this->_data->window.draw(this->background_menu);
		for (int i = 0; i < 3; i++) {
			this->_data->_window.draw(_bg[i].sky);
		}
		for (int i = 0; i < 3; i++) {
			this->_data->_window.draw(_bg[i].clouds_1);
			this->_data->_window.draw(_bg[i].clouds_2);
		}
		for (int i = 0; i < 3; i++) {
			this->_data->_window.draw(_bg[i].mountain_1);
		}
		for (int i = 0; i < 3; i++) {
			this->_data->_window.draw(_bg[i].clouds_3);
			this->_data->_window.draw(_bg[i].mountain_2);
		}
		this->_data->_window.draw(logo);
		if (this->_mstate == menuState::main_menu_state) {
			this->_data->_window.draw(this->new_game);
			this->_data->_window.draw(this->options);
			this->_data->_window.draw(this->exit_game);
		}

		if (this->_mstate == menuState::option_state) {


			this->_data->_window.draw(this->controls);
			this->_data->_window.draw(this->sounds);
			this->_data->_window.draw(this->instructions);
			this->_data->_window.draw(this->credits);
			this->_data->_window.draw(this->map);

		}


		if (this->_mstate == menuState::sound_state) {

			this->_data->_window.draw(this->sound_panel);
			this->_data->_window.draw(this->Sound_text);
			this->_data->_window.draw(this->Sound_status);
			this->_data->_window.draw(this->music_status);


		}
		this->_data->_window.draw(mouseRect);
		this->_data->_window.draw(KeyboardRect);
		this->_data->_window.display();
	}

	void sg::MainMenuState::Pause()
	{

	}

	void sg::MainMenuState::Resume()
	{
	}



	void MainMenuState::keyChecker()
	{
		for (auto button : buttons) {

			if (button->getGlobalBounds().intersects(KeyboardRect.getGlobalBounds())) {
				button->setColor(sf::Color::Magenta);

			}
			else {
				button->setColor(sf::Color::White);
			}
		}
	}

	void MainMenuState::bg_moveLeft()
	{
		for (int i = 0; i < 3; i++) {
			this->_bg[i].clouds_2.move(-2, 0);
			this->_bg[i].mountain_1.move(-1, 0);
			this->_bg[i].mountain_2.move(-2, 0);

			if (this->_bg[i].clouds_2.getPosition().x <= -1920) {
				int a = (i + 2) % 3;
				this->_bg[i].clouds_2.setPosition(this->_bg[a].clouds_2.getPosition().x + this->_bg[a].clouds_2.getGlobalBounds().width - 1, 0);
			}
			if (this->_bg[i].mountain_1.getPosition().x <= -1920) {
				int a = (i + 2) % 3;
				this->_bg[i].mountain_1.setPosition(this->_bg[a].mountain_1.getPosition().x + this->_bg[a].mountain_1.getGlobalBounds().width - 1, 0);
			}
			if (this->_bg[i].mountain_2.getPosition().x <= -1920) {
				int a = (i + 2) % 3;
				this->_bg[i].mountain_2.setPosition(this->_bg[a].mountain_2.getPosition().x + this->_bg[a].mountain_2.getGlobalBounds().width - 2, 0);
			}
		}
	}

	void MainMenuState::bg_moveRight()
	{
		for (int i = 0; i < 3; i++) {

			this->_bg[i].clouds_1.move(1, 0);
			this->_bg[i].clouds_3.move(2, 0);
			if (this->_bg[i].clouds_1.getPosition().x >= 1920 * 2) {
				int a = (i + 2) % 3;
				this->_bg[i].clouds_1.setPosition(this->_bg[a].clouds_1.getPosition().x + this->_bg[a].clouds_1.getGlobalBounds().width - 1, 0);
			}

			if (this->_bg[i].clouds_3.getPosition().x >= 1920 * 2) {
				int a = (i + 2) % 3;
				this->_bg[i].clouds_3.setPosition(this->_bg[a].clouds_3.getPosition().x + this->_bg[a].clouds_3.getGlobalBounds().width - 1, 0);
			}

		}
	}

	void MainMenuState::Draghandler()
	{
		this->sound_panel.setPosition(this->_settings.GetMousePosition(this->_data->_window));
		this->Sound_text.setPosition(sound_panel.getPosition().x + 25, sound_panel.getPosition().y + 15);
		this->Sound_status.setPosition(sound_panel.getPosition().x + 25, sound_panel.getPosition().y + 95);
		music_status.setPosition(sound_panel.getPosition().x + 185, sound_panel.getPosition().y + 90);
	}




}
