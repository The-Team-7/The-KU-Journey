#include "Conversation.h"

namespace sg {

	void Conversation::startConvo(std::string filename, GameDataRef data)
	{
		/*
		if (buffer.loadFromFile(NARRATOR_sound)) {
		sb.setBuffer(buffer);
		}
		*/
		this->clock = new sf::Clock();
		count = 0;
		this->animationComplete = false;

		this->_data = data;
		dialogue.loadDialogueFile(filename);
		dialogueManager.startDialogue(dialogue);
		this->setDisplayConversation(true);
	}
	void Conversation::setDisplayConversation(bool true_or_false)
	{
		this->displayConversation = true_or_false;
	}
	bool Conversation::getDisplayConversation()
	{
		return displayConversation;
	}
	void Conversation::next()
	{
		//if (this->animationComplete) {
		if (this->getDisplayConversation() == true) {
			this->convoBox.lineString = dialogueManager.getNextSentence();
			cp = dialogueManager.getCharacterProperty();
			this->convoBox.nameString = this->cp.name;
			setConvoBox();
			this->displayConversation = !dialogueManager.getSceneFinished();
		}
		this->clock->restart();
		count = 0;
		d = "";
		//}
	}

	void Conversation::draw()
	{
		if (this->getDisplayConversation() == true) {
			this->_data->_window.draw(this->convoBox.background);
			this->_data->_window.draw(this->convoBox.avatar);
			this->_data->_window.draw(this->convoBox.nameText);

			if (this->clock->getElapsedTime().asSeconds() >= 0.05f && count <= this->convoBox.lineString.length()) {
				count++;
				if (this->convoBox.lineString.substr(count - 1, 4) == "<br>") {
					count += 4;
					d = d + "\n";
				}
				else {
					d = d + this->convoBox.lineString.substr(count - 1, 1);
				}


				this->convoBox.lineText.setString(d);
				this->clock->restart();
			}
			if (count == this->convoBox.lineString.length()) {
				this->animationComplete = true;
			}
			this->_data->_window.draw(this->convoBox.lineText);
		}
	}
	void Conversation::setConvoBox()
	{
		sf::IntRect rect(0, 0, this->_data->_asset.GetTexture(cp.background).getSize().x, this->_data->_asset.GetTexture(cp.background).getSize().y);
		this->convoBox.background.setTextureRect(rect);
		this->convoBox.background.setTexture(this->_data->_asset.GetTexture(cp.background));

		sf::IntRect dpRect(0, 0, this->_data->_asset.GetTexture(cp.avatar).getSize().x, this->_data->_asset.GetTexture(cp.avatar).getSize().y);
		this->convoBox.avatar.setTextureRect(dpRect);
		this->convoBox.avatar.setTexture(this->_data->_asset.GetTexture(cp.avatar));

		this->convoBox.nameText.setFont(this->_data->_asset.GetFont(cp.font));
		this->convoBox.lineText.setFont(this->_data->_asset.GetFont(cp.font));

		this->convoBox.nameText.setCharacterSize(cp.fontSize);
		this->convoBox.lineText.setCharacterSize(cp.fontSize - 15);

		this->convoBox.nameText.setFillColor(sf::Color::White);
		this->convoBox.lineText.setFillColor(cp.color);
		if (this->cp.name != CH_0) {
			this->convoBox.background.setPosition(0,0 /*SCREEN_HEIGHT - this->convoBox.background.getGlobalBounds().height*/);
			this->convoBox.avatar.setPosition(SCREEN_WIDTH - this->convoBox.avatar.getGlobalBounds().width - 10, SCREEN_HEIGHT - this->convoBox.avatar.getGlobalBounds().height - 10);
			this->convoBox.nameText.setPosition(this->convoBox.background.getPosition().x + this->cp.position.x, this->convoBox.background.getPosition().y + this->cp.position.y);
			this->convoBox.lineText.setPosition(this->convoBox.background.getPosition().x + 100, this->convoBox.nameText.getPosition().y + 100);
			this->convoBox.nameText.setString(this->convoBox.nameString);
		}
		else {
			this->convoBox.background.setPosition(0, 0);
			this->convoBox.avatar.setPosition(SCREEN_WIDTH / 2 - this->convoBox.avatar.getGlobalBounds().width / 2, 100);
			//this->convoBox.nameText.setPosition(this->convoBox.background.getPosition().x + this->cp.position.x, this->convoBox.background.getPosition().y + this->cp.position.y);
			this->convoBox.lineText.setPosition(this->convoBox.avatar.getPosition().x, this->convoBox.avatar.getPosition().y + this->convoBox.avatar.getGlobalBounds().height + 30);
		}
	}
}

