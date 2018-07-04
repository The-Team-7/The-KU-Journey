#pragma once
#include"StaticObject.h"
#include "DEFINITIONS.h"

#include<string>

class Player
{
	
	

public:
	Player();
	~Player();

	enum moves {
		up, down, left, right
	};

	enum animation{
		moving, jumping, shooting, spellcast, slash, thrust, none
	};

	void init();
	void moveAnimation(moves m);
	void dynamicAnimation();
	void animate(animation state);
	void draw(RenderWindow& win);
	void update();
	void setPosition(Vector2f pos);
	void move(moves m);
	void shoot();
	void updateMotion();
	void setToFallingState();
	void setToGroundState();
	void jump();



public:
	StaticObject * object;
	Sprite sprite;
	Texture texture;
	moves face;
	animation animationState ;
	Vector2u objSize;
	Vector2u dim;
	Vector2f pos;
	IntRect rect;
	Clock animationClock;
	Clock jumpClock;
	Clock motionClock;
	


	float gravity;
	float yVel;
	float xVel;
	float liftForce;
	float jumpVel;
	float xAccel;
	float shift;
	float xDir;
	float yDir;

	int row, col, maxCol;
	int aRow, aCol, aMaxCol;

	bool canJump;
	bool moveup, movedown, moveleft, moveright;
	bool animationIsOn;
	bool isFalling,isJumping;
	bool restrictX, restrictY;


	
	
	


};

