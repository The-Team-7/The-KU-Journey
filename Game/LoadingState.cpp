#include "LoadingState.h"
//#include "LevelOne.h"
namespace sg{
	LoadingState::LoadingState(GameDataRef data) : _data(data)
	{
		
	}
	LoadingState::~LoadingState()
	{
	}
	void LoadingState::Init()
	{
		this->_data->_asset.LoadTexture("BackgroundLoadingState", BACKGROUND_LOADING_STATE);
		this->bg.setTexture(this->_data->_asset.getTexture("BackgroundLoadingState"));

		this->clock = new sf::Clock();
		this->text.setFont(this->_data->_asset.getFont("narratorFont"));
		this->text.setFillColor(sf::Color(136, 136, 136, 255));
		this->text.setCharacterSize(60);
		
		this->load = "Loading";
		this->text.setString(this->load);
		this->text.setPosition(50,SCREEN_HEIGHT/2 + 300);
		n = 0;

		this->threadTask.setFont(this->_data->_asset.getFont("narratorFont"));
		this->threadTask.setFillColor(sf::Color(136, 136, 136, 255));
		this->threadTask.setCharacterSize(40);

		this->taskname = "iniitalizing loading";
		this->threadTask.setString(this->taskname);
		this->threadTask.setPosition(50, SCREEN_HEIGHT / 2 + 400);
		
		this->assets = std::thread (&LoadingState::loadAssets,this);
		this->threadFinished = false;

	}
	void LoadingState::HandleInput()
	{
		
	}
	void LoadingState::Update(float dt)
	{
		if (this->clock->getElapsedTime().asSeconds() >= .5f) {
			n++;
			if (this->load.length() < 10) {
				this->load += ".";
			}
			else {
				this->load = "Loading.";
			}
			this->text.setString(this->load);
			this->clock->restart();
		}
		if (this->threadFinished) {
			this->_data->_machine.AddState(StateRef(new levelState(this->_data)), true);
		}
		
	}
	void LoadingState::Draw(float dt)
	{
		this->_data->_window.clear();
		this->_data->_window.draw(bg);
		this->_data->_window.draw(text);
		this->_data->_window.draw(this->threadTask);
		this->_data->_window.display();
	}
	void LoadingState::loadAssets()
	{
		//std::this_thread::sleep_for(std::chrono::seconds(1));

		this->taskname = "loading Texture";
		this->threadTask.setString(this->taskname);
			//std::this_thread::sleep_for(std::chrono::seconds(1));
		this->_data->_asset.LoadTexture("player1Texture", PLAYER_1_TEXTURE);
		this->_data->_asset.LoadTexture("levelOneBackground", BACKGROUND_LEVEL1);
		this->_data->_asset.LoadTexture("dialogueBg",DIALOGUE_BG);
		this->_data->_asset.LoadTexture("playerProfile",PLAYER_PROFILE_1);

		this->taskname = "Texture Loaded";

		this->taskname = "loading weapons";
		this->threadTask.setString(this->taskname);
			//std::this_thread::sleep_for(std::chrono::seconds(1));
		
		this->taskname = "Finished loading";


		this->threadTask.setString(this->taskname);
		this->threadFinished = true;
	}
}