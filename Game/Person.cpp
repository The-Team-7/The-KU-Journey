#include "Person.h"
#include"Object.h"
#include<iostream>
#include<Math.h>
#include<cmath>


Person::Person(Texture* tex, Vector2u dim, Vector2f pos) :Object(tex, dim, pos)
{
	this->jumping = false;
	this->trigger_jump = false;
	this->jumpClock = new Clock;
	this->onground = false;
	this->impulse = -48;
	this->ximpulse = this->impulse / 1.5;
}

Person::Person()
{
}

Person::~Person()
{
}

void Person::animateMove(int r) {
	row = r;
	if (col == this->dim.x - 1) {
		col = 1;
	}
	else {
		col++;
	}

	rect.top = objSize.y*row;
	rect.left = objSize.x*col;
	sprite.setTextureRect(rect);
}

void Person::move(moves m) {

	if (m == Object::moves::up && moveup) {
		sprite.move(0, -shift);
		animateMove(spiriteSetup[0]);
		face = up;
	}
	if (m == Object::moves::down && movedown) {
		sprite.move(0, shift);
		animateMove(spiriteSetup[1]);
		face = down;
	}
	if (m == Object::moves::left && moveleft) {
		sprite.move(-shift, 0);
		animateMove(spiriteSetup[2]);
		face = left;
	}
	if (m == Object::moves::right && moveright) {
		sprite.move(shift, 0);
		animateMove(spiriteSetup[3]);
		face = right;
	}

}

void Person::setRPGMODE()
{
	this->rpg_mode = true;
	this->onground = true;
	this->jumping = false;
}

void Person::setImpulse(int impulse)
{
	this->impulse = impulse;
}

void Person::jump() {
	if (onground && !rpg_mode) {
		trigger_jump = true;
	}
	else {
		trigger_jump = false;
	}
}


void Person::update(RenderWindow * win)
{
	int gravity = 9;
	float dist = 0;

	if (this->clock->getElapsedTime().asSeconds() >0.3) {

		dist = sqrt(pow((this->init_pos.x - sprite.getPosition().x), 2) + pow((this->init_pos.y - sprite.getPosition().y), 2));
		this->init_pos.x = sprite.getPosition().x;
		this->init_pos.y = sprite.getPosition().y;

		if (dist == 0.0f) {
			this->state = state::still;
		}
		else {
			this->state = state::moving;
		}


		clock->restart();
	}

	if (!onground || jumping) {
		if (this->jumpClock->getElapsedTime().asSeconds() > float(1 / float(rate))) {
			sprite.move(velocity.x, velocity.y);
			velocity.y = velocity.y + gravity;
			jumpClock->restart();
		}
	}

	if (onground) {
		jumping = false;
	}

	if (trigger_jump && onground) {
		jumping = true;
		if (this->state == state::still) {
			velocity.y = impulse;
			velocity.x = 0;
		}
		else {

			velocity.y = impulse;
			ximpulse = impulse / 1.5;

			if (face == right) {
				velocity.x = -ximpulse;
			}
			else if (face == left) {
				velocity.x = ximpulse;
			}
		}
		trigger_jump = false;

	}


	win->draw(sprite);
}



