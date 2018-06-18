#include "InputManager.h"
#include <SFML\Graphics.hpp>

namespace sg {
	InputManager::InputManager()
	{
	}

	InputManager::~InputManager()
	{
	}

	bool InputManager::isSpriteClicked(sf::Sprite obj, sf::Mouse::Button button, sf::RenderWindow &window) {

		if (sf::Mouse::isButtonPressed(button)) {
			sf::IntRect rect(obj.getPosition().x, obj.getPosition().y, obj.getGlobalBounds().width, obj.getGlobalBounds().height);
			if (rect.contains(sf::Mouse::getPosition(window))) {
				return true;
			}
		}
		return false;

	}
	sf::Vector2i InputManager::getMousePos(sf::RenderWindow &window) {

		return sf::Mouse::getPosition(window);
	}
}
