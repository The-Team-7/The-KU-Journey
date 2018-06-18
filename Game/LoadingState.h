#pragma once
#include "Game.h"
#include "State.h"
#include <iostream>
#include<thread>
#include<string>
#include <chrono> 
#include "DEFINITIONS.h"
#include "levelState.h"
namespace sg {

	class LoadingState : public State
	{
	public:

		LoadingState(GameDataRef data);
		~LoadingState();

		// Inherited via State
		virtual void Init() override;

		virtual void HandleInput() override;

		virtual void Update(float dt) override;

		virtual void Draw(float dt) override;

		void loadAssets();

	private:

		GameDataRef _data;
		sf::Sprite bg;
		sf::Clock* clock;

		sf::Text text;
		sf::Text threadTask;
		std::string load;
		std::string taskname;
		int n;

		bool threadFinished;
		std::thread _asset;
	};
}
