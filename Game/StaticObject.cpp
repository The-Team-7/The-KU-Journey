#include "StaticObject.h"



StaticObject::StaticObject(Texture * tex, Vector2f pos) :Object(tex, pos)
{
}

StaticObject::StaticObject(Texture * tex, Vector2f pos, std::string type_name) : Object(tex, pos)
{
	this->type = type_name;
}

StaticObject::StaticObject(Texture * tex, IntRect rect, Vector2f pos) : Object(tex, rect, pos)
{
}

void StaticObject::update(RenderWindow * win)
{
	win->draw(this->sprite);
}

void StaticObject::move(moves m)
{
}