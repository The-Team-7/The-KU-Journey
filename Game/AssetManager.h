#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<map>



namespace sg {

	/////////////////////////THIS CLASS MANAGES ALL THE ASSETS IN THE GAME///////////////////////

	class AssetManager
	{
	public:

		////////THIS FUNCTION LOADS TEXTURE FROM FILE AND STORES IT IN A MAP WITH A SPECIFIC NAME//////
		void LoadTexture(std::string textureName, std::string fileName);

		////////THIS FUNCTION RETURNS A TEXTURE REFERENCE STORED IN THE MAP WITH A SPECIFIC NAME/////
		sf::Texture &GetTexture(std::string textureName);

		///////THIS FUNCTION RETURNS A TEXTURE POINTER//////
		sf::Texture * GetTexturePointer(std::string textureName);

		////////THIS FUNCTION LOADS FONT FROM FILE AND STORES IT IN A MAP WITH A SPECIFIC NAME//////
		void LoadFont(std::string fontName, std::string fileName);

		////////THIS FUNCTION RETURNS A FONT REFERENCE STORED IN THE MAP WITH A SPECIFIC NAME/////
		sf::Font &GetFont(std::string fontName);

		////////THIS FUNCTION LOADS SOUND FROM FILE AND STORES IT IN A MAP WITH A SPECIFIC NAME//////
		void LoadSoundBuffer(std::string bufferName, std::string fileName);

		////////THIS FUNCTION RETURNS A SOUNDBUFFER REFERENCE STORED IN THE MAP WITH A SPECIFIC NAME/////
		sf::SoundBuffer &GetSoundBuffer(std::string bufferName);
		
		

	private:
		std::map<std::string, sf::Texture> textureMap;
		std::map<std::string, sf::Font> fontMap;
		std::map<std::string, sf::SoundBuffer> soundMap;
		
	};

}