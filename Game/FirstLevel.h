#pragma once
#include"State.h"
#include "Game.h"
#include "MapLoader.h"
#include "Map.h"
#include "Person.h"
#include "Player.h"
#include <unordered_map>

class FirstLevel: public sg::State
{
public:
	FirstLevel(sg::GameDataRef _data);
	~FirstLevel();

	// Inherited via State
	virtual void Init() override;
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void Draw(float dt) override;
	void InteractionHandler();
	bool blockInteraction(std::vector<std::string> entities);
	void settingUpBlockIrect();
	bool shouldObjectsFall(std::vector<std::string> entities);


public:
	sg::GameDataRef _data;
	Map map;
	std::unordered_map<int, bool> _input;
	sg::MapLoader mapLoader;
	Player player;

};

