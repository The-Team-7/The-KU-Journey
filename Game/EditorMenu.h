#pragma once
#include"State.h"
#include"Game.h"
#include"DEFINITIONS.h"
#include"MapEditor.h"
#include"MainMenu.h"

class EditorMenu :public sg::State
{
public:
	EditorMenu(sg::GameDataRef _data);
	~EditorMenu();

	// Inherited via State
	virtual void Init() override;
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void Draw(float dt) override;
	virtual void Pause() override;
	virtual void Resume() override;
private:
	sg::GameDataRef _data;
	sf::RectangleShape mouseRect;
	sf::Sprite button_create;
	sf::Sprite button_load;
	sf::Sprite bg;

private:
	void buttonPressedhandler();
};

