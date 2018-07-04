#pragma once
#include"DEFINITIONS.h"
#include<string>
#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
#include<unordered_map>
namespace sg {
	typedef std::queue<std::string> stringQueue;
	typedef std::unordered_multimap<std::string, stringQueue> DialogueMap;
	class Dialogue
	{
	public:
		void loadDialogueFile(std::string filePath);
		~Dialogue();
		DialogueMap getDialogue();

		//if dialogue is finished. only one dialogue repeats.
		std::string getEndDialogue();
		bool ifHasEndDialogue();
	private:
		std::ifstream file;
		std::string endDialoue;
		bool hasEndDialogue;
		stringQueue dialogue;
		DialogueMap	name_dialogue;
		std::queue<DialogueMap> name_dialogue_Queue;

	};
}