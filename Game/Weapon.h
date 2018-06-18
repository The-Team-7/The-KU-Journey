#pragma once
#include "LoadingState.h"
#include "Game.h"
#include "DEFINITIONS.h"
#include "Enums.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <chrono> 
#include <map>
#include <cmath>

namespace sg {
	typedef sf::Sprite Bullet;
	class Weapon
	{
	public:
		Weapon(GameDataRef data, Enums::WeaponType type);
		~Weapon();
		void setWeapon();
		void fire(Enums::facing direction);
		void reload();
		bool checkDistanceTravelled(int i);
		void updateBullet(Bullet * bullet, int i);
		void update();
		
		/*void destroyBullet();
		void checkCollision();
		
		int damage;
		Player weaponWielder;
		sf::Text gunState*/


	private:
		Enums::WeaponType _type;
		GameDataRef _data;
		Bullet* bullet;
		std::vector<Bullet> bulletArray;
		std::vector<Enums::facing> bulletDirection;
		std::vector<sf::Vector2f> bulletPosition;
		std::thread reloadThread;

	//characterstics of the weapon
	private:
		int range;											  //range of bullet
		int bulletSpeed;
		int clips;											// current Bullet		
		int magSize;									   // maximum clip size
		int ammo;										  // total bullets
		int bulletFired;								 // total bullets fired 
		float reloadTime;

	//state of the weapon
	private:
		bool reloading;
		bool haveBullets;

	};
}
