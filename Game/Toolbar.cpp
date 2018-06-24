#include "Toolbar.h"



Toolbar::Toolbar(sg::GameDataRef _data)
{
	this->_data = _data;
	this->boxSize = sf::Vector2f(100, 100);

	col = 7;
	row = 15;

	titleRect.setPosition(1500, 150);
	titleRect.setSize(sf::Vector2f(boxSize.x*col, boxSize.y));
	titleRect.setFillColor(sf::Color::Blue);
	titleRect.setOutlineColor(sf::Color::Blue);
	titleRect.setOutlineThickness(3);

	int total_boxes = row * col;
	for (int i = 1; i <= total_boxes; i++) {
		this->boxes.push_back(new box);
	}

	float x = titleRect.getPosition().x;
	float y = titleRect.getPosition().y + boxSize.y;
	int m = 0, n = 0;

	for (auto box : this->boxes) {
		box->rect.setSize(boxSize);
		box->rect.setOutlineThickness(3);
		box->rect.setOutlineColor(sf::Color::Blue);
		box->rect.setFillColor(sf::Color::Yellow);
		box->rect.setPosition(x, y);
		box->isActive = false;
		box->isLocked = false;
		m++;
		x += boxSize.x;
		if (m == col) {
			m = 0;
			x = titleRect.getPosition().x;
			y += boxSize.y;
		}
	}

	toolbar.setSize(sf::Vector2f(boxSize.x*col, boxSize.y*(row + 1)));
	toolbar.setPosition(titleRect.getPosition().x, titleRect.getPosition().y);
	toolbar.setFillColor(sf::Color::Green);
}


Toolbar::~Toolbar()
{
}

void Toolbar::handleInput()
{
}

void Toolbar::update()
{
	float x = titleRect.getPosition().x;
	float y = titleRect.getPosition().y + boxSize.y;
	int m = 0, n = 0;

	for (auto box : this->boxes) {

		box->rect.setSize(boxSize);
		box->rect.setOutlineThickness(3);
		box->rect.setOutlineColor(sf::Color::Blue);
		box->rect.setPosition(x, y);
		m++;
		x += boxSize.x;
		if (m == col) {
			m = 0;
			x = titleRect.getPosition().x;
			y += boxSize.y;
		}
	}

	toolbar.setPosition(titleRect.getPosition().x, titleRect.getPosition().y);


}

void Toolbar::draw()
{
	_data->_window.draw(toolbar);
	for (auto box : boxes) {
		_data->_window.draw(box->rect);
	}
	_data->_window.draw(titleRect);


}


