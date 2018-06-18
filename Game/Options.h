#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"Game.h"

class Options
{

public:
	Options(sg::GameDataRef _data);
	~Options();
	void update();
	void draw();
	void setPosition(sf::Vector2f pos);
public:
	std::map <std::string, sf::RectangleShape*> rect;
	std::vector<sf::Text *> text;
	sg::GameDataRef _data;
	sf::Vector2f pos = *new sf::Vector2f(0, 0);
	sf::Vector2f size;

};

