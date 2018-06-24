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
			object->draw(win);;
		}
	}
}

void Map::update()
{
	for (auto key : mapkey) {
		for (auto object : this->objects[key]) {
			object->update();
		}
	}
}

void Map::setDepth(std::vector<String> entities, int depth)
{
	for (auto entity:entities) {
		for (auto obj : objects[entity]) {
			obj->depth = depth;
		}
	}
}

void Map::showIBound()
{
	for (auto entity : objects) {
		for (auto obj : entity.second) {
			obj->showIBound();
		}
	}
}

void Map::hideIBound()
{
	for (auto entity : objects) {
		for (auto obj : entity.second) {
			obj->hideIBound();
		}
	}
}
