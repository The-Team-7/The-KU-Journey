#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "State.h"
#include "Game.h"
#include"EditorMenu.h"
#include "Settings.h"

namespace sg {
	class MainMenuState :public State
	{
	public:
		MainMenuState(GameDataRef data);
		~MainMenuState();
		enum Sprite {
			play, option, exitgame
		};
		enum menuState {
			main_menu_state, option_state, sound_state

		};


		struct Background {
			sf::Sprite sky;
			sf::Sprite clouds_1;
			sf::Sprite clouds_2;
			sf::Sprite clouds_3;
			sf::Sprite mountain_1;
			sf::Sprite mountain_2;
		};

		// Inherited via state
		virtual void Init() override;
		virtual void HandleInput() override;
		virtual void Update(float dt) override;
		virtual void Draw(float dt) override;
		virtual void Pause() override;
		virtual void Resume() override;

		//void animateMenu();
		void keyChecker();
		void bg_moveLeft();
		void bg_moveRight();
		void Draghandler();

	private:

		GameDataRef _data;
		sf::RectangleShape mouseRect;
		sf::RectangleShape KeyboardRect;
		sf::Sprite bg;
		sf::Sprite music_status;
		sf::Music music;
		Settings _settings;
		Sprite selected_sprite;
		sf::Vector2i sprite_pos;
		menuState _mstate;



		sf::Sprite* buttons[8] = { &exit_game,&new_game,&options,&controls,&instructions,&sounds,&map, &credits };
		sf::SoundBuffer click_sound;
		sf::Sound sound_play;

		sf::Sprite new_game;
		sf::Sprite options;
		sf::Sprite exit_game;
		sf::Sprite controls;
		sf::Sprite instructions;
		sf::Sprite credits;
		sf::Sprite sounds;
		sf::Sprite map;
		bool isPlaying;


		//int row=0;
		//int col = 0;
		sf::Vector2u *dim;
		int height;
		int width;

		//sf::Sprite background_menu;
		sf::IntRect rect;
		sf::Vector2u dimensions;
		sf::Clock clock;

		Background _bg[3];
		sf::Sprite logo;

		//options state assets
		bool check_sound;
		sf::Sprite sound_panel;

		sf::Text Sound_text;
		sf::Text Sound_status;

		bool isDragging;
		bool isMouseClicked;
		bool is_selected;

	};

}
