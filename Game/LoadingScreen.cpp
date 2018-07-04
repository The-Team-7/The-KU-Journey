#include "LoadingScreen.h"
#include "IntroLevel.h"

namespace sg {
	LoadingScreen::LoadingScreen(GameDataRef data) : _data(data)
	{
	}
	LoadingScreen::~LoadingScreen()
	{
	}
	void LoadingScreen::Init()
	{
		this->_data->_asset.LoadTexture("BackgroundLoadingScreen", BACKGROUND_LOADING_STATE);
		this->bg.setTexture(this->_data->_asset.GetTexture("BackgroundLoadingScreen"));

		this->clock = new sf::Clock();
		this->_data->_asset.LoadFont("Accura", ACCURA);
		this->_data->_asset.LoadFont("Neuton", NEUTON);
		this->text.setFont(this->_data->_asset.GetFont("Accura"));
		this->text.setFillColor(sf::Color(136, 136, 136, 255));
		this->text.setCharacterSize(60);

		this->load = "Loading";
		this->text.setString(this->load);
		n = 0;

		this->threadTask.setFont(this->_data->_asset.GetFont("Neuton"));
		this->threadTask.setFillColor(sf::Color(136, 136, 136, 255));
		this->threadTask.setCharacterSize(40);
		this->taskname = "iniitalizing loading";
		this->threadTask.setString(this->taskname);
		//this->threadTask.setPosition(SCREEN_WIDTH / 2 - this->threadTask.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 + 400);

		this->threadFinished = false;
		this->assets = std::thread(&LoadingScreen::loadAssets, this);
		
	}
	void LoadingScreen::HandleInput()
	{

	}
	void LoadingScreen::Update(float dt)
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
			this->_data->_machine.AddState(StateRef(new IntroLevel(this->_data)), true);
		}
	}
	void LoadingScreen::Draw(float dt)
	{
		this->_data->_window.clear();
		this->_data->_window.draw(bg);
		this->text.setPosition(SCREEN_WIDTH / 2 - this->text.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 + 300);

		this->_data->_window.draw(text);
		this->threadTask.setPosition(SCREEN_WIDTH / 2 - this->threadTask.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 + 400);
		this->_data->_window.draw(this->threadTask);
		this->_data->_window.display();
	}
	void LoadingScreen::loadAssets()
	{
		

		this->taskname = "Texture";
		this->threadTask.setString(this->taskname);

		//character profile
		this->taskname = "Character Profile";
		this->threadTask.setString(this->taskname);
		//narrator
		this->_data->_asset.LoadTexture("bg-Narrator", NARRATOR_bg);
		this->_data->_asset.LoadTexture("avatar-Narrator", NARRATOR_dp);
		this->_data->_asset.LoadFont("narratorFont", NARRATOR_FONT);
		//this->_data->_asset.LoadSoundBuffer("narratorSound", NARRATOR_sound);
		//this->_data->_asset.LoadSoundBuffer("typing", TYPEWRITER_typing);
		//karun
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		this->_data->_asset.LoadTexture("dialogueBox-Karun", KARUN_bg);
		this->_data->_asset.LoadTexture("avatar-Karun", KARUN_dp);
		this->_data->_asset.LoadFont("karunFont", KARUN_FONT);
		//bijay
		this->_data->_asset.LoadTexture("dialogueBox-Bijay", BIJAY_bg);
		this->_data->_asset.LoadTexture("avatar-Bijay", BIJAY_dp);
		this->_data->_asset.LoadFont("bijayFont", BIJAY_FONT);
		//prabhat
		this->_data->_asset.LoadTexture("dialogueBox-Prabhat", PRABHAT_bg);
		this->_data->_asset.LoadTexture("avatar-Prabhat", PRABHAT_dp);
		this->_data->_asset.LoadFont("prabhatFont", PRABHAT_FONT);
		//anup
		this->_data->_asset.LoadTexture("dialogueBox-Anup", ANUP_bg);
		this->_data->_asset.LoadTexture("avatar-Anup", ANUP_dp);
		this->_data->_asset.LoadFont("anupFont", ANUP_FONT);
		
		//background
		this->_data->_asset.LoadTexture("intro-bg", INTRO_BG);
		this->taskname = "weapons";
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		this->threadTask.setString(this->taskname);
		this->taskname = "completed";
		this->threadTask.setString(this->taskname);
		//std::this_thread::sleep_for(std::chrono::seconds(2));
		this->threadFinished = true;
	}
}