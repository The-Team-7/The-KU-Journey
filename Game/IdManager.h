#pragma once
#include"State.h"
#include"Game.h"
#include"InputBox.h"

class IdManager: public sg::State
{
public:
	IdManager(sg::GameDataRef _data);
	~IdManager();

	// Inherited via State
	virtual void Init() override;
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void Draw(float dt) override;

public:
	sg::GameDataRef _data;
	InputBox idInput;
	Map map;
};

