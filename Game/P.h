#pragma once
#include "Object.h"

namespace sg {
	class Player : public Object
	{
	public:
		Player(sf::Texture* tex, sf::Vector2u dim, sf::Vector2f pos);
		Player() { };
		~Player();
		
	

		virtual void update(RenderWindow * win) override;
		virtual void move(moves m) override;
		void animate(int r);
	
	};
}

