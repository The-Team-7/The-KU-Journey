#pragma once
#include "State.h"
#include "Game.h"
#include <SFML/Audio.hpp>
#include<vector>
#include<string>

namespace sg {
	struct ParallaxBackground {
		sf::Sprite sky;
		struct parallax {
			sf::Sprite cloud1;
			sf::Sprite cloud2;
			sf::Sprite cloud3;
			sf::Sprite mountain1;
			sf::Sprite mountain2;
			sf::Sprite mountain3;
		}p[2];
	};
	class MainMenu : public State
	{
	private:
		enum MenuState {
			starting, about
		};
		struct Components {
			sf::Sprite newGame;
			sf::Sprite Continue;
			sf::Sprite about;
			sf::Sprite back;
			sf::Sprite mapeditor;
			sf::Sprite sound;
			sf::Sprite music;
			sf::Sprite ornament1;
			sf::Sprite ornament2;
		};
		enum buttonName {
			newGame,
			continueGame,
			aboutButton,
			back,
			music,
			sound,
			mapEditor,
		};
	public:
		MainMenu(GameDataRef data);
		~MainMenu();

		virtual void Init() override;
		virtual void HandleInput() override;
		virtual void Update(float dt) override;
		virtual void Draw(float dt) override;

	private:
		void LoadButtons();
		void setParalax();
		void drawParallax();
		void moveparallax();
	private:

		GameDataRef _data;
		//buttons
		Components b;
		//pointer
		sf::Sprite pointer[2];
		bool pointerActive;
		sf::Sprite menuRect;

		std::map<sf::Sprite*, buttonName> _buttonName;
		MenuState state;
		std::vector<sf::Sprite*>  _startingState;
		std::vector<sf::Sprite*>  _aboutState;
		std::vector<sf::Sprite*>  _buttonsToPoint;
		sf::Sprite* iconClicked;
		//about text
		sf::Text aboutText;
		std::string aboutString;
		//parallax background
		ParallaxBackground bg;
		bool mouseClicked;
		int n;
		bool SpriteClicked;

		sf::Music mainMusic;
		sf::Sound typingSound;
		sf::Sound enterSound;
		bool isplaying;
		bool playSound;

	};
}


