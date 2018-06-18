#pragma once
#pragma once
#include "State.h"
#include "Game.h"
#include "DEFINITIONS.h"
#include "Enums.h"
//#include "Player.h"
//#include "EnemyFactory.h"
#include <iostream>
#include <vector>
#include <map>
#include <vector>
#include<memory>

namespace sg {

	class LevelOne : public State
	{
	public:
		
		LevelOne(GameDataRef data);
		~LevelOne();

		// Inherited via State
		virtual void Init() override;
		virtual void HandleInput() override;
		virtual void Update(float dt) override;
		virtual void Draw(float dt) override;

	public:
		GameDataRef _data;
		sf::Sprite bg;
		
		std::map<int, bool> keys;
		//std::map<Enums::Characters, Player> _playerMap;
		//EnemyFactory* enemyFactory;
		//std::vector<Enemy> tort;
		//std::map<Enums::Characters, std::vector<Enemy>> enemyMap;
	};
}


