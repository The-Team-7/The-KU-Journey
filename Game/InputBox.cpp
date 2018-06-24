#include "InputBox.h"
#include "DEFINITIONS.h"


InputBox::InputBox()
{
}

InputBox::InputBox(sf::Vector2f pos, std::string size, std::string type,std::string labelText)
{
	box.setFillColor(sf::Color::White);
	isActive = false;
	box.setPosition(pos);
	std::string path = ASSETS_DIR;
	font.loadFromFile(path+"Pixellari.ttf");
	text.setFont(font);
	text.setString("");
	text.setPosition(pos.x +14, pos.y+4);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::Black);
	Label.setFont(font);
	Label.setString(labelText);
	Label.setCharacterSize(30);
	Label.setFillColor(sf::Color::Red);
	textLimit = 100;


	this->type = type;

	if (size== "s") {
		box.setSize(sf::Vector2f(250,40));
		Label.setPosition((pos.x+250/2)-(labelText.size()*12), pos.y-42);
		textLimit = 15;
	}
	else if(size=="l"){
		box.setSize(sf::Vector2f(450,45));
		Label.setPosition((pos.x + 450/2)- (labelText.size() *12),pos.y - 42);
		textLimit = 29;
	}
	else if (size == "xl") {
		box.setSize(sf::Vector2f(560, 45));
		Label.setPosition((pos.x + 560/2)- (labelText.size() * 12), pos.y - 42);
		textLimit = 40;
	}
	else {
		box.setSize(sf::Vector2f(360, 45));
		Label.setPosition((pos.x + 360/2)- (labelText.size() * 12), pos.y - 42);
		textLimit = 22;
	}

	
}


InputBox::~InputBox()
{
}

void InputBox::setFont(sf::Font & font)
{
	text.setFont(font);
}

void InputBox::setPosition(sf::Vector2f pos)
{
	box.setPosition(pos);
}

std::string InputBox::getString()
{
	return text.getString();
}

void InputBox::draw(sf::RenderWindow & win)
{

	text.setString(inputData);
	win.draw(box);
	win.draw(this->text);
	win.draw(this->Label);
}

void InputBox::setActive()
{
	isActive = true;
	this->box.setFillColor(sf::Color::Magenta);
}

void InputBox::setInactive()
{

	this->isActive = false;
	this->box.setFillColor(sf::Color::White);
}

void InputBox::update(sf::Event evnt,sf::RectangleShape& _mouse)
{

		if (evnt.type == sf::Event::TextEntered) {
			if (isActive) {
				if (evnt.text.unicode == 8) {
					if (inputData.size() != 0) {
						inputData.erase(inputData.begin() + inputData.size() - 1);
						text.setString(inputData);
					}
				}
				else{
					if (type=="number") {
						if((evnt.text.unicode >= 48 && evnt.text.unicode <= 57)) {
							if (inputData.size() <= textLimit) {
								inputData =inputData+ evnt.text.unicode;
								text.setString(inputData);
							}
						}
					}

					if (type == "text") {
						if ((evnt.text.unicode >= 48 && evnt.text.unicode <= 57) || (evnt.text.unicode >= 64 && evnt.text.unicode <= 90) || (evnt.text.unicode >= 95 && evnt.text.unicode <= 122)) {
							if (text.getString().getSize() <= textLimit) {
								inputData = inputData + evnt.text.unicode;
								text.setString(inputData);
							}
						}
					}
					
				}
			}
		}
		if (evnt.type == sf::Event::MouseButtonPressed){
			if (evnt.key.code == sf::Mouse::Left) {
				if (box.getGlobalBounds().intersects(_mouse.getGlobalBounds())) {
					setActive();
				}
				else {
					setInactive();
				}
			}
			if (evnt.key.code == sf::Mouse::Right){
				setInactive();
			}
		}
	
}




