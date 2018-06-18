#pragma once
#include "Object.h"
#include"SFML\Graphics.hpp"

using namespace sf;

class Object
{
public:
	Object(Texture* tex, Vector2u dim, Vector2f pos);
	Object(Texture* tex, Vector2f pos);
	Object(Texture* tex, IntRect rect, Vector2f pos);
	Object();
	~Object();

public:

	enum framerate {
		low = 7,
		normal = 10,
		high = 45
	};

	enum shiftMode {
		slow = 7,
		fast = 15
	};

	enum moves {
		up, down, left, right
	};

	enum state {
		moving, still
	};
	enum face {
		a, d, w, s
	};
public:
	state state;
	face facing;
	Clock * clock;
	Texture* tex;
	Sprite sprite;
	IntRect rect;
	float speed;
	int row;
	int col;
	Vector2u objSize;
	Vector2u dim;
	Vector2f init_pos;
	int rate;
	int shift;
	float restTime;
	int spiriteSetup[4];
	Clock* speed_clock;

public:
	virtual void update(RenderWindow* win) = 0;
	virtual void move(moves m) = 0;
	void setDim(Vector2u dim);
	void setManualFrameRate(int s);
	void setFrameRate(framerate s);
	void setShift(int d);
	void setMode(Object::shiftMode m);
	void setManualShift(int s);
	void setRestTime(float t);
	void setSpirite(int u, int d, int l, int r);
	void setPosition(Vector2f pos);
};