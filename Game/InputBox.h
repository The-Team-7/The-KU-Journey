#pragma once
#include<SFML\Graphics.hpp>
#include<string>
#include "Game.h"
class InputBox
{
public:
	InputBox();
	InputBox(sf::Vector2f pos, std::string size, std::string type,std::string labelText);
	~InputBox();

public:
	sf::RectangleShape box;
	sf::Text text;
	bool isActive;
	int textLimit;
	sf::Text Label;
	std::string type;
	sf::Font font;
	std::string inputData;

public:
	void setFont(sf::Font& font);
	void setPosition(sf::Vector2f pos);
	std::string getString();
	void update(sf::Event event,sf::RectangleShape& _mouse);
	void draw(sf::RenderWindow& win);
	void setActive();
	void setInactive();
};

