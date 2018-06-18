#pragma once
#include"State.h"
#include<sfml/Graphics.hpp>
#include"Person.h"
#include"Game.h"
#include"MapLoader.h"
#include"Collision.h"
#include"Map.h"

class IntroLevel :public sg::State
{
public:
	IntroLevel(sg::GameDataRef _data);
	~IntroLevel();

	// Inherited via State
	virtual void Init() override;
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void Draw(float dt) override;
	virtual void Pause() override;
	virtual void Resume() override;
	bool Interaction1(String entity);
	void InteractionHandler();

private:
	sg::GameDataRef _data;
	sf::Sprite backgroundSpr;
	Person player;
	sf::View view;
	float zoom = 0.6;
	int zoomIn = 0;
	int zoomOut = 0;
	Map map;
};

