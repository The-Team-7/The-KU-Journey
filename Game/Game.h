#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<memory>
#include"State.h"
#include"StateMachine.h"
#include"AssetManager.h"
#include"InputManager.h"
#include"MapLoader.h"
#include"Settings.h"
#include<unordered_map>

namespace sg {

	///////// THIS CLASS MANAGES AND RUNS ALL THE GAME ENGINE TOOLS SPECIFICALLY STATE MACHINE /////////
	///////// IT CREATES GAME DATA STRUCT WHICH IS USED ALL OVER THE GAME /////////


	////////// GAME DATA CONTAINS ALL GAME ENGINE TOOLS WHICH IS PASSED,SHARD AND USED BY GAME STATES///////
	struct GameData {

		StateMachine _machine;
		AssetManager _asset;
		InputManager _inputManager;
		sf::RenderWindow _window;
		Settings _settings;
		MapLoader _maploader;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{

	public:

		Game(int width, int height, std::string title);
		~Game();

	private:
		GameDataRef _data = std::make_shared<GameData>();
		sf::Clock clock;

		////// THIS IS THE MAIN GAME LOOP //////
		void Run();
	};
}


