#include "LevelOne.h"

namespace sg {

	sg::LevelOne::LevelOne(GameDataRef data) :_data(data)
	{
//		enemyFactory = new EnemyFactory(_data);
	}

	sg::LevelOne::~LevelOne()
	{
	}

	void sg::LevelOne::Init()
	{
		
		this->bg.setTexture(this->_data->_asset.getTexture("levelOneBackground"));

		//Player p1(this->_data->_asset.getTexturePointer("player1Texture") ,sf::Vector2u(4,4),sf::Vector2f(300,300));
		//this->_playerMap[Enums::Characters::Player] = p1;

		//enemy
		/*Enemy* enemy;
		enemy = this->enemyFactory->makeEnemy(Enums::minions, sf::Vector2f(300,300));
		tort.push_back(*enemy);

		Enemy* tort2;
		tort2 = this->enemyFactory->makeEnemy(Enums::minions, sf::Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
		tort.push_back(*tort2);
*/
	}

	void sg::LevelOne::HandleInput()
	{
		sf::Event event;
		while (this->_data->_window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->_window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					this->_data->_window.close();
				}
			}

			if (event.type == Event::KeyPressed) {
				if (keys.count(event.key.code) == 0) {
					keys[event.key.code] = true;
				}
			}
			if (event.type == Event::KeyReleased) {
				if (keys.count(event.key.code) == 1) {
					keys.erase(event.key.code);
				}
			}
		}
	}

	void sg::LevelOne::Update(float dt)
	{
		for (auto keyvalue : keys) {

			int code = keyvalue.first;
			//if (.canjump) {
				if (code == Keyboard::W) {
					this->_playerMap[Enums::Characters::Player].move(Object::moves::up);
				}
				if (code == Keyboard::S) {
					this->_playerMap[Enums::Characters::Player].move(Object::moves::down);
				}
				if (code == Keyboard::A) {
					this->_playerMap[Enums::Characters::Player].move(Object::moves::left);
				}
				if (code == Keyboard::D) {
					this->_playerMap[Enums::Characters::Player].move(Object::moves::right);
				}
		}
	}

	void sg::LevelOne::Draw(float dt)
	{
		this->_data->_window.clear();
		this->_data->_window.draw(bg);
		
		if (!tort.empty()) {
			for (auto i : tort) {
				i.update(&this->_data->_window);
			}
		}

		this->_playerMap[Enums::Characters::Player].update(&this->_data->_window);
		
		this->_data->_window.display();
	}
}