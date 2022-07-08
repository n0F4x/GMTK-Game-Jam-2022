#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


namespace engine {

	class Core;

	/**
	 * @brief	Class for managing assets. Acts as an API.
	 *			EDIT TOP OF .CPP TO LOAD NEW GLOBAL ASSET. LOAD LOCAL ASSETS INSIDE THEIR RESPECTABLE STATE (override `State::setup()`).
	 *			Does not support sf::Music.
	*/
	class Assets {
	public:
		/////////
		// API //
		/////////
		/**
		 * @brief	Getter for fonts. Returns reference to first font stored inside the class if one with the given name doesn't exist.
		 * @param name	Name of the font
		 * @return	Reference to font
		*/
		static const sf::Font& getFont(const std::string_view& name);
		/**
		 * @brief	Getter for fonts. Returns reference to first font stored inside the class if one with the given name doesn't exist.
		 * @param name	Name of the font
		 * @return	Reference to font
		*/
		static const sf::Image& getImage(const std::string_view& name);
		/**
		 * @brief	Getter for sounds. Returns an empty sound if one with the given name doesn't exist.
		 * @param name	Name of the sound(buffer)
		 * @return	Newly created sound from buffer
		*/
		static sf::Sound getSound(const std::string_view& name);
		/**
		 * @brief	Getter for textures. Returns reference to first texture stored inside the class if one with the given name doesn't exist.
		 * @param name	Name of the texture
		 * @return	Reference to texture
		*/
		static const sf::Texture& getTexture(const std::string_view& name);


		//////////////////
		// Initializing //	Call these functions to load local assets when initializing their state.
		//////////////////
		static int loadFont(const std::string& name, const std::string& filePath);
		static int loadImage(const std::string& name, const std::string& filePath);
		static int loadSoundBuffer(const std::string& name, const std::string& filePath);
		static int loadTexture(const std::string& name, const std::string& filePath);


	private:
		//////////
		// Core //
		//////////
		friend Core;
		/**
		 * @brief	Reads and stores global assets from the corresponding files.
		 * @return	0 - in case of success
		*/
		static int load_global();



		// Variables (Global stores) //
		static std::map<const std::string, const sf::Font, std::less<>> _fonts;
		static std::map<const std::string, const sf::Image, std::less<>> _images;
		static std::map<const std::string, const sf::SoundBuffer, std::less<>> _soundBuffers;
		static std::map<const std::string, const sf::Texture, std::less<>> _textures;
	};

}
