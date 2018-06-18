#pragma once
#include <SFML\Graphics.hpp>
namespace sg {
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		bool isSpriteClicked(sf::Sprite obj, sf::Mouse::Button button, sf::RenderWindow &window);
		sf::Vector2i getMousePos(sf::RenderWindow &window);

	};
}
