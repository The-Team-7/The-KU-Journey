#include "Player.h"


namespace sg {

	Player::Player(sf::Texture * tex, sf::Vector2u dim, sf::Vector2f pos):Object(tex,dim,pos)
	{
	}

	Player::~Player()
	{
	}

	void Player::update(RenderWindow * win)
	{
		
		win->draw(sprite);
		
	}

	void Player::move(moves m)
	{
		if (this->clock->getElapsedTime().asSeconds() >= 1 / (float)rate) {
			if (m == Object::moves::up) {
				sprite.move(0, -shift);
				this->animate(3);
			}
			if (m == Object::moves::down) {
				sprite.move(0, shift);
				this->animate(0);
			}
			if (m == Object::moves::left) {
				sprite.move(-shift, 0);
				this->animate(1);
			}
			if (m == Object::moves::right) {
				sprite.move(shift, 0);
				this->animate(2);
			}
			this->clock->restart();
		}
	}
	void Player::animate(int r) 
	{
		row = r;
		if (col == this->dim.x - 1) {
			col = 0;
		}
		else {
			col++;
		}
		rect.top = objSize.y*row;
		rect.left = objSize.x*col;
		sprite.setTextureRect(rect);
	}

}
