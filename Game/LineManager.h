#pragma once
#include<SFML/Graphics.hpp>
#include "Line.h"
#include<queue>
#include<string>
#include<map>
namespace sg {
	struct CharacterProperty {
		std::string font;
		std::string animationType;
		std::string name;
		int fontSize;
		sf::Color color;
		std::string background;
		std::string avatar;
		sf::Vector2i position;
	};
	class DialogueManager
	{
	public:
		DialogueManager();
		void startDialogue(Dialogue& dialogue);
		CharacterProperty getCharacterProperty();
		std::string getNextSentence();				//call if it doesnt return eod
		bool getSceneFinished();
	private:
		void setCharacterProperty();

	private:
		CharacterProperty narrator;
		CharacterProperty prabhat;
		CharacterProperty bijay;
		CharacterProperty karun;
		CharacterProperty anup;
		Dialogue* dial;
		std::string endDilogue;
		std::string name;
		stringQueue dialogue;
		bool sceneFished;
	};

}

