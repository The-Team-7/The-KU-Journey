#include "Player.h"
#include<iostream>



Player::Player()
{
	init();
}


Player::~Player()
{

}

void Player::init()
{
	std::string dir = ASSETS_DIR;
	this->texture.loadFromFile(dir+"character.png");
	this->sprite.setTexture(texture);
	this->canJump = false;
	this->isFalling = false;
	this->isJumping = false;
	this->liftForce = 6;
	this->gravity =0.3;
	this->xVel = 0;
	this->yVel = 0;
	this->jumpVel = -12;
	moveup = true;
	movedown = true;
	moveleft = true;
	moveright = true;

	dim.x = 13;
	dim.y = 21;
	objSize = texture.getSize();
	objSize.x /= dim.x;
	objSize.y /= dim.y;
	row = 0;
	col = 0;
	rect.left = objSize.x*col;
	rect.top = objSize.y*row;
	rect.width = objSize.x;
	rect.height = objSize.y;
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	sprite.setScale(sf::Vector2f(2,2));

	shift = 4;
}

void Player::moveAnimation(moves m)
{
	if (m == moves::up) {
		row = 8;
		maxCol = 8;
		face = moves::up;
	}
	if (m == moves::down) {
		row = 10;
		maxCol = 8;
		face = moves::down;
	}
	if (m == moves::left) {
		row = 9;
		maxCol = 8;
		face = moves::left;
	}
	if (m == moves::right) {
		row =11 ;
		maxCol = 8;
		face = moves::right;
	}
	if (col==maxCol) {
		col = 1;
	}
	else {
		col++;
	}

	rect.top = objSize.y*row;
	rect.left = objSize.x*col;
	sprite.setTextureRect(rect);
}

void Player::dynamicAnimation()
{
	if (animationClock.getElapsedTime().asMilliseconds()>18.0f) {
		if (aCol == aMaxCol) {
			aCol = 1;
			animationState = none;
			animationIsOn = false;
		}
		else {
			aCol++;
		}
		rect.top = objSize.y*aRow;
		rect.left = objSize.x*aCol;
		sprite.setTextureRect(rect);
		animationClock.restart();
	}
}

void Player::animate(animation state)
{
	animationState = state;
	;
	animationIsOn = true;
	if (animationState == animation::shooting) {
		if (face == moves::up and moveup) {
			aRow = 16; aMaxCol = 12; aCol = 0;
		}
		if (face == moves::down and movedown) {
			aRow = 18; aMaxCol = 12; aCol = 0;
		}
		if (face == moves::left and moveleft) {
			aRow = 17; aMaxCol = 12; aCol = 0;
		}
		if (face == moves::right and moveright) {
			aRow = 19; aMaxCol = 12; aCol = 0;
		}
	}
	if (animationState == animation::spellcast) {
		if (face == moves::up) {
			aRow = 0; aMaxCol = 6; aCol = 0;
		}
		if (face == moves::down) {
			aRow = 2; aMaxCol = 6; aCol = 0;
		}
		if (face == moves::left) {
			aRow = 1; aMaxCol = 6; aCol = 0;
		}
		if (face == moves::right) {
			aRow = 3; aMaxCol = 6; aCol = 0;
		}
	}
	if (animationState == animation::slash) {
		if (face == moves::up) {
			aRow = 12; aMaxCol = 5; aCol = 0;
		}
		if (face == moves::down) {
			aRow = 14; aMaxCol = 5; aCol = 0;
		}
		if (face == moves::left) {
			aRow = 13; aMaxCol = 5; aCol = 0;
		}
		if (face == moves::right) {
			aRow = 15; aMaxCol = 5; aCol = 0;
		}
	}
	if (animationState == animation::thrust) {
		if (face == moves::up) {
			aRow = 4; aMaxCol = 7; aCol = 0;
		}
		if (face == moves::down) {
			aRow = 6; aMaxCol = 7; aCol = 0;
		}
		if (face == moves::left) {
			aRow = 5; aMaxCol = 7; aCol = 0;
		}
		if (face == moves::right) {
			aRow = 7; aMaxCol = 7; aCol = 0;
		}
	}
	if (animationState == animation::none) {
		aRow = 0; aCol = 0; aMaxCol=0;
	}

}


void Player::draw(RenderWindow& win)
{
	win.draw(this->sprite);
}

void Player::update()
{
	if (animationState!=animation::none and animationIsOn==true) {
		dynamicAnimation();
	}
	updateMotion();

	if (jumpClock.getElapsedTime().asMilliseconds()>10 && canJump==false){
		isJumping=true;
	}
	else {
		isJumping = false;
	}
}

void Player::setPosition(Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::move(moves m)
{
	if (m == Player::moves::up && moveup) {

		if (isJumping) {
			
		}
		else {
			sprite.move(0, -shift);
			moveAnimation(m);
			face = up;
		}
		
	}
	if (m == Player::moves::down && movedown) {
		if (isJumping) {
		}
		else {
			sprite.move(0, shift);
			moveAnimation(m);
			face = down;
		}
	}
	if (m == Player::moves::left && moveleft) {
		
		if (isJumping && xVel==0) {
			row = 9;
			col = 0;
			face = moves::left;
			rect.top = objSize.y*row;
			rect.left = objSize.x*col;
			sprite.setTextureRect(rect);
		}
		else {
			sprite.move(-shift, 0);
			moveAnimation(m);
			face = left;
		}

	}
	if (m == Player::moves::right && moveright) {
		if (isJumping && xVel == 0) {
			row = 11;
			col= 1;
			face = moves::right;
			rect.top = objSize.y*row;
			rect.left = objSize.x*col;
			sprite.setTextureRect(rect);
		}
		else {
			sprite.move(shift, 0);
			moveAnimation(m);
			face = right;
		}
	}
}

void Player::shoot()
{

}

void Player::updateMotion()
{
	if ((isFalling)) {
		yVel = yVel + gravity;
	}

	if (motionClock.getElapsedTime().asMilliseconds()>30.0f) {
		Vector2f newPos = this->sprite.getPosition();
		xDir = newPos.x - pos.x;
		yDir = newPos.y - pos.y;
		pos = newPos;
	}

	if (restrictX && restrictY) {
		sprite.move(0,0);
	}
	else if (restrictX) {
		sprite.move(0, yVel);
	}
	else if (restrictY) {
		sprite.move(xVel,0);
	}
	else {
		sprite.move(xVel,yVel);
	}
	
	



}

void Player::setToFallingState()
{
	this->isFalling = true;
	this->canJump = false;
	this->isJumping = false;

}

void Player::setToGroundState()
{
	yVel = 0;
	xVel = 0;
	this->canJump = true;
	this->isFalling = false;
	this->isJumping = false;

}

void Player::jump()
{
	if (canJump && !isFalling) {
		jumpClock.restart();
		yVel = jumpVel;

		

		if (xDir>0 and face==moves::right) {
			xVel = liftForce;
		}
		else if (xDir<0 and face == moves::left) {
			xVel =-liftForce;
		}

		canJump = false;
		isFalling = true ;
	}
}


