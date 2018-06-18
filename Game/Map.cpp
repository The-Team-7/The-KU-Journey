#include "Map.h"

Map::Map(std::vector<std::string> mapkey, std::map<std::string, std::vector<StaticObject*>> objects)
{
	this->mapkey = mapkey;
	this->objects = objects;
}

Map::Map()
{
}

Map::~Map()
{
}

void Map::draw(sf::RenderWindow* win)
{
	for (auto key : mapkey) {
		for (auto object : this->objects[key]) {
			win->draw(object->sprite);
		}
	}
}
