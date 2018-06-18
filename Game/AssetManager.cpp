#include "AssetManager.h"
#include<iostream>

namespace sg {

	void AssetManager::LoadTexture(std::string textureName, std::string fileName)
	{
		sf::Texture texture;
		if (texture.loadFromFile(fileName)) {
			textureMap[textureName] = texture;
		}

		else {
			std::cout << textureName << " texture not loaded";
		}
	}

	sf::Texture & AssetManager::GetTexture(std::string textureName)
	{
		return this->textureMap[textureName];
	}

	sf::Texture * AssetManager::GetTexturePointer(std::string textureName)
	{
		return &textureMap[textureName];
	}

	void AssetManager::LoadFont(std::string fontName, std::string fileName)
	{
		sf::Font font;
		if (font.loadFromFile(fileName)) {
			fontMap[fontName] = font;
		}
		else {
			std::cout << fontName << " font not loaded";
		}
	}

	sf::Font & AssetManager::GetFont(std::string fontName)
	{
		return this->fontMap[fontName];
	}



	void AssetManager::LoadSoundBuffer(std::string bufferName, std::string fileName)
	{
		sf::SoundBuffer sound;
		if (sound.loadFromFile(fileName)) {
			soundMap[bufferName] = sound;
			std::cout << bufferName << " buffer loaded";
		}
	}

	sf::SoundBuffer & AssetManager::GetSoundBuffer(std::string bufferName)
	{
		return this->soundMap[bufferName];
	}
}