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
	{ "gate",dir + "gate.png" } ,
	{ "sidewall1",dir + "sidewall1.png" },
	{ "sidewall2",dir + "sidewall2.png" },
	{ "sidewall3",dir + "sidewall3.png" },
	{ "sidewall4",dir + "sidewall4.png" },
	{ "stonewall",dir + "stonewall.png" },
	{ "table1",dir + "table1.png" },
	{ "table2",dir + "table2.png" },
	{ "chair1",dir + "chair1.png" },
	{ "chest",dir + "chest.png" },
	{ "crates",dir + "crates.png" } ,
	{ "wall1",dir + "wall1.png" },
	{ "wall2",dir + "wall2.png" }, 
	{"resume",dir+"resume.png"},
	{"save",dir+"save.png"},
	{"exit",dir+"exit.png"}
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

