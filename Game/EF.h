#pragma once
#include "Game.h"
#include "Enemy.h"
#include "Enums.h"
#include "DEFINITIONS.h"
namespace sg{
	class EnemyFactory 
	{
	public:
		EnemyFactory(GameDataRef data);
		~EnemyFactory();
		
		Enemy* makeEnemy(Enums::EnemyType type, sf::Vector2f pos);

	private:
		void loadTextures();
	private:		
		GameDataRef _data;
	};

}

