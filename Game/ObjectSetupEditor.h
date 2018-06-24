#pragma once
#include"State.h"
#include"InputBox.h"
#include"Game.h"
#include"Map.h"

class InterSectionBound {
public:
	RectangleShape rect;
	Vector2f center;
	float height;
	float width;
	bool isActive=false;
	Vector2f maxSize;
	float shift=5;

	InterSectionBound(sf::Vector2f pos) {
		//rect.setFillColor(sf::Color::Cyan);
		rect.setSize(Vector2f(100, 100));
		rect.setPosition(pos);
		rect.setOutlineColor(sf::Color::Blue);
		rect.setOutlineThickness(6);
	}
	InterSectionBound() {
	
	}

	void setPosition(sf::Vector2f pos) {
		rect.setPosition(pos);
	}
	void update() {
		if (isActive) {
			rect.setOutlineColor(sf::Color::Red);
			rect.setFillColor(sf::Color::White);
		}
		else {
			rect.setOutlineColor(sf::Color::Blue);
			rect.setFillColor(sf::Color::Transparent);
		}
	}

	void resize(std::string type) {
		
		if (type == "downGrow") {
			rect.setSize(sf::Vector2f(rect.getSize().x, rect.getSize().y + shift));
		}
		if (type == "rightGrow") {
			rect.setSize(sf::Vector2f(rect.getSize().x +shift, rect.getSize().y));
		}
		if (type == "upGrow") {
			rect.setSize(sf::Vector2f(rect.getSize().x, rect.getSize().y +shift ));
			rect.move(0, -shift);
		}
		if (type == "leftGrow") {
			rect.setSize(sf::Vector2f(rect.getSize().x + shift, rect.getSize().y));
			rect.move(-shift, 0);
		}
	

		if (rect.getSize().x >10) {
			if (type == "rightShrink") {
				rect.setSize(sf::Vector2f(rect.getSize().x - shift, rect.getSize().y));
				rect.move(shift, 0);
			}		
			if (type == "leftShrink") {
				rect.setSize(sf::Vector2f(rect.getSize().x - shift, rect.getSize().y));
			}
		}
		if (rect.getSize().y > 10) {
			if (type == "upShrink") {
				rect.setSize(sf::Vector2f(rect.getSize().x, rect.getSize().y - shift));
			}
			if (type == "downShrink") {
				rect.setSize(sf::Vector2f(rect.getSize().x, rect.getSize().y - shift));
				rect.move(0, shift);
			}
		}
	}

	void move(std::string type) {

		if (type == "down") {
			rect.move(0, shift);
		}
		if (type == "right") {
			rect.move(shift,0);
		}
		if (type == "up") {
			rect.move(0, -shift);
		}
		if (type == "left") {
			rect.move(-shift, 0);
		}
	}

	void setMaxSize(Vector2f size) {
		this->maxSize = size;
	}


};

class ObjectSetupEditor: public sg::State
{
public:
	ObjectSetupEditor(sg::GameDataRef& _data,std::map<std::string, std::pair<int, sf::FloatRect>>* objectSettings, std::string entity);
	~ObjectSetupEditor();

	// Inherited via State
	virtual void Init() override;
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void Draw(float dt) override;
	bool checkBound(std::string type);
	void updateData();
	void loadData();

public:

	std::map<std::string, std::pair<int, sf::FloatRect>>* objectSettings;
	std::string entity;
	sf::Texture tex;
	Map map;
	bool isSaveButtonActive;
	bool isAltPressed;
	float shift;
	sf::Vector2f scale;
	RectangleShape body;
	InterSectionBound i1;
	InputBox input1;
	InputBox input2;
	InputBox input3;
	InputBox scalex;
	InputBox scaley;
	InputBox xValue;
	InputBox yValue;
	InputBox rectheightValue;
	InputBox rectwidthValue;
	InputBox texheightValue;
	InputBox texwidthValue;
	sg::GameDataRef _data;
	float xpos=0, ypos=0, rectH=0, rectW=0, texH=0, texW=0;
	FloatRect intersectionRect;
	int depth;

};

