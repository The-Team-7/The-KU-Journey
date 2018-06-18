#include "DialogueBox.h"
#include"EditorMenu.h"
#include"MapEditor.h"

DialogueBox::DialogueBox(sg::GameDataRef _data, DialogueBox::Type type)
{
	this->_data = _data;
	this->type = type;
}


DialogueBox::~DialogueBox()
{
}


void DialogueBox::Init()
{
	mouseRect.setSize(Vector2f(2, 2));
	textLimit = 20;
	std::string dir = "assets//";
	std::string texName[2] = { "create_button","load_button" };

	if (type == create) {
		button.setTexture(_data->_asset.GetTexture(texName[0]));
	}
	else if (type == load) {

		button.setTexture(_data->_asset.GetTexture(texName[1]));
	}

	_data->_asset.LoadTexture("darkbg", dir + "darkbg.jpg");

	background.setTexture(_data->_asset.GetTexture("leveldesignbg"));
	background.setTextureRect(sf::IntRect(0, 0, 1920, 1080));


	filenameTextBox.setSize(Vector2f(450, 45));
	filenameTextBox.setPosition(800, 300);
	filenameTextBox.setFillColor(Color::White);
	background.setPosition(0, 0);
	dialogueBox.setPosition(650, 200);
	button.setPosition(880, 400);

	_data->_asset.LoadFont("font1", dir + "Pixellari.ttf");
	filenameLabel.setFont(_data->_asset.GetFont("font1"));
	filenameLabel.setString("Filename:");
	filenameLabel.setFillColor(Color::Black);
	filenameLabel.setPosition(630, 300);
	filenameLabel.setCharacterSize(35);

	displayText.setFont(_data->_asset.GetFont("font1"));
	displayText.setString(filenameText);
	displayText.setFillColor(Color::Black);
	displayText.setPosition(830, 300);
	displayText.setCharacterSize(35);

	InfoText.setFont(_data->_asset.GetFont("font1"));
	InfoText.setFillColor(Color::Red);
	InfoText.setPosition(800, 200);
	InfoText.setCharacterSize(35);
}

void DialogueBox::HandleInput()
{
	sf::Event event;
	while (_data->_window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == Keyboard::Escape) {
				_data->_machine.AddState(sg::StateRef(new EditorMenu(this->_data)),true);
			}
			if (event.key.code == Keyboard::Return) {
				std::cout << filenameText << std::endl;
			}
		}

		if (event.type == sf::Event::TextEntered) {
			if (isTextActive) {
				keyboardInputHandler(&event);
			}
		}

		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.key.code == Mouse::Left) {
				if (filenameTextBox.getGlobalBounds().intersects(this->_data->_settings._mouse.getGlobalBounds())) {
					isTextActive = true;
					filenameTextBox.setFillColor(Color::Magenta);
				}
				else {
					isTextActive = false;
					filenameTextBox.setFillColor(Color::White);
				}
				if (button.getGlobalBounds().intersects(this->_data->_settings._mouse.getGlobalBounds())) {

					if (filenameText.size()==0) {
						InfoText.setString("Field cannot be left empty!");
						InfoText.setPosition(800, 200);
						clock.restart();
						triggerInfo=true;
					}
					else {
						if (type == Type::load) {
							std::ifstream file;
							std::string name = MAPEDITOR_DIR+ filenameText + ".txt";
							file.open(name);
							if (file.is_open()) {
								_data->_machine.AddState(sg::StateRef(new MapEditor(this->_data, MapEditor::load, filenameText)), true);
							}
							else {
								InfoText.setString("There is no such file. Please Check the directory");
								InfoText.setPosition(680, 200);
								clock.restart();
								triggerInfo = true;
							}
						}
						if (type == Type::create) {
							_data->_machine.AddState(sg::StateRef(new MapEditor(this->_data, MapEditor::create, filenameText)), true);	
						}
					}
				}
			}
		}
	}
}

void DialogueBox::Update(float dt)
{
	displayText.setString(filenameText);
	mouseRect.setPosition(sf::Mouse::getPosition(_data->_window).x, sf::Mouse::getPosition(_data->_window).y);

	if (button.getGlobalBounds().intersects(this->_data->_settings._mouse.getGlobalBounds())) {

		button.setColor(Color::Yellow);
	}
	else {
		button.setColor(Color::White);
	}
}

void DialogueBox::Draw(float dt)
{
	_data->_window.clear();
	_data->_window.draw(background);
	_data->_window.draw(filenameTextBox);
	_data->_window.draw(displayText);
	_data->_window.draw(filenameLabel);

	if (clock.getElapsedTime().asSeconds()<= 2 && this->triggerInfo)
	{
		_data->_window.draw(InfoText);
	}
	else {
		triggerInfo = false;
	}

	_data->_window.draw(button);
	_data->_window.display();
}

void DialogueBox::Pause()
{
}

void DialogueBox::Resume()
{
}

void DialogueBox::keyboardInputHandler(Event * evnt)
{
	if (evnt->text.unicode == 8) {
		if (filenameText.size() != 0) {
			filenameText.erase(filenameText.begin() + filenameText.size() - 1);
		}
	}
	else if ((evnt->text.unicode >= 48 && evnt->text.unicode <= 57) || (evnt->text.unicode >= 64 && evnt->text.unicode <= 90) || (evnt->text.unicode >= 95 && evnt->text.unicode <= 122)) {
		if (filenameText.size() <= textLimit) {
			filenameText = filenameText + evnt->text.unicode;
		}
	}

}

