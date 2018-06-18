#include "Dialogue.h"
#include<iostream>
namespace sg{

	Dialogue::Dialogue(std::string filePath)
	{
		std::string line;
		std::string name;
		file.open(filePath);
		if (file.is_open()) {
			std::cout << "file loaded";
			while (!file.eof()) {
				getline(file, line);
				if (line == "[ch1]") {
					name = "Karun";
				}
				else if(line == "[ch2]") {
					name = "Bijay";
				}
				else if (line == "[ch3]") {
					name = "Prabhat";
				}
				else if (line == "[ed]") {
					this->name_dialogue.insert(std::make_pair(name, dialogue));
					this->name_dialogue_Queue.push(this->name_dialogue);
					this->name_dialogue.clear();
					while (!this->dialogue.empty()) {
						this->dialogue.pop();
					}
				}
				else {
					dialogue.push(line);
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
	DialogueMap Dialogue::getDialogue()
	{
		DialogueMap d;
		if (!this->name_dialogue_Queue.empty()) {
			d = this->name_dialogue_Queue.front();
			this->name_dialogue_Queue.pop();
		}
		return d;
	}
}