#include "FirstLevel.h"
#include "Mainmenu.h"
#include "Collision.h"



FirstLevel::FirstLevel(sg::GameDataRef _data)
{
	this->_data = _data;
}


FirstLevel::~FirstLevel()
{
	
}

void FirstLevel::Init()
{
	this->map = this->_data->_maploader.loadMap("jangam", &_data->_asset);
	this->_data->_asset.LoadTexture("Player", "assets//oldMan.png");
	player = *new Player();
	player.canJump=true;
	player.setPosition(sf::Vector2f(180, 810));
	for (auto object:map.objects["floatplatform"]) {
		object->showCollider();
	}

}

void FirstLevel::HandleInput()
{

	sf::Event event;
	while (_data->_window.pollEvent(event)) {
		if (event.type == Event::KeyPressed) {

			if (_input.count(event.key.code) == 0) {
				_input.insert(std::pair<int, bool>(event.key.code, true));
			}

		}
		if (event.type == sf::Event::KeyReleased) {
			if (_input.count(event.key.code)>0) {
				_input.erase(_input.find(event.key.code),_input.end());
			}
		}

	}

	for (auto key:_input) {
		if (key.first== sf::Keyboard::A) {
			player.move(Player::moves::left);
		}
		if (key.first == sf::Keyboard::D) {
			player.move(Player::moves::right);
		}
		if (key.first == sf::Keyboard::Space) {
			player.jump();
		}


		if (key.first == sf::Keyboard::Escape) {
			_data->_machine.AddState(sg::StateRef(new sg::MainMenu(_data)), false);
		}
	}
}

void FirstLevel::Update(float dt)
{
	InteractionHandler();
	player.update();
	if (player.sprite.getPosition().x <= 0) {
		player.sprite.setPosition(0, player.sprite.getPosition().y);
	}
	if (player.sprite.getPosition().x >= _data->_window.getSize().x) {
		//this->_data->_machine.AddState(sg::StateRef(new IntroLevelLevel(this->_data)), true);
	}

}

void FirstLevel::Draw(float dt)
{
	_data->_window.clear();
	map.draw(&_data->_window);
	player.draw(_data->_window);
	_data->_window.display();
}

void FirstLevel::InteractionHandler()
{
	std::vector<std::string> blockObjects = {"floatplatform","float","grasschunk"};
	blockInteraction(blockObjects);
	if (shouldObjectsFall(blockObjects)) {
		player.setToFallingState();
	};




}

bool FirstLevel::blockInteraction(std::vector<std::string> entities)
{
	float cory=player.sprite.getGlobalBounds().height/3;
	float corx = player.sprite.getGlobalBounds().width /3;
	bool sidewayFlag = true;

	for (auto entity:entities) {
		for (auto block : map.objects[entity]) {
			if (block->Collider.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {

				block->showCollider();
				block->Collider.setFillColor(sf::Color::Magenta);
				if (Collision::PixelPerfectTest(player.sprite, block->sprite) && !player.canJump) {
					std::cout << player.isJumping << std::endl;
					if ((player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width > block->sprite.getGlobalBounds().left &&
						player.sprite.getGlobalBounds().left < block->sprite.getGlobalBounds().left + block->sprite.getGlobalBounds().width)
						&& player.sprite.getGlobalBounds().top + player.sprite.getGlobalBounds().height - cory < block->sprite.getGlobalBounds().top && player.isJumping) {

						player.setPosition(sf::Vector2f(player.sprite.getPosition().x, block->sprite.getPosition().y - player.sprite.getGlobalBounds().height + 12));
						player.yVel = 0;
						player.xVel = 0;
						player.setToGroundState();
						std::cout << "on platform check";
						return true;
					}
				}



				if (Collision::PixelPerfectTest(player.sprite, block->sprite)) {
					if ((player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width > block->sprite.getGlobalBounds().left &&
						player.sprite.getGlobalBounds().left < block->sprite.getGlobalBounds().left + block->sprite.getGlobalBounds().width)
						&& (player.yVel < 0) && player.isJumping) {
						player.yVel = 6;
						player.xVel = 0;
						std::cout << "colliding up check";

						return false;
					}

					if (player.sprite.getGlobalBounds().top + player.sprite.getGlobalBounds().height - cory > block->sprite.getGlobalBounds().top &&
						player.sprite.getGlobalBounds().top < block->sprite.getGlobalBounds().top + block->sprite.getGlobalBounds().height - cory
					    & sidewayFlag) {

						if (player.xDir > 0 || player.face==Player::moves::right && (player.sprite.getGlobalBounds().left+player.sprite.getGlobalBounds().width-corx)>(block->sprite.getGlobalBounds().left)) {
							player.moveright = false;
							player.restrictX = true;

							std::cout << "from left";
							player.sprite.move(0, 0);
							sidewayFlag = false;
							return false;
						}

						if (player.xDir < 0 || player.face == Player::moves::left 
							&& player.sprite.getGlobalBounds().left>(block->sprite.getGlobalBounds().left+block->sprite.getGlobalBounds().width-corx)) {
							player.moveleft = false;
							player.restrictX = true;


							if (player.isJumping) {
								player.xVel = 2;
							}
							std::cout << "from right";
							player.sprite.move(0,0);
							return false;
						}
						else {
							player.moveleft = true;
							player.moveright = true;
							player.restrictX = false;
						}

					}

				}
			}
			else {

				block->Collider.setFillColor(sf::Color::White);
				block->hideCollider();
			}
		}
	}
}

bool FirstLevel::shouldObjectsFall(std::vector<std::string> entities)
{
	bool flag = true;
	float cory = player.sprite.getGlobalBounds().height / 2;
	float corx = player.sprite.getGlobalBounds().width / 2;
	for (auto entity : entities) {
		for (auto block : map.objects[entity]) {
			if (block->Collider.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {


				if (Collision::PixelPerfectTest(player.sprite, block->sprite)) {
					if ((player.sprite.getGlobalBounds().left + player.sprite.getGlobalBounds().width > block->sprite.getGlobalBounds().left &&
						player.sprite.getGlobalBounds().left < block->sprite.getGlobalBounds().left + block->sprite.getGlobalBounds().width)
						&& player.sprite.getGlobalBounds().top + player.sprite.getGlobalBounds().height - cory < block->sprite.getGlobalBounds().top) {
						flag = false;
					}
				}
			}
		}
	}

	return flag;
	
}










