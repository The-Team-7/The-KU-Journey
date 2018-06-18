#pragma once
#include"Game.h"
#include"State.h"
#include"DEFINITIONS.h"

#include<string>
#include<iostream>

namespace sg{
	class levelState : public State
{
public:
	levelState(GameDataRef data);
	~levelState();

	// Inherited via State
	virtual void Init() override;
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void Draw(float dt) override;

private:
	GameDataRef _data;
	sf::Sprite bg;

	
	
	};
}

