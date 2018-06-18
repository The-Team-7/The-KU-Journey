#include "levelState.h"


namespace sg{
	levelState::levelState(GameDataRef data):_data(data)
	{

	}


	levelState::~levelState()
	{
	}

	void levelState::Init()
	{
		this->bg.setTexture(_data->_asset.getTexture("levelOneBackground"));
	}

	void levelState::HandleInput()
	{
		sf::Event event;
		if (this->_data->_window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->_window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					this->_data->_window.close();
				}
			}
		}
	}

	void levelState::Update(float dt)
	{

	}

	void levelState::Draw(float dt)
	{
		this->_data->_window.clear();
		this->_data->_window.draw(bg);

		this->_data->_window.display();
	}

}
