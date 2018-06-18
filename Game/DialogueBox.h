#pragma once
#include"Game.h"
#include"State.h"
#include"StateMachine.h"
#include"SFML/Graphics.hpp"

class DialogueBox :public sg::State
{
public:

	enum Type {
		create, load
	};

	DialogueBox(sg::GameDataRef _data, DialogueBox::Type type);
	~DialogueBox();



private:
	// Inherited via State
	virtual void Init() override;

	virtual void HandleInput() override;

	virtual void Update(float dt) override;

	virtual void Draw(float dt) override;

	virtual void Pause() override;

	virtual void Resume() override;

	void showInfo();


private:
	Type type;
	sf::RectangleShape mouseRect;
	sg::GameDataRef _data;
	sf::Sprite background;
	sf::Sprite dialogueBox;
	sf::Sprite button;
	sf::RectangleShape filenameTextBox;
	sf::Text filenameLabel;
	bool isTextActive;
	int textLimit;
	std::string filenameText;
	sf::Text displayText;
	sf::Text InfoText;
	bool triggerInfo;
	sf::Clock clock;

private:
	void keyboardInputHandler(sf::Event* evnt);


};

