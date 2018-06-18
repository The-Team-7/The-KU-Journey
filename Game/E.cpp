#include "Enemy.h"


namespace sg {
	Enemy::Enemy(sf::Texture * tex, sf::Vector2u dim, sf::Vector2f pos, Enums::EnemyType type) :Object(tex, dim, pos)
	{
		this->type = type;
	}
	Enemy::~Enemy()
	{
	}
	void Enemy::update(RenderWindow * win)
	{
		
		win->draw(sprite);
	}
	void Enemy::move(moves m)
	{
		if (this->type == Enums::EnemyType::minions) {
			if (m == moves::left) {
				sprite.move(-shift, 0);
				animate(0);
			}
		}
	}
	void Enemy::animate(int r)
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


