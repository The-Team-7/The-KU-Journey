#pragma once
#include "Game.h"
#include "LineManager.h";
#include "Line.h"
#include <string>
#include<SFML/Graphics.hpp>

namespace sg {
	class Conversation
	{
	public:
		void startConvo(std::string filename, GameDataRef data);
		void setDisplayConversation(bool true_or_false);
		bool getDisplayConversation();
		void next();
		void draw();
	private:
		void setConvoBox();
	private:
		struct ConvoBox {
			sf::Sprite background;
			sf::Sprite avatar;
			std::string nameString;
			std::string lineString;
			sf::Text nameText;
			sf::Text lineText;
		};
		GameDataRef _data;

		Dialogue dialogue;
		DialogueManager dialogueManager;
		CharacterProperty cp;
		ConvoBox convoBox;
		bool displayConversation;
		bool sceneFinished;

		sf::SoundBuffer buffer;
		sf::Sound sb;
		sf::Clock* clock;
		int count;
		std::string d;
		bool animationComplete;
	};
}