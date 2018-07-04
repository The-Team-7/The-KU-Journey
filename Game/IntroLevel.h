#pragma once
#include <iostream>
#include"DEFINITIONS.h"
#include "Game.h"
#include "State.h"
#include "MainMenuState.h"
#include<sfml/Graphics.hpp>
#include"Conversation.h"
#include "Person.h"
#include "Player.h"
class IntroLevel : public sg::State
{
public:
	IntroLevel(sg::GameDataRef data);
	virtual void Init() override;
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void Draw(float dt) override;

private:
	sf::Sprite go;
	sg::GameDataRef _data;
	Map map;
	sg::Conversation* convo;
	sf::Sprite bg;
	sf::Clock* transitClock;
	int opacity;
	sf::RectangleShape transit;
	Player p;
};
