#pragma once
#include"Object.h"

class Person :public Object
{

public:
	enum Face {
		right, left, up, down
	};
	bool moveleft = true;
	bool moveright = true;
	bool moveup = true;
	bool movedown = true;
	Face face;

public:
	Person(Texture* tex, Vector2u dim, Vector2f pos);
	Person();
	~Person();
private:

	bool jumping;
	int impulse;
	int ximpulse;
	Vector2i velocity;
	bool trigger_jump;
	Clock* jumpClock;
	bool rpg_mode;


public:
	bool onground;
	void move(moves m);
	void setRPGMODE();
	void setImpulse(int impulse);
	void animateMove(int r);
	virtual void update(RenderWindow* win) override;
	void jump();
};

