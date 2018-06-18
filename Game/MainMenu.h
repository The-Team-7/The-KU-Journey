#pragma once
#include "State.h"
#include "Game.h"
#include "Weapon.h"
#include <SFML/Audio.hpp>

namespace sg {
	class MainMenu : public State
	{
	public:
		enum Menu {
			mainMenu, resumeMenu
		};
		enum MenuIcon {
			newGame,
			Continue,
			controlls,
			about,
			sound,
			music,
			back,
			description,
			mapeditor
		};
		MainMenu(GameDataRef data, Menu type);
		~MainMenu();

		virtual void Init() override;
		virtual void HandleInput() override;
		virtual void Update(float dt) override;
		virtual void Draw(float dt) override;

		void FillIcons();
	private:
		Weapon* plasmaGun;
		sf::Clock* clock;
		GameDataRef _data;
		Menu type;
		sf::Sprite bg;
		//sf::Sprite logo;
		bool mouseClicked;
		int n;

		MenuIcon iconClicked;
		bool SpriteClicked;
		std::map<MenuIcon, sf::Sprite> _icons;

		sf::Music mainMusic;
		sf::Sound typingSound;
		sf::Sound enterSound;
		bool isplaying;
		bool playSound;


		////////////////////////
	};
}


