#include "DialogueManager.h"

namespace sg {

	void DialogueManager::Start()
	{
		
	}

	void DialogueManager::startDialogue(Dialogue& dialogue)
	{

		for (auto& s: dialogue.getDialogue()) {
			this->name = s.first;
			this->dialogue = s.second;
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
			s = "[eod]";
		}
		return s;
	}

	std::string DialogueManager::getName()
	{

		return this->name;
	}

	std::string DialogueManager::displayAllDialogue()
	{
		std::string s;
		while (!this->dialogue.empty()) {
			s +="\n" + this->dialogue.front();
			this->dialogue.pop();
		}

		s += "[eod]";
		return s;
	}
	
}

