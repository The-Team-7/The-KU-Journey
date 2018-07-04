#include "EditorMenu.h"
#include"DialogueBox.h"
#include"DEFINITIONS.h"
#include"MainMenuState.h"
#include "Mainmenu.h"
#include"iostream"
#include"vector"


EditorMenu::EditorMenu(sg::GameDataRef _data)
{
	this->_data = _data;
}


EditorMenu::~EditorMenu()
{

}

void EditorMenu::Init()
{
	std::cout << "editor init done!";
	std::string dir = ASSETS_DIR;
	this->_data->_asset.LoadTexture("leveldesignbg", dir + "bg2.jpg");
	this->_data->_asset.LoadTexture("create_button", dir + "button_create.png");
	this->_data->_asset.LoadTexture("load_button", dir + "button_load.png");
	bg.setTexture(_data->_asset.GetTexture("leveldesignbg"));
	button_create.setTexture(_data->_asset.GetTexture("create_button"));
	button_load.setTexture(_data->_asset.GetTexture("load_button"));
	bg.setPosition(0, 0);
	button_create.setPosition(830, 250);
	button_load.setPosition(830, 350);
	mouseRect.setSize(Vector2f(5, 5));

	std::cout << "editor init done!";
}

void EditorMenu::HandleInput()
{
	sf::Event event;
	while (_data->_window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code==Keyboard::Escape) {
				this->_data->_machine.AddState(sg::StateRef(new sg::MainMenu(this->_data)),true);
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.key.code == Mouse::Left) {
				buttonPressedhandler();
			}
		}
	}
}

void EditorMenu::Update(float dt)
{
	Vector2f mousePos = this->_data->_window.mapPixelToCoords(sf::Mouse::getPosition(this->_data->_window));
	this->mouseRect.setPosition(mousePos.x, mousePos.y);
	std::vector<Sprite*> buttons = {&button_create,&button_load};
	for (auto button:buttons) {
		if (button->getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {

			button->setColor(Color::Yellow);
		}
		else {
			button->setColor(Color::White);
		}
	}
}

void EditorMenu::Draw(float dt)
{
	_data->_window.clear();
	_data->_window.draw(bg);
	_data->_window.draw(button_create);
	_data->_window.draw(button_load);
	_data->_window.display();
}

void EditorMenu::Pause()
{
}

void EditorMenu::Resume()
{
}

void EditorMenu::buttonPressedhandler()
{
	if (button_create.getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
		_data->_machine.AddState(sg::StateRef(new DialogueBox(_data, DialogueBox::Type::create)), true);
	}
	if (button_load.getGlobalBounds().intersects(mouseRect.getGlobalBounds())) {
		_data->_machine.AddState(sg::StateRef(new DialogueBox(_data, DialogueBox::Type::load)), true);
	}
}

