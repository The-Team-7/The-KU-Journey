#include "IntroLevel.h"
#include "Person.h"
#include "Player.h"
#include "FirstLevel.h"



IntroLevel::IntroLevel(sg::GameDataRef data) :_data(data)
{
	this->convo = new sg::Conversation();
	this->_data->_asset.LoadTexture("go", "Resource//introLevel//go.png");
	this->go.setTexture(_data->_asset.GetTexture("go"));
	this->go.setPosition(1622, 910);
	this->bg.setTexture(_data->_asset.GetTexture("intro-bg"));
}

void IntroLevel::Init()
{
	this->convo->startConvo(INTRO, _data);
	this->convo->next();
	this->_data->_asset.LoadTexture("Player", "assets//oldMan.png");
	p = *new Player();
	p.setPosition(sf::Vector2f(180, 810));
	p.shift = 25;
	p.canJump = true;
	p.isJumping = false;
	this->opacity = 255;
	this->transitClock = new sf::Clock();
	this->transit.setSize(sf::Vector2f(1920, 1080));
}

void IntroLevel::HandleInput()
{
	sf::Event event;
	while (_data->_window.pollEvent(event)) {
		if (event.type == Event::KeyPressed) {

			if (this->convo->getDisplayConversation() == false) {
				if (event.key.code == sf::Keyboard::A) {
					p.move(Player::moves::left);
				}
				if (event.key.code == sf::Keyboard::D) {
					p.move(Player::moves::right);
				}

				if (event.key.code==sf::Keyboard::F) {
					p.animate(Player::animation::shooting);
				}
				if (event.key.code == sf::Keyboard::G) {
					p.animate(Player::animation::slash);
				}
				if (event.key.code == sf::Keyboard::T) {
					p.animate(Player::animation::thrust);
				}
				if (event.key.code == sf::Keyboard::H) {
					p.animate(Player::animation::spellcast);
				}
			}

			if (p.sprite.getPosition().x <= 0) {
				p.sprite.setPosition(0, p.sprite.getPosition().y);
			}
			if (p.sprite.getPosition().x >= _data->_window.getSize().x) {
				this->_data->_machine.AddState(sg::StateRef(new FirstLevel(this->_data)), true);
			}
			if (event.key.code == sf::Keyboard::Space) {
				this->convo->next();
			}
			if (event.key.code == sf::Keyboard::Escape) {
				this->_data->_machine.AddState(sg::StateRef(new sg::MainMenu(this->_data)), true);
			}
		}
	}
}

void IntroLevel::Update(float dt)
{
	this->transit.setFillColor(sf::Color(0, 0, 0, opacity));
	p.update();
	if (this->transitClock->getElapsedTime().asMilliseconds() >= 10 && opacity != 0) {
		if (opacity > 0) {
			opacity -= 5;
		}
		if (opacity < 0) {
			opacity = 0;
		}
	}
}

void IntroLevel::Draw(float dt)
{
	_data->_window.clear();
	_data->_window.draw(this->bg);
	this->map.draw(&_data->_window);
	p.draw(_data->_window);
	this->convo->draw();
	if (convo->getDisplayConversation() == false) {
		_data->_window.draw(this->go);
	}
	_data->_window.draw(transit);
	_data->_window.display();
}
