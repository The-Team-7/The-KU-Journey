#include "Settings.h"
#include"DEFINITIONS.h"



Settings::Settings()
{
	std::string dir = ASSETS_DIR;

	_mouse.setSize(sf::Vector2f(4,4));
	_mouse.setFillColor(sf::Color::White);

	MapTextureInfo = { 

	{ "tree",dir + "tree.png" } ,
	{ "path",dir + "path.png" },
	{ "fighter",dir + "fighter.jpg" },
	{ "box",dir + "box.jpg" },
	{ "mainbase",dir + "mainbase.png" },
	{ "mario",dir + "mario.png" },
	{ "bg1",dir + "bg1.png" },
	{ "bg2",dir + "bg2.jpg" },
	{ "darkbg",dir + "darkbg.jpg" },
	{ "button_create",dir + "button_create.png" },
	{ "button_load",dir + "button_load.png" },
	{ "grass1",dir + "grass1.png" },
	{ "grass2",dir + "grass2.png" },
	{ "grass3",dir + "grass3.png" },
	{ "road1",dir + "road1.png" },
	{"resume",dir+"resume.png"},
	{"save",dir+"save.png"},
	{"exit",dir+"exit.png"},
	{ "mainbg",dir + "mainbg.png" },
	{ "chain",dir + "chain.png" },
	{ "grasschunk",dir + "grasschunk.png" },
	{ "rightgrass",dir + "rightgrass.png" },
	{ "leftgrass",dir + "leftgrass.png" },
	{ "floatplatform",dir + "floatplatform.png" },
	{ "mudSpike",dir + "mudSpike.png" },
	{ "boneSpike",dir + "boneSpike.png" },
	{ "hangingSpike",dir + "hangingSpike.png" },
	{ "float",dir+"float.png" },
	{ "greenGem",dir + "greenGem.png" },
	{ "purpleGem",dir + "purpleGem.png" },
	{ "yellowGem",dir + "yellowGem.png" },
	{ "algaeUp",dir + "algaeUp.png" },
	{ "algaeDown",dir + "algaeDown.png" },
	{"base",dir+"base.png"}
	};

}

void Settings::SetViewToNormal(sf::RenderWindow & win)
{

	this->view.setSize(1920,1080);
	this->view.setCenter(1920/2,1080/2);
	win.setView(view);
}

sf::Vector2f Settings::GetMousePosition(sf::RenderWindow & _window)
{
	sf:: Vector2f mousePos = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
	return mousePos;
}

void Settings::Update(sf::RenderWindow & _window)
{
	_mouse.setPosition(GetMousePosition(_window));
}

