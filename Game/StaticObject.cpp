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
}


StaticObject::StaticObject(Texture * tex, IntRect rect, Vector2f pos) : Object(tex, rect, pos)
{
}

void StaticObject::update()
{
	updateIBound();
}

void StaticObject::move(moves m)
{

}

void StaticObject::updateIBound()
{
	float xpos = sprite.getPosition().x + IRect.left;
	float ypos = sprite.getPosition().y + IRect.top;
	float width = IRect.width;
	float height = IRect.height;
	IBound.setPosition(xpos,ypos);
	IBound.setSize(Vector2f(width,height));
}

void StaticObject::showIBound()
{
	shouldShowIBound = true;
}

void StaticObject::hideIBound()
{
	shouldShowIBound = false;
}

void StaticObject::draw(RenderWindow * win)
{
	win->draw(this->sprite);
	if (shouldShowIBound) {
		win->draw(IBound);
	}
}
