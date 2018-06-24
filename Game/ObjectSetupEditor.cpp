#include "ObjectSetupEditor.h"




ObjectSetupEditor::ObjectSetupEditor(sg::GameDataRef& _data,std::map<std::string, std::pair<int, sf::FloatRect>>* objectSettings,std::string entity)
{
	this->_data = _data;
	this->objectSettings = objectSettings;
	this->entity = entity;
	this->tex = _data->_asset.GetTexture(entity);
	this->body.setTexture(&tex);
	this->body.setSize(sf::Vector2f(700,400));
	this->scale = sf::Vector2f(700.0f/tex.getSize().x, 400.0f / tex.getSize().y);
	this->body.setOutlineThickness(3);
	this->body.setOutlineColor(sf::Color::Magenta);
	this->body.setPosition(100, 100);
	map = this->_data->_maploader.loadMap("objectsettingeditor",&this->_data->_asset);
	input3 = *new InputBox(Vector2f(1200,50), "s", "text", "Name");
	input1 = *new InputBox(Vector2f(1200,140 ), "s", "number", "Depth");
	scalex = *new InputBox(Vector2f(1200,230), "s", "text", "Scale-X");
	scaley = *new InputBox(Vector2f(1200,320), "s", "text", "Scale-Y");
	xValue= *new InputBox(Vector2f(1200, 410), "s", "text", "X-Pos");
	yValue= *new InputBox(Vector2f(1200, 490),"s", "text", "Y-Pos");;
	rectheightValue= *new InputBox(Vector2f(1200,580), "s", "text", "RectH");;
	rectwidthValue= *new InputBox(Vector2f(1200,670), "s", "text", "RectW");;
	texheightValue= *new InputBox(Vector2f(1200,760), "s", "text", "TexH");;
	texwidthValue= *new InputBox(Vector2f(1200,850), "s", "text", "TexW");;
	i1 = *new InterSectionBound(Vector2f(100+(700/2),100+(400/2)));
	i1.setMaxSize(Vector2f(700,400));
	shift = 7;
	i1.shift = shift;	
	texH = this->tex.getSize().y;
	texW = this->tex.getSize().x;
}

ObjectSetupEditor::~ObjectSetupEditor()
{
}

void ObjectSetupEditor::Init()
{
	this->_data->_settings.SetViewToNormal(this->_data->_window);
	std::string dep = std::to_string((*this->objectSettings)[this->entity].first); 
	this->depth = std::stoi(dep);
	input1.text.setString(dep);
	input1.inputData = dep;
	input3.inputData = this->entity;
	scalex.inputData = std::to_string(this->scale.x);
	scaley.inputData = std::to_string(this->scale.y);
	xValue.inputData = std::to_string(xpos);
	yValue.inputData = std::to_string(ypos);
	texheightValue.inputData = std::to_string(texH);
	texwidthValue.inputData = std::to_string(texW);
	rectheightValue.inputData = std::to_string(rectH);
	rectwidthValue.inputData = std::to_string(rectW);
	updateData();

	if ((*this->objectSettings)[this->entity].second.width!=0 && (*this->objectSettings)[this->entity].second.height!=0) {
		loadData();
	}
}

void ObjectSetupEditor::HandleInput()
{

}

void ObjectSetupEditor::Update(float dt)
{

	sf::Event event;
	while (_data->_window.pollEvent(event)) {
		if (event.type == sf::Event::MouseMoved) {
			for (auto button:map.objects["save"]) {
				if(button->sprite.getGlobalBounds().intersects(this->_data->_settings._mouse.getGlobalBounds())) {
					button->sprite.setColor(sf::Color::Black);
					isSaveButtonActive = true;
				}
				else {
					isSaveButtonActive = false;
					button->sprite.setColor(sf::Color::White);
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.key.code==sf::Mouse::Left) {
				if (isSaveButtonActive) {
					(*this->objectSettings)[entity].first = std::stoi(input1.getString());
					(*this->objectSettings)[entity].second = this->intersectionRect;
				}

				if (i1.rect.getGlobalBounds().intersects(this->_data->_settings._mouse.getGlobalBounds())) {
					i1.isActive = true;
				}
				else {
					i1.isActive = false;
				}

			}
			if (event.key.code == sf::Mouse::Right) {
				i1.isActive = false;
			}
		}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code==Keyboard::LAlt) {
				isAltPressed = true;
			}
			if (i1.isActive) {

				if (isAltPressed) {
					
					if (event.key.code == Keyboard::Up) {
						i1.resize("upShrink");
					}
					if (event.key.code == Keyboard::Down) {
						i1.resize("downShrink");
					}
					if (event.key.code == Keyboard::Right) {
						i1.resize("rightShrink");
					}
					if (event.key.code == Keyboard::Left) {
						i1.resize("leftShrink");
					}

				}
				else {
					if (event.key.code == Keyboard::Up && checkBound("upside")) {
						i1.resize("upGrow");
					}
					if (event.key.code == Keyboard::Down && checkBound("downside")) {
						i1.resize("downGrow");
					}
					if (event.key.code == Keyboard::Right && checkBound("rightside")) {
						i1.resize("rightGrow");
					}
					if (event.key.code == Keyboard::Left && checkBound("leftside")) {
						i1.resize("leftGrow");
					}
					
				}
				
				if (event.key.code == Keyboard::W && checkBound("upside")) {
					i1.move("up");
				}
				if (event.key.code == Keyboard::S && checkBound("downside")) {
					i1.move("down");
				}
				if (event.key.code == Keyboard::A && checkBound("leftside")) {
					i1.move("left");
				}
				if (event.key.code == Keyboard::D && checkBound("rightside")) {
					i1.move("right");
				}
				updateData();
			}
			if (event.key.code == Keyboard::Escape) {
				_data->_machine.RemoveState();
			}
		}

		if (event.type==Event::KeyReleased) {
			if (event.key.code==Keyboard::LAlt) {
				isAltPressed = false;
			}
		}



		input1.update(event,_data->_settings._mouse);
		input2.update(event, _data->_settings._mouse);
		i1.update();
	}
}

void ObjectSetupEditor::Draw(float dt)
{
	
	_data->_window.clear();
	this->map.draw(&_data->_window);
	_data->_window.draw(this->body);
	input1.draw(_data->_window);
	input3.draw(_data->_window);
	scalex.draw(_data->_window);
	scaley.draw(_data->_window);
	xValue.draw(_data->_window);
	yValue.draw(_data->_window);
	texheightValue.draw(_data->_window);
	texwidthValue.draw(_data->_window);
	rectheightValue.draw(_data->_window);
	rectwidthValue.draw(_data->_window);
	_data->_window.draw(i1.rect);
	_data->_window.display();

}

bool ObjectSetupEditor::checkBound(std::string type)
{
	if (type=="rightside") {
		if ((this->i1.rect.getPosition().x + this->i1.rect.getGlobalBounds().width+shift) < this->body.getPosition().x + this->body.getGlobalBounds().width) {
			return true;
		}
		else {
			return false;
		}
	}
	if (type == "leftside") {
		if ((this->i1.rect.getPosition().x-shift)> this->body.getPosition().x) {
			return true;
		}
		else {
			return false;
		}
	}
	if (type == "upside") {
		if ((this->i1.rect.getPosition().y -shift)>this->body.getPosition().y) {
			return true;
		}
		else {
			return false;
		}
	}
	if (type == "downside") {
		if ((this->i1.rect.getPosition().y + this->i1.rect.getGlobalBounds().height+shift) < this->body.getPosition().y + this->body.getGlobalBounds().height) {
			return true;
		}
		else {
			return false;
		}
	}
}

void ObjectSetupEditor::updateData()
{
	xpos = (i1.rect.getPosition().x - body.getPosition().x)/scale.x;
	ypos= (i1.rect.getPosition().y - body.getPosition().y)/scale.y;
	rectH = i1.rect.getSize().y/scale.y;
	rectW = i1.rect.getSize().x/scale.x;
	xValue.inputData = std::to_string(xpos);
	yValue.inputData = std::to_string(ypos);
	rectheightValue.inputData = std::to_string(rectH);
	rectwidthValue.inputData= std::to_string(rectW);
	intersectionRect.left = xpos;
	intersectionRect.top = ypos;
	intersectionRect.width = rectW;
	intersectionRect.height = rectH;
	depth= std::stoi(input1.getString());

}

void ObjectSetupEditor::loadData()
{
	float x = this->body.getPosition().x + ((*this->objectSettings)[this->entity].second.left)*(this->scale.x);
	float y = this->body.getPosition().y + (*this->objectSettings)[this->entity].second.top*(this->scale.y);
	float height = ((*this->objectSettings)[this->entity].second.height)*(this->scale.y);
	float width= ((*this->objectSettings)[this->entity].second.width)*(this->scale.x);
	this->i1.setPosition(Vector2f(x,y));
	this->i1.rect.setSize(Vector2f(width,height));
	updateData();

}
