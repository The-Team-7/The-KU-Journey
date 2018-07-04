
#include "MapEditor.h"
#include"DEFINITIONS.h"
#include<fstream>
#include "Collision.h"
#include "EditorMenu.h"
#include"MainMenu.h"
#include"ObjectSetupEditor.h"


MapEditor::MapEditor(sg::GameDataRef _data, Type type, std::string filename)
{
	_dir = MAPEDITOR_DIR;
	this->option = new Options(_data);
	this->_data = _data;
	this->_filename = filename;
	this->_type = type;
	this->toolbar = new Toolbar(_data);
}

MapEditor::~MapEditor()
{
}


//////////////////////////////// INITIALIZING EVERYTHING TO START THE MAP EDITOR ////////////////////////////////////
void MapEditor::Init()
{

	mapSize = Vector2f(1920 * 2, 1080 * 2);
	this->zoom = 2;
	this->is_selected = false;
	this->multiple_select = false;
	this->mouseClicked = false;
	this->altPressed = false;
	this->isTileSelected = false;
	this->object_being_dragged = false;
	this->triggerInfo = false;

	_data->_asset.LoadTexture("mouse", "mouse.png");
	this->mouseSpr.setColor(Color::Blue);
	this->mouseSpr.setTexture(_data->_asset.GetTexture("mouse"));
	this->mouseSpr.setTextureRect(IntRect(0, 0, 3, 3));

	this->mouseSprite.setSize(Vector2f(10, 10));
	this->mouseSprite.setFillColor(Color::Cyan);
	this->view.reset(sf::FloatRect(0, 0, 1920, 1080));
	bgRect.setSize(mapSize);
	bgRect.setFillColor(Color::Cyan);
	view.setCenter((1920/2)+110, (1080/2)+400);
	view.zoom(zoom);
	
	infoText.setFont(this->_data->_asset.GetFont("font1"));
	infoText.setFillColor(Color::Blue);
	infoText.setCharacterSize(34);
	
	//initializing map object//
	for (auto info : _data->_settings.MapTextureInfo) {
		_map.insert(std::make_pair(info.first, *new std::vector<StaticObject*>));
		_mapKey.push_back(info.first);
		objectSettings[info.first] = std::make_pair(0,FloatRect(0,0,0,0));
	}


	if (this->_type == Type::load) {	
		Map map = this->_maploader.loadMap(this->_filename, &_data->_asset);
		this->_map = map.objects;
		this->_mapKey = map.mapkey;


		for (auto obj : _map) {
			objectSettings[obj.first] = std::make_pair(_map[obj.first][0]->depth, _map[obj.first][0]->IRect);
		}



		for (auto info : _data->_settings.MapTextureInfo) {
			if (std::find(_mapKey.begin(), _mapKey.end(), info.first) != _mapKey.end()) {
				
			}
			else {
				_map.insert(std::make_pair(info.first, *new std::vector<StaticObject*>));
				_mapKey.push_back(info.first);
			}
		}

		std::vector<std::string> tempKey;

		for (auto key : map.mapkey) {
			tempKey.push_back(key);
		}

	}

	std::string gameDir = GAMEMAPS_DIR;
	_menuMap= this->_maploader.loadMap("EditorPauseMenu",&_data->_asset);
	_idMap = this->_maploader.loadMap("idmanager",&_data->_asset);
	idInput = *new InputBox(Vector2f(1920/2-200, 500), "l", "text", "Id");

	this->toolbar->titleRect.setPosition(-780, 0);
	populateToolbar();

	this->state = States::editorState;
}

/////////////////////////////////////// INPUT HANDLER ////////////////////////////////////////

void MapEditor::HandleInput()
{
	int shift = 30;
	int objShift = 10;
	sf::Event event;

	while (_data->_window.pollEvent(event)) {


		//INPUT HANDLER FOR EDITOR STATE//
		if (this->state == States::editorState) {

			if (event.type == Event::KeyPressed) {

				if (!isToolbarSelected) {

					if (is_selected) {

						for (auto selectedObject : selectedObjects) {

							if (event.key.code == sf::Keyboard::W) {
								selectedObject->sprite.move(0, -objShift);
							}

							if (event.key.code == sf::Keyboard::S) {
								selectedObject->sprite.move(0, objShift);
							}

							if (event.key.code == sf::Keyboard::D) {
								selectedObject->sprite.move(objShift, 0);
							}

							if (event.key.code == sf::Keyboard::A) {
								selectedObject->sprite.move(-objShift, 0);
							}

						}
						if (event.key.code == sf::Keyboard::Delete) {
							deleteObject();
						}
						if (event.key.code==sf::Keyboard::RShift) {
							
							  if (selectedObjects.size()==1) {
								this->state = States::idManager;
								view.reset(sf::FloatRect(0, 0, 1920, 1080));
								this->_data->_window.setView(view);
								idInput.inputData = selectedObjects[0]->id;
							}
						}

					}

					else {

						if (event.key.code == sf::Keyboard::W) {
							view.move(0, -shift);
						}
						if (event.key.code == sf::Keyboard::S) {
							view.move(0, shift);
						}
						if (event.key.code == sf::Keyboard::A) {
							view.move(-shift, 0);
						}
						if (event.key.code == sf::Keyboard::D) {
							view.move(shift, 0);
						}
						if (event.key.code == sf::Keyboard::Space) {
							this->_data->_settings.SetViewToNormal(_data->_window);
							view.setSize(1920, 1080);
							view.setCenter(1920 / 2, 1080 / 2);
						}
					}
				}

				if (event.key.code == Keyboard::LControl) {
					multiple_select = true;
				}

				if (event.key.code == Keyboard::LAlt) {
					altPressed = true;
				}
				if (event.key.code == Keyboard::Tab) {
					save();
				}
				if (isTileSelected) {
					if (event.key.code == Keyboard::Z) {
						swapToolbarObject(activeBox->texture_name, 1);
					}

					if (event.key.code == Keyboard::X) {
						swapToolbarObject(activeBox->texture_name, 2);
					}


					activeBox->rect.setFillColor(Color::White);
					std::string name = activeBox->texture_name;
					updateToolbar(name);
					activeBox->rect.setFillColor(Color::Cyan);
					
				}


				if (event.key.code == sf::Keyboard::Escape) {
					view.reset(sf::FloatRect(0, 0, 1920, 1080));
					this->_data->_window.setView(view);
					this->state = States::menuState;
					return;
				}

			}


			if (event.type == Event::KeyReleased) {

				if (event.key.code == Keyboard::LControl) {
					multiple_select = false;
				}
				if (event.key.code == Keyboard::LAlt) {
					altPressed = false;
				}
			}

			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (event.mouseWheelScroll.wheel == 1) {
					zoom = 0.9;
				}

				else {
					zoom = 1.1;
				}
				view.zoom(zoom);

			}
			if (event.type == Event::MouseButtonPressed) {

				if (event.key.code == Mouse::Left) {
					mouseClicked = true;

					if (!mouseOverToolBar && isTileSelected && !altPressed) {
						dropTileHandler();
					}

					if (!isOptionActive && !altPressed) {
						selectToolbar();
					}

					if (!isOptionActive && !mouseOverToolBar and !altPressed and !isTileSelected) {
						selectObject();
					}

					if (isOptionActive) {
						optionLeftClickHandler();
					}
				}

				if (event.key.code == Mouse::Right) {

					for (auto selectedObject : selectedObjects) {
						selectedObject->sprite.setColor(Color::White);
						selectedObjects.erase(selectedObjects.begin(), selectedObjects.end());
					}

					is_selected = false;

					if (isTileSelected) {
						selectedTile->sprite.setColor(Color::Transparent);
						activeBox->rect.setFillColor(Color::White);
					}


					isTileSelected = false;

					optionRightClickHandler();
				}
			}

			if (event.type == Event::MouseButtonReleased) {

				if (event.key.code == Mouse::Left) {
					mouseClicked = false;
				}
			}

			if (event.type == Event::MouseMoved) {

				if (mouseClicked && isToolbarSelected) {
					toolbarDragHandler();
				}

				if (mouseClicked && is_selected && !isToolbarSelected) {
					object_being_dragged = true;
					objectMouseDragHandler();
				}
				if (altPressed && mouseClicked && !is_selected && !isToolbarSelected) {
					mouseMovementHandler();
				}
				if (isTileSelected && !mouseOverToolBar) {
					tileDragHandler();
				}

			}
			else {
				object_being_dragged = false;
			}
		}
		//INPUT HANDLER FOR MENU STATE//
		if (this->state == States::menuState) {

			if (event.type == Event::KeyPressed) {

				if (event.key.code == Keyboard::Escape) {
					view.zoom(2);
					this->state = States::editorState;
				}
			}

			if (event.type == Event::MouseButtonPressed) {

				if (event.key.code == Mouse::Left) {
					for (auto obj : _menuMap.objects["resume"]) {
						if (obj->sprite.getGlobalBounds().intersects(mouseSprite.getGlobalBounds())) {
							view.zoom(2);
							this->state = States::editorState;
						}
					}
					for (auto obj : _menuMap.objects["exit"]) {
						if (obj->sprite.getGlobalBounds().intersects(mouseSprite.getGlobalBounds())) {
							view.reset(FloatRect(0, 0, 1920, 1080));
							this->_data->_machine.AddState(sg::StateRef( new sg::MainMenu(this->_data)), true);
						}
					}

					for (auto obj : _menuMap.objects["save"]) {
						if (obj->sprite.getGlobalBounds().intersects(mouseSprite.getGlobalBounds())) {
							save();
							infoText.setPosition(750,80);
							infoText.setString("***Save sucessfull!***");
							triggerInfo = true;
							clock.restart();
						}
					}

				}
			}
		}
		if (this->state == States::idManager) {
			idInput.update(event, _data->_settings._mouse);

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					idInput.text.setString("");
					view.zoom(2);
					this->state = States::editorState;
				}	
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code==sf::Mouse::Left) {
					for (auto obj : _idMap.objects["save"]) {
						if (obj->sprite.getGlobalBounds().intersects(mouseSprite.getGlobalBounds())) {
							if (idInput.getString()=="") {
								for (auto selectedObject : selectedObjects) {
									selectedObject->id = "null";
									selectedObject->sprite.setColor(Color::White);
									selectedObjects.erase(selectedObjects.begin(), selectedObjects.end());
								}
							}
							else {
								for (auto selectedObject : selectedObjects) {
									selectedObject->id = idInput.getString();
									selectedObject->sprite.setColor(Color::White);
									selectedObjects.erase(selectedObjects.begin(), selectedObjects.end());
								}
							
							}
						}
					}
				}
			
			}

			if (event.type == Event::MouseMoved) {
				for (auto obj : _idMap.objects["save"]) {
					if (obj->sprite.getGlobalBounds().intersects(mouseSprite.getGlobalBounds())) {
						obj->sprite.setColor(sf::Color::Black);
					}
					else {
						obj->sprite.setColor(sf::Color::White);
					}
				}
			}
		}

	}	
}


//////////////////////////////// UPDATE ////////////////////////////////////

void MapEditor::Update(float dt)
{


	for (auto key : _mapKey) {
		for (auto obj : _map[key]) {
			obj->update();
		}
	}
	if (mouseSprite.getGlobalBounds().intersects(toolbar->toolbar.getGlobalBounds())) {
		mouseOverToolBar = true;
	}
	else {
		mouseOverToolBar = false;
	}
	this->_data->_window.setView(view);
	mousePos = getMousePos();
	this->mouseSprite.setPosition(mousePos.x, mousePos.y);
	this->mouseSpr.setPosition(mousePos.x, mousePos.y);
	this->toolbar->update();
	this->option->update();

	for (auto obj : _menuMap.objects["save"]) {
		if (obj->sprite.getGlobalBounds().intersects(mouseSprite.getGlobalBounds())) {
			obj->sprite.setColor(Color::Yellow);
		}
		else {
			obj->sprite.setColor(Color::White);
		}
	}

	for (auto obj : _menuMap.objects["exit"]) {

		if (obj->sprite.getGlobalBounds().intersects(mouseSprite.getGlobalBounds())) {

			obj->sprite.setColor(Color::Black);
		}
		else {
			obj->sprite.setColor(Color::White);
		}
	}

	for (auto obj : _menuMap.objects["resume"]) {
		if (obj->sprite.getGlobalBounds().intersects(mouseSprite.getGlobalBounds())) {
			obj->sprite.setColor(Color::Yellow);
		}
		else {
			obj->sprite.setColor(Color::White);
		}
	}
}

void MapEditor::Draw(float dt)
{
	_data->_window.clear();

	if (this->state==States::editorState) {
		_data->_window.draw(bgRect);


		for (auto key : _mapKey) {
			for (auto obj : _map[key]) {
				obj->draw(&_data->_window);
			}
		}

		_data->_window.draw(mouseSprite);
		_data->_window.draw(mouseSpr);

		if (isTileSelected && !isOptionActive && !mouseOverToolBar) {
			_data->_window.draw(selectedTile->sprite);
		}

		toolbar->draw();

		if (isOptionActive) {
			this->option->draw();
		}
	}

	if (this->state==States::menuState) {
		_menuMap.draw(&_data->_window);

		if (clock.getElapsedTime().asSeconds()<2 && triggerInfo) {
			_data->_window.draw(infoText);
		}
		else{
			triggerInfo = false;
		}
	}
	if (this->state == States::idManager) {
		_idMap.draw(&_data->_window);
		idInput.draw(_data->_window);
	}
	_data->_window.display();
}
//////////////////////////////// HANDLER WHEN EDITOR STATE IS PAUSED ////////////////////////////////////
void MapEditor::Pause()
{
}

//////////////////////////////// HANDLER WHEN EDITOR STATE IS RESUMED ////////////////////////////////////
void MapEditor::Resume()
{
}

//////////////////////////////// SELECT OBJECT IN MAP ////////////////////////////////////
void MapEditor::selectObject()
{
	bool is_object = false;
	

	for (std::vector<std::string>::reverse_iterator i = _mapKey.rbegin();
		i != _mapKey.rend(); ++i) {

	
		for (std::vector<StaticObject*>::reverse_iterator j = _map[*i].rbegin();
			j != _map[*i].rend(); ++j) {

			auto obj = *j;
			if (Collision::PixelPerfectTest(obj->sprite, mouseSpr)) {
				is_object = true;
				bool isLocked = false;
				for (auto object : lockedObjects) {

					if (obj->type == object) {
						isLocked = true;
					}

				}

				if (not isLocked) {
					if (!multiple_select) {
						for (auto selectedObject : selectedObjects) {
							selectedObject->sprite.setColor(Color::White);
						}
					}


					bool already_selected = false;

					int ind = 0;
					for (auto selectedObject : selectedObjects) {
						if (selectedObject == obj) {
							already_selected = true;
							if (multiple_select) {
								selectedObject->sprite.setColor(Color::White);
								selectedObjects.erase(selectedObjects.begin() + ind);
							}
							else {
								selectedObjects.erase(selectedObjects.begin(), selectedObjects.end());
							}

						}
						ind++;
					}

					if (!already_selected) {
						if (multiple_select) {
							selectedObjects.push_back(obj);
						}
						else {
							selectedObjects.erase(selectedObjects.begin(), selectedObjects.end());
							selectedObjects.push_back(obj);
						}
						is_selected = true;
					}
					else {
						if (!multiple_select) {
							is_selected = false;
						}
						else {
							is_selected = true;
						}
					}

					for (auto selectedObject : selectedObjects) {
						selectedObject->sprite.setColor(Color::Cyan);
					}
				}
				else {
					is_object = false;
				}

				return;
			}
		}
	}
	if (!is_object && !multiple_select ) {
		is_selected = false;
		for (auto selectedObject : selectedObjects) {
			selectedObjects.erase(selectedObjects.begin(), selectedObjects.end());
			selectedObject->sprite.setColor(Color::White);
		}
	}
}

////////////////////////////////SELECT TOOLBAR AND OBJECTS////////////////////////////////////

void MapEditor::selectToolbar()
{
	

	if (toolbar->titleRect.getGlobalBounds().intersects(mouseSprite.getGlobalBounds())) {
		this->isToolbarSelected = true;
	}
	else {
		this->isToolbarSelected = false;
	}

	if (isTileSelected) {
		activeBox->rect.setFillColor(Color::White);
	}

	for (auto box : toolbar->boxes) {
		if (box->rect.getGlobalBounds().intersects(mouseSprite.getGlobalBounds())) {
			if (box->isActive) {
				isTileSelected = true;
				selectedTile = new StaticObject(&_data->_asset.GetTexture(box->texture_name), Vector2f(0, 2000));
				activeBox = box;
				box->rect.setFillColor(Color::Cyan);

			}
		}
	}
}

//////////////////////////////// TOOLBAR EVENT HANDLER ////////////////////////////////////

void MapEditor::toolbarHandler(Event* event)
{
	int objShift = 15;
	if (event->key.code == sf::Keyboard::W) {
		toolbar->titleRect.move(0, -objShift);
	}

	if (event->key.code == sf::Keyboard::S) {
		toolbar->titleRect.move(0, objShift);
	}

	if (event->key.code == sf::Keyboard::D) {
		toolbar->titleRect.move(objShift, 0);
	}

	if (event->key.code == sf::Keyboard::A) {
		toolbar->titleRect.move(-objShift, 0);
	}

}



//////////////////////////////// TOOLBAR DRAG HANDLER ////////////////////////////////////

void MapEditor::toolbarDragHandler()
{
	Vector2f newPos = this->_data->_window.mapPixelToCoords(sf::Mouse::getPosition(this->_data->_window));
	toolbar->titleRect.setPosition(newPos);
}


//////////////////////////////// POPULATE TOOLBAR WITH OBJECTS FROM SETTINGS ////////////////////////////////////
void MapEditor::populateToolbar()
{
	int i = 0;
	for (auto info : this->_mapKey){

		this->toolbar->boxes[i]->rect.setFillColor(Color::White);
		this->toolbar->boxes[i]->rect.setTexture(&this->_data->_asset.GetTexture(info));
		this->toolbar->boxes[i]->texture_name = info;
		this->toolbar->boxes[i]->isActive = true;
		i++;
	}
}

//////////////////////////////// TILE OBJECTS OF MAP DRAG HANDLER ////////////////////////////////////
void MapEditor::tileDragHandler()
{
	Vector2f newPos = this->_data->_window.mapPixelToCoords(sf::Mouse::getPosition(this->_data->_window));
	selectedTile->sprite.setPosition(newPos);
}

//////////////////////////////// HANDLER WHEN TILE OBJECTS FROM TOOLBAR IS DROPPED INTO MAP ////////////////////////////////////
void MapEditor::dropTileHandler()
{
	Vector2f newPos = this->_data->_settings.GetMousePosition(this->_data->_window);
	std::cout << newPos.x << "," << newPos.y<<std::endl;
	StaticObject* obj = new StaticObject(&_data->_asset.GetTexture(activeBox->texture_name), newPos, activeBox->texture_name);
	obj->id = "0";
	std::cout << obj->id;
	_map[activeBox->texture_name].push_back(obj);
}

//////////////////////////////// HANDLER FOR DELETING OBJECTS FROM MAP ////////////////////////////////////
void MapEditor::deleteObject()
{
	if (is_selected) {
		for (auto object : selectedObjects) {
			_map[object->type].erase(std::remove(_map[object->type].begin(), _map[object->type].end(), object));
		}
	}
	is_selected = false;
}

//////////////////////////////// FUNCTION THAT SWAPS ORDER OF OBEJCTS IN MAPKEY ////////////////////////////////////
void MapEditor::swapToolbarObject(std::string name, int type)
{
	if (type == 1) {
		//pushing object backwards in vector//
		int pos = find(_mapKey.begin(), _mapKey.end(), name) - _mapKey.begin();
		if (pos != 0) {
			std::string temp = _mapKey[pos - 1];
			_mapKey[pos - 1] = _mapKey[pos];
			_mapKey[pos] = temp;
		}
	}
	if (type == 2) {
		//pushing object forward in vector//
		int pos = find(_mapKey.begin(), _mapKey.end(), name) - _mapKey.begin();
		if (pos != _mapKey.size() - 1) {
			std::string temp = _mapKey[pos + 1];
			_mapKey[pos + 1] = _mapKey[pos];
			_mapKey[pos] = temp;
		}
	}
}


//////////////////////////////// HANDLER FOR RIGHT CLICK OPTION  ////////////////////////////////////
void MapEditor::optionRightClickHandler()
{
	bool flag = false;
	for (auto box : toolbar->boxes) {
		if (box->rect.getGlobalBounds().intersects(mouseSprite.getGlobalBounds())) {
			if (box->isActive) {
				isOptionActive = true;
				activeBox = box;
				option->setPosition(getMousePos());
				flag = true;
			}
		}
	}

	if (!flag) {
		isOptionActive = false;
	}
}


//////////////////////////////// HANDLER FOR LEFT CLICK OPTION  ////////////////////////////////////
void MapEditor::optionLeftClickHandler()
{
	for (auto obj : option->rect) {
		if (obj.second->getGlobalBounds().intersects(mouseSprite.getGlobalBounds())) {
			if (obj.first == "swap back") {
				swapToolbarObject(activeBox->texture_name, 1);
			}
			if (obj.first == "swap forward") {
				swapToolbarObject(activeBox->texture_name, 2);
			}
			if (obj.first == "lock") {
				if (!activeBox->isLocked) {
					activeBox->isLocked = true;
					lockedObjects.push_back(activeBox->texture_name);
				}
				
			}

			if (obj.first=="unlock") {
				lockedObjects.erase(std::remove(lockedObjects.begin(),lockedObjects.end(),activeBox->texture_name),lockedObjects.end());
				activeBox->isLocked = false;
			}

			if (obj.first == "settings") {
				_data->_machine.AddState(sg::StateRef(new ObjectSetupEditor(_data,&this->objectSettings,activeBox->texture_name)),false);
			}

			updateToolbar(activeBox->texture_name);
		}
	}


	isOptionActive = false;

}

void MapEditor::updateToolbar(std::string name)
{
	int i = 0;
	for (auto info : this->_mapKey) {
		this->toolbar->boxes[i]->rect.setTexture(&this->_data->_asset.GetTexture(info));
		Vector2u* size = &this->_data->_asset.GetTexture(info).getSize();
		this->toolbar->boxes[i]->rect.setTextureRect(IntRect(0, 0, size->x, size->y));
		this->toolbar->boxes[i]->texture_name = info;

		if (name == info) {
			activeBox = this->toolbar->boxes[i];
		}
		i++;
	}
}

void MapEditor::save()
{
	std::ofstream file;
	file.open(_dir + this->_filename + ".txt");


	for (auto name : _mapKey) {
		file << "@" << name << "# ";
	}

	file << std::endl;
	for (auto info : _map) {
		if (info.second.size() != 0) {
			file << info.first << "# ";
			file << "{" << this->objectSettings[info.first].first << "," << this->objectSettings[info.first].second.left << "," << this->objectSettings[info.first].second.top << "," << this->objectSettings[info.first].second.width << "," << this->objectSettings[info.first].second.height << "} ";
			for (auto obj : info.second) {
				file << "(" << obj->sprite.getPosition().x << "," << obj->sprite.getPosition().y << ") ";
				file << "[" << obj->id << "] ";
			}
			file << std::endl;
		}

	}
}


//////////////////////////////// RETURNS MOUSE POSITION ////////////////////////////////////
Vector2f MapEditor::getMousePos()
{
	Vector2f newPos = this->_data->_window.mapPixelToCoords(sf::Mouse::getPosition(this->_data->_window));
	return newPos;
}


//////////////////////////////// HANDLER FOR CHANGING VIEW POSITION WITH RESPECT TO MOUSE POS ////////////////////////////////////
void MapEditor::mouseMovementHandler()
{
	Vector2f newPos = this->_data->_settings.GetMousePosition(this->_data->_window);
	float x = mousePos.x - newPos.x;
	float y = mousePos.y - newPos.y;
	view.move(x, y);
}

//////////////////////////////// HANDLER FOR DRAGGING OBJECTS OVER MAP ////////////////////////////////////
void MapEditor::objectMouseDragHandler()
{
	Vector2f newPos = this->_data->_window.mapPixelToCoords(sf::Mouse::getPosition(this->_data->_window));
	float x = mousePos.x - newPos.x;
	float y = mousePos.y - newPos.y;
	if (selectedObjects.size() == 1) {
		selectedObjects[0]->sprite.setPosition(mousePos);
	}
	for (auto selectedObject : selectedObjects) {
		selectedObject->sprite.move(-x, -y);
	}
}



