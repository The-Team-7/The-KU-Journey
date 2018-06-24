#include "IdManager.h"



IdManager::IdManager(sg::GameDataRef _data)
{
	this->_data = _data;
}

IdManager::~IdManager()
{
}

void IdManager::Init()
{
	map=_data->_maploader.loadMap("idmanager",&_data->_asset);
	idInput = *new InputBox(Vector2f(1200, 580), "s", "text", "ID");

}

void IdManager::HandleInput()
{
	sf::Event event;
	while(_data->_window.pollEvent(event)) {
		idInput.update(event,_data->_settings._mouse);
	}
	
}

void IdManager::Update(float dt)
{
	
}

void IdManager::Draw(float dt)
{
	_data->_window.clear();
	map.draw(&_data->_window);
	idInput.draw(_data->_window);
	_data->_window.display();
}
