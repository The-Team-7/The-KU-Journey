#include "LineManager.h"

namespace sg {
	DialogueManager::DialogueManager()
	{
		this->setCharacterProperty();
	}
	void DialogueManager::startDialogue(Dialogue& dialogue)
	{
		this->dial = &dialogue;
		for (auto& s : dialogue.getDialogue()) {
			this->name = s.first;
			std::cout << std::endl << this->name << "in start diaogue\n";
			this->dialogue = s.second;
		}
		if (this->dialogue.empty()) {
			this->sceneFished = true;
			if (dialogue.ifHasEndDialogue()) {
				this->endDilogue = dialogue.getEndDialogue();
			}
			else {
				this->endDilogue = "i dont have end dialogue";
			}
		}
		else {
			this->sceneFished = false;
		}

	}

	CharacterProperty DialogueManager::getCharacterProperty()
	{
		if (this->name == CH_1) {
			return karun;
		}
		if (this->name == CH_2) {
			return bijay;
		}
		if (this->name == CH_3) {
			return prabhat;
		}
		if (this->name == CH_4) {
			return anup;
		}
		if (this->name == CH_0) {
			return narrator;
		}
	}

	std::string DialogueManager::getNextSentence()
	{
		std::string s;
		if (!this->dialogue.empty()) {
			s = this->dialogue.front();
			this->dialogue.pop();
		}
		else {
			if (!this->sceneFished) {
				startDialogue(*dial);
				std::cout << "\n self call \n";
				return getNextSentence();
			}
		}
		if (this->sceneFished) {
			s = this->endDilogue;
		}
		return s;
	}
	bool DialogueManager::getSceneFinished()
	{
		return this->sceneFished;
	}
	void DialogueManager::setCharacterProperty()
	{
		this->narrator.font = "narratorFont";
		this->narrator.animationType = "Typewriter";
		this->narrator.name = CH_0;
		this->narrator.fontSize = 60;
		this->narrator.color = sf::Color::White;
		this->narrator.background = "bg-Narrator";
		this->narrator.avatar = "avatar-Narrator";
		this->narrator.position = sf::Vector2i(600, 300);

		this->karun.font = "prabhatFont";
		this->karun.animationType = "Typewriter";
		this->karun.name = CH_1;
		this->karun.fontSize = 60;
		this->karun.color = sf::Color::White;
		this->karun.background = "dialogueBox-Karun";
		this->karun.avatar = "avatar-Karun";
		this->karun.position = sf::Vector2i(100, 20);

		this->bijay.font = "bijayFont";
		this->bijay.animationType = "Typewriter";
		this->bijay.name = CH_2;
		this->bijay.fontSize = 60;
		this->bijay.color = sf::Color::White;
		this->bijay.background = "dialogueBox-Bijay";
		this->bijay.avatar = "avatar-Bijay";
		this->bijay.position = sf::Vector2i(100, 20);

		this->prabhat.font = "prabhatFont";
		this->prabhat.animationType = "Typewriter";
		this->prabhat.name = CH_3;
		this->prabhat.fontSize = 60;
		this->prabhat.color = sf::Color::White;
		this->prabhat.background = "dialogueBox-Prabhat";
		this->prabhat.avatar = "avatar-Prabhat";
		this->prabhat.position = sf::Vector2i(100, 20);

		this->anup.font = "anupFont";
		this->anup.animationType = "Typewriter";
		this->anup.name = CH_4;
		this->anup.fontSize = 60;
		this->anup.color = sf::Color::White;
		this->anup.background = "dialogueBox-Anup";
		this->anup.avatar = "avatar-Anup";
		this->anup.position = sf::Vector2i(100, 20);
	}

}

