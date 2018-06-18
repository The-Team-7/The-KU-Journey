#pragma once
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
		Dialogue(std::string filePath);
		~Dialogue();

		DialogueMap getDialogue();
	private:
		std::ifstream file;

		stringQueue dialogue;
		DialogueMap	name_dialogue;
		std::queue<DialogueMap> name_dialogue_Queue;
	};
}