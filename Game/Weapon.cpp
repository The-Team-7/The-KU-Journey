#include "Weapon.h"


namespace sg {
	Weapon::Weapon(GameDataRef data, Enums::WeaponType type):_data(data)
	{
		this->_type = type;
		this->setWeapon();
	}
	Weapon::~Weapon()
	{
	}
	void Weapon::setWeapon()
	{
		//inserting the bullets
		switch (this->_type) {
		case(Enums::WeaponType::plasmaGun): {
			this->_data->_asset.LoadTexture("plasma_gun", PLASMA_BULLET_TEXTURE);

			this->range = 800;
			this->bulletSpeed = 1;
			this->clips = 20;
			this->magSize = 20;
			this->ammo = 120;
			this->bulletFired = 0;
			this->reloadTime = 2.0f;

			this->reloading = false;
			this->haveBullets = true;
		}
		}
	}

	void Weapon::fire(Enums::facing direction)		//this code is to be removed
	{
		//std::cout << "ullets:"<<;
		if (!this->reloading && this->haveBullets) {
			bullet = new Bullet();
			bullet->setTexture(this->_data->_asset.getTexture("plasma_gun"));
			bullet->setPosition(sf::Mouse::getPosition(this->_data->_window).x, sf::Mouse::getPosition(this->_data->_window).y);

			bulletArray.push_back(*bullet);
			bulletPosition.push_back(bulletArray.back().getPosition());
			bulletDirection.push_back(direction);				//change the right value latter

			++bulletFired;
			if (!--clips) {
				reloadThread = std::thread (&Weapon::reload,this);
				reloadThread.detach();
			}
			if (ammo <= 0 && clips <= 0) {
				haveBullets = false;
			}
		}
	}

	void Weapon::reload()
	{
		int initAmmo = ammo;
		this->reloading = true;
		std::this_thread::sleep_for(std::chrono::seconds(int(this->reloadTime)));
		this->reloading = false;
		ammo -= (magSize - clips);
		clips += initAmmo - ammo;
	}

	bool Weapon::checkDistanceTravelled(int i)					//return if range is crossed
	{
		
		sf::Vector2f initPosition = bulletPosition.at(i);
		sf::Vector2f currentPosition = bulletArray.at(i).getPosition();

		float distance = std::sqrt(std::pow(currentPosition.x - initPosition.x, 2) + 
									std::pow(currentPosition.y - initPosition.y, 2));

		if (distance >= this->range) {
			return true;
		}
			return false;
	}

	void Weapon::updateBullet(Bullet* bullet, int i)				//update position of bullet
	{
		switch (bulletDirection.at(i)) {
		case(Enums::facing::left): {
			bullet->move(-1*this->bulletSpeed,0);
			break;
		}
		case(Enums::facing::right): {
			bullet->move(this->bulletSpeed, 0);
			break;
		}
		case(Enums::facing::up): {
			bullet->move(0, -1 * this->bulletSpeed);
			break;
		}
		case(Enums::facing::down): {
			bullet->move(0, this->bulletSpeed);
			break;
		}
		}	
	}

	void Weapon::update() 
	{
		for (int i = 0; i < bulletArray.size(); i++) {
			this->updateBullet(&bulletArray[i], i);
			/*if (this->checkDistanceTravelled(i)){
				this->bulletArray.erase(bulletArray.begin()+i);
				continue;
			}*/

			this->_data->_window.draw(bulletArray[i]);
		}
	}
}
