#include "Line.h"
#include<iostream>
namespace sg {

	void Dialogue::loadDialogueFile(std::string filePath)
	{
		this->hasEndDialogue = false;
		std::string line;
		std::string name;
		file.open(filePath);
		if (file.is_open()) {
			std::cout << "file loaded";
			while (!file.eof()) {
				getline(file, line);
				if (line == "<Karun>") {
					name = CH_1;
				}
				else if (line == "<Bijay>") {
					name = CH_2;
				}
				else if (line == "<Prabhat>") {
					name = CH_3;
				}
				else if (line == "<Anup>") {
					name = CH_4;
				}
				else if (line == "<Narrator>") {
					name = CH_0;
				}
				else if (line == "<ed>") {
					this->name_dialogue.insert(std::make_pair(name, dialogue));
					this->name_dialogue_Queue.push(this->name_dialogue);
					this->name_dialogue.clear();
					while (!this->dialogue.empty()) {
						this->dialogue.pop();
					}
				}
				else {
					dialogue.push(line);
					std::cout << "dialogue pushed of " << name << std::endl;
				}
				if (line == "<repeatingDialogue>") {
					getline(file, line);
					this->hasEndDialogue = true;
					this->endDialoue = line;
				}
			}
		}
		else {
			std::cout << "scene file not loaded";
		}
		file.close();
	}

	Dialogue::~Dialogue()
	{
	}
	std::string Dialogue::getEndDialogue()
	{
		return this->endDialoue;
	}
	DialogueMap Dialogue::getDialogue()
	{
		DialogueMap name_dialogue_from_queue;

		if (!this->name_dialogue_Queue.empty()) {
			name_dialogue_from_queue = this->name_dialogue_Queue.front();
			this->name_dialogue_Queue.pop();
		}
		return name_dialogue_from_queue;
	}
	bool Dialogue::ifHasEndDialogue()
	{
		return this->hasEndDialogue;
	}
}