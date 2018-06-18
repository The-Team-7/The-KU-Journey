#include "EnemyFactory.h"
#include<iostream>

namespace sg {
	EnemyFactory::EnemyFactory(GameDataRef data):_data(data)
	{
		
		this->loadTextures();
		
	}


	EnemyFactory::~EnemyFactory()
	{
	}
	Enemy* EnemyFactory::makeEnemy(Enums::EnemyType type, sf::Vector2f pos)
	{
		Enemy* enemy;
		if (type == Enums::EnemyType::minions) {
			enemy = new Enemy(this->_data->_asset.getTexturePointer("tort"), sf::Vector2u(9, 4), pos, type);
			return enemy;
		}
		else {
			return NULL;
		}
	}
	void EnemyFactory::loadTextures()
	{
		this->_data->_asset.LoadTexture("tort", ENEMY_1_TORT);
	}
}

