#include "Object.h"
#include"SFML\Graphics.hpp"
#include<iostream>
#include "DEFINITIONS.h"
using namespace sf;

Object::Object(Texture* tex, Vector2u dim, Vector2f pos)
{
	this->spiriteSetup[0] = 0;
	this->spiriteSetup[1] = 1;
	this->spiriteSetup[2] = 2;
	this->spiriteSetup[3] = 3;
	this->shift = Object::shiftMode::slow;
	this->rate = framerate::normal;
	this->state = state::still;
	this->facing = face::a;
	this->restTime = 0.4;
	this->clock = new Clock();
	this->tex = tex;
	this->dim = dim;
	this->init_pos = pos;
	objSize = tex->getSize();
	objSize.x /= dim.x;
	objSize.y /= dim.y;
	row = 0;
	col = 0;
	rect.left = objSize.x*col;
	rect.top = objSize.y*row;
	rect.width = objSize.x;
	rect.height = objSize.y;
	sprite.setTexture(*tex);
	sprite.setTextureRect(rect);
	sprite.setPosition(pos.x, pos.y);

}

Object::Object(Texture * tex, Vector2f pos)
{
	this->spiriteSetup[0] = 0;
	this->spiriteSetup[1] = 1;
	this->spiriteSetup[2] = 2;
	this->spiriteSetup[3] = 3;
	this->shift = Object::shiftMode::slow;
	this->rate = framerate::normal;
	this->state = state::still;
	this->restTime = 0.4;
	this->clock = new Clock();
	this->tex = tex;
	this->init_pos = pos;
	sprite.setTexture(*tex);
	sprite.setPosition(pos.x, pos.y);
}

Object::Object(Texture * tex, IntRect rect, Vector2f pos)
{
	this->spiriteSetup[0] = 0;
	this->spiriteSetup[1] = 1;
	this->spiriteSetup[2] = 2;
	this->spiriteSetup[3] = 3;
	this->shift = Object::shiftMode::slow;
	this->rate = framerate::normal;
	this->state = state::still;
	this->restTime = 0.4;
	this->clock = new Clock();
	this->tex = tex;
	this->init_pos = pos;
	sprite.setTexture(*tex);
	sprite.setTextureRect(rect);
	sprite.setPosition(pos.x, pos.y);
}


Object::~Object()
{
}

Object::Object()
{
}

void Object::update(RenderWindow * win)
{
	win->draw(this->sprite);
}

void Object::move(moves m)
{
}

void Object::setDim(Vector2u dim)
{
	this->dim = dim;
	objSize = tex->getSize();
	objSize.x /= dim.x;
	objSize.y /= dim.y;
	row = 0;
	col = 0;
	rect.left = objSize.x*col;
	rect.top = objSize.y*row;
	rect.width = objSize.x;
	rect.height = objSize.y;
	sprite.setTexture(*tex);
	sprite.setTextureRect(rect);
}


void Object::setManualFrameRate(int r) {
	this->rate = r;
}

void Object::setFrameRate(Object::framerate r) {
	this->rate = r;
}

void Object::setShift(int d) {
	this->shift = d;
}

void Object::setMode(Object::shiftMode m)
{
	this->shift = m;
}

void Object::setManualShift(int s)
{
	this->shift = s;
}

void Object::setRestTime(float t) {
	this->restTime = t;
}

void Object::setSpirite(int u, int d, int l, int r) {
	spiriteSetup[0] = u;
	spiriteSetup[1] = d;
	spiriteSetup[2] = l;
	spiriteSetup[3] = r;
}

void Object::setPosition(Vector2f pos)
{
	this->sprite.setPosition(pos);
}
