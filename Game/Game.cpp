#include "Game.h"
#include"SplashState.h"
#include"EditorMenu.h"
#include<iostream>
namespace sg {

	sg::Game::Game(int width, int height, std::string title){

		_data->_window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), title,sf::Style::Fullscreen);
		_data->_window.setVerticalSyncEnabled(true);
		_data->_machine.AddState(StateRef(new SplashState(this->_data)),true);
		_data->_maploader.init(&this->_data->_asset);
		_data->_settings.SetViewToNormal(_data->_window);
		this->Run();
	}

	sg::Game::~Game()
	{
	}

	void sg::Game::Run()
	{


		while (this->_data->_window.isOpen()) {

			this->_data->_settings.Update(this->_data->_window);

			this->_data->_machine.ProcessStateChanges();
	
			this->_data->_machine.GetActiveState()->HandleInput();	//handle input

			this->_data->_machine.GetActiveState()->Update(0.1f);			//update

			this->_data->_machine.GetActiveState()->Draw(0.01f);		//draw
		}
	}

}