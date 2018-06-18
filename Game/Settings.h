#pragma once
#include<iostream>
#include<map>
#include<SFML/Graphics.hpp>


class Settings
{

public:
	Settings();
	void SetViewToNormal(sf::RenderWindow & win);
	sf::Vector2f GetMousePosition(sf::RenderWindow & win);
	void Update(sf::RenderWindow & _window);

public:
	std::map<std::string, std::string> MapTextureInfo;
	sf::RectangleShape _mouse;

private:
	sf::View view;

	
};

