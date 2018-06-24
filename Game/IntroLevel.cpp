#include "IntroLevel.h"
#include "MainMenuState.h"
#include"Collision.h"



IntroLevel::IntroLevel(sg::GameDataRef _data)
{
	this->_data = _data;
}


IntroLevel::~IntroLevel()
{
}

void IntroLevel::Init()
{


	//setting up player//
	this->_data->_asset.LoadTexture("Player", "assets//oldman.png");
	player = *new Person(&this->_data->_asset.GetTexture("Player"), sf::Vector2u(9, 4), sf::Vector2f(500,500));
	player.setSpirite(0, 2, 1, 3);
	player.setShift(6);
	player.setRPGMODE();

	
	this->map = _data->_maploader.loadMap("level",&this->_data->_asset);
	map.showIBound();

	//setting view//
	zoom = 0.8f;
	view.reset(sf::FloatRect(0, 0, 1920, 1080));
	view.setCenter(player.sprite.getPosition());
	view.zoom(zoom);

}

void IntroLevel::HandleInput()
{
	sf::Event event;
	while (_data->_window.pollEvent(event)) {
		if (event.type == Event::KeyPressed) {

			if (event.key.code == sf::Keyboard::Up) {
				player.move(Person::moves::up);
			}
			if (event.key.code == sf::Keyboard::Down) {
				player.move(Person::moves::down);
			}
			if (event.key.code == sf::Keyboard::Left) {
				player.move(Person::moves::left);
			}
			if (event.key.code == sf::Keyboard::Right) {
				player.move(Person::moves::right);
			}

			if (event.key.code == sf::Keyboard::Space) {
				player.jump();
			}

			if (event.key.code == sf::Keyboard::Escape) {
				_data->_machine.AddState(sg::StateRef(new sg::MainMenuState(_data)), false);
			}
		}
	}
}

bool IntroLevel::Interaction1(String entity)
{
	/****************************** TYPE 1 INTERACTION ************************************/

	/*This function checks for the collision of player with the type of objects where restriction of movement is required*/
	/*If there has been any interaction of player with certain type of objects then player is restricted to move in specific direction*/

	bool collision = false;
	for (auto box : this->map.objects[entity]) {
		if (Collision::PixelPerfectTest(box->sprite, player.sprite)) {
			collision = true;
		};
	}

	if (collision) {
		if (player.face == Person::Face::up) {
			player.moveup = false;
			player.sprite.move(0, 10);
		}
		else {
			player.moveup = true;
		}
		if (player.face == Person::Face::down) {
			player.movedown = false;
			player.sprite.move(0, -10);
		}
		else {
			player.movedown = true;
		}
		if (player.face == Person::Face::right) {
			player.moveright = false;
			player.sprite.move(-10, 0);
		}
		else {
			player.moveright = true;
		}
		if (player.face == Person::Face::left) {
			player.moveleft = false;
			player.sprite.move(10, 0);
		}
		else {
			player.moveleft = true;
		}
		return true;
	}
	else {
		return false;
	}
}

void IntroLevel::InteractionHandler()
{
	/******** This function handles all type of Interactions *************/

	std::vector<std::string> entity = { "tree","box","mainbase","sidewall1","sidewall2","sidewall3","stonewall","sidewall4","wall1","wall2","chair1","table1","table2","chest" }; /* entities name which belongs to type 1 Interaction */
	bool collision1 = false; // this bool is required to check if there has been any type 1 interactions in the game//

	for (auto e : entity) {
		if (Interaction1(e)) {
			collision1 = true; // If there has been any type 1 interaction this bool variable is set to true //
		};
	}

	/* Type 1 interaction restricts player movement in certain direction . It is essential to free the restrictions if there is not
	any interactions. So if no any interaction , player is allowed to move in any direction.
	*/

	if (!collision1) {
		player.moveleft = true;
		player.moveright = true;
		player.moveup = true;
		player.movedown = true;
	}
}


void IntroLevel::Update(float dt)
{
	
	InteractionHandler();
	view.setCenter(player.sprite.getPosition());
	_data->_window.setView(view);
	map.update();
}

void IntroLevel::Draw(float dt)
{
	_data->_window.clear();
	this->map.draw(&_data->_window);
	_data->_window.draw(player.sprite);
	_data->_window.display();
}

void IntroLevel::Pause()
{
}

void IntroLevel::Resume()
{
	_data->_window.setView(view);
}



