#include "Options.h"


Options::Options(sg::GameDataRef _data)
{
	this->_data = _data;

	this->size.x = 290;
	this->size.y = 50;
	std::vector<std::string> optionsName = { "lock","unlock","swap back","swap forward","settings"};

	for (auto name : optionsName) {
		this->rect[name] = new sf::RectangleShape;
		this->text.push_back(new sf::Text);
	}

	int i = 0;

	for (auto obj : rect) {
		obj.second->setFillColor(sf::Color::Cyan);
		obj.second->setOutlineThickness(3);
		obj.second->setOutlineColor(sf::Color::Black);
		obj.second->setSize(size);
		text[i]->setFont(this->_data->_asset.GetFont("font1"));
		text[i]->setString(obj.first);
		text[i]->setCharacterSize(35);
		text[i]->setFillColor(sf::Color::Red);
		i++;
	}
}


Options::~Options()
{
}

void Options::update()
{
	int x = pos.x;
	int y = pos.y;
	int i = 0;
	for (auto obj : rect) {
		obj.second->setPosition(sf:: Vector2f(x, y));
		text[i]->setPosition(sf::Vector2f(x + 15, y + 4));
		i++;
		y += size.y;
	}
}

void Options::draw()
{
	for (auto obj : rect) {
		_data->_window.draw(*obj.second);
	}
	for (auto obj : text) {
		_data->_window.draw(*obj);
	}
}

void Options::setPosition(sf::Vector2f pos)
{
	this->pos = pos;
}
