#pragma once
#include"State.h"
#include"Game.h"
#include"MapLoader.h"
#include"StaticObject.h"
#include"Toolbar.h"
#include"Options.h"


class MapEditor :public sg::State
{
public:

	enum Type {
		create,
		load
	};

	enum States {
		editorState,
		menuState
	};


	MapEditor(sg::GameDataRef _data, Type type, std::string filename);
	~MapEditor();

	// Inherited via State
	virtual void Init() override;

	virtual void HandleInput() override;

	virtual void Update(float dt) override;

	virtual void Draw(float dt) override;

	virtual void Pause() override;

	virtual void Resume() override;

private:
	void selectObject();
	void mouseMovementHandler();
	void objectMouseDragHandler();
	void selectToolbar();
	void toolbarHandler(Event* event);
	void toolbarDragHandler();
	void populateToolbar();
	void tileDragHandler();
	void dropTileHandler();
	void deleteObject();
	void swapToolbarObject(std::string name, int type);
	void optionRightClickHandler();
	void optionLeftClickHandler();
	void updateToolbar(std::string name);
	void save();
	Vector2f getMousePos();

private:
	States state;
	Toolbar * toolbar;
	std::string _filename;
	Type _type;
	std::map<std::string, std::vector<StaticObject*>> _map;
	Map _menuMap;
	std::vector<std::string> _mapKey;
	sg::MapLoader _maploader;
	std::string _dir;
	sf::Clock clock;
	sf::View view;
	sg::GameDataRef _data;
	sf::RectangleShape bgRect;
	sf::Vector2f mapSize;
	sf::RectangleShape mouseSprite;
	std::vector<std::string> lockedObjects;
	std::vector<StaticObject*> selectedObjects;
	sf::Sprite mouseSpr;
	Object* selectedTile;
	Toolbar::box* activeBox;
	Options* option;
	Vector2f mousePos;
	Text infoText;
	bool triggerInfo;
	bool isOptionActive;
	bool mouseClicked;
	bool is_selected;
	bool altPressed;
	bool isToolbarSelected;
	bool object_being_dragged;
	bool multiple_select;
	float zoom;
	bool isTileSelected;
	bool mouseOverToolBar;

};

