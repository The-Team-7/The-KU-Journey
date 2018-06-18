#pragma once
#include<iostream>
#include<map>
#include<vector>
#include"StaticObject.h"
#include<SFML/Graphics.hpp>

class Map
{
public:
	Map(std::vector<std::string> mapkey, std::map<std::string, std::vector<StaticObject*>> objects);
	Map();
	~Map();
	void draw(sf::RenderWindow* win);
	std::map<std::string, std::vector<StaticObject*>> objects;
	std::vector<std::string> mapkey;
};

