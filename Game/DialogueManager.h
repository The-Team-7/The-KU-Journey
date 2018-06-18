#pragma once
#include "Dialogue.h"
#include<queue>
#include<string>
#include<map>
namespace sg {

	class DialogueManager
	{
	public:
		void Start();
		void startDialogue(Dialogue& dialogue);
		std::string getNextSentence();				//call if it doesnt return eod
		std::string getName();
		std::string displayAllDialogue();
	private:
		std::string name;
		stringQueue dialogue;
		bool sceneFished;
	};

}

