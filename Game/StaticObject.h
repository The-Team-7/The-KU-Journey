#pragma once
#include"Object.h"
#include<sfml/Graphics.hpp>
class StaticObject :public Object
{
public:
	StaticObject(Texture* tex, Vector2f pos);
	StaticObject(Texture* tex, Vector2f pos, std::string type_name);
	StaticObject(Texture* tex, IntRect rect, Vector2f pos);

public:

	virtual void update(RenderWindow * win) override;
	virtual void move(moves m) override;

public:
	std::string type;


};

