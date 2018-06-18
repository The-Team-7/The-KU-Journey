#pragma once
#include<SFML/Graphics.hpp>
#include"Object.h"
#include "Enums.h"
#include<SFML/Audio.hpp>

namespace sg {
	class Enemy : public Object
	{
	public:
		Enemy(sf::Texture * tex, sf::Vector2u dim, sf::Vector2f pos, Enums::EnemyType type);
		//Enemy() { };
		~Enemy();

		virtual void update(RenderWindow * win) override;
		virtual void move(moves m) override;
		void animate(int r);

	private:
		Enums::EnemyType type;

	};

}