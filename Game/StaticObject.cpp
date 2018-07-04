#include "StaticObject.h"
#include<iostream>



StaticObject::StaticObject(Texture * tex, Vector2f pos) :Object(tex, pos)
{
}

StaticObject::StaticObject(Texture * tex, Vector2f pos, std::string type_name) : Object(tex, pos)
{
	this->type = type_name;
	this->IRect = FloatRect(0,0,0,0);
	this->IBound.setFillColor(sf::Color::Cyan);
	this->IBound.setSize(sf::Vector2f(IRect.width,IRect.height));
	this->Collider.setSize(sf::Vector2f(this->sprite.getGlobalBounds().width+20, this->sprite.getGlobalBounds().height+20));
	this->Collider.setOrigin(Vector2f(Collider.getSize().x/2,Collider.getSize().y/2));
	this->Collider.setPosition((this->sprite.getPosition().x+ this->sprite.getGlobalBounds().width/2), (this->sprite.getPosition().y+ this->sprite.getGlobalBounds().height/ 2));
	this->Collider.setFillColor(sf::Color::Blue);

}


StaticObject::StaticObject(Texture * tex, IntRect rect, Vector2f pos) : Object(tex, rect, pos)
{
}

void StaticObject::update()
{
	updateBounds();
}

void StaticObject::move(moves m)
{

}

void StaticObject::updateBounds()
{
	float xpos = sprite.getPosition().x + IRect.left;
	float ypos = sprite.getPosition().y + IRect.top;
	float width = IRect.width;
	float height = IRect.height;
	IBound.setPosition(xpos, ypos);
	IBound.setSize(Vector2f(width, height));
	Collider.setPosition((this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2), (this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2));
}



void StaticObject::showIBound()
{
	shouldShowIBound = true;
}

void StaticObject::hideIBound()
{
	shouldShowIBound = false;
}

void StaticObject::showCollider()
{
	shouldShowCollider = true;
}

void StaticObject::hideCollider()
{
	shouldShowCollider = false;
}

void StaticObject::draw(RenderWindow * win)
{
	if (shouldShowIBound) {
		win->draw(IBound);
	}
	if (shouldShowCollider) {
		win->draw(Collider);
	}
	win->draw(this->sprite);
	
}