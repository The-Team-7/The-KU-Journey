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

	void update();
	virtual void move(moves m) override;
	void updateBounds();
	void showIBound();
	void hideIBound();
	void showCollider();
	void hideCollider();
	void draw(RenderWindow * win);

public:
	std::string type;
	int depth;
	bool shouldShowIBound;
	bool shouldShowCollider;
	std::string id;
	FloatRect IRect;
	FloatRect ColliderRect;
	RectangleShape IBound;
	RectangleShape Collider;
};

