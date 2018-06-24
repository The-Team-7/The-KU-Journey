#pragma once
#include<iostream>
#include<sfml/Graphics.hpp>
#include"Game.h"

class Toolbar
{
public:

	struct box {
		sf::RectangleShape rect;
		bool isActive;
		std::string texture_name;
		bool isLocked;
	};

	Toolbar(sg::GameDataRef _data);
	~Toolbar();
	void init();
	void draw();
	void handleInput();
	void update();

public:
	int row;
	int col;
	sg::GameDataRef _data;
	sf::RectangleShape toolbar;
	sf::RectangleShape titleRect;
	std::vector<box*> boxes;
	sf::Vector2f toolbarSize;
	sf::Vector2f boxSize;
};

