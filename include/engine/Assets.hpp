#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


namespace engine {

	class Core;

	/**
	 * @brief	Class for managing assets. Acts as an API for sf::Font, sf::Sound and sf::Texture.
	 *			Place your asset inside its respectable asset folder to be loaded automatically.
	 *			SUPPORTED FILE FORMATS:
	 *				fonts: TrueType, Type 1, CFF, OpenType, SFNT, X11 PCF, Windows FNT, BDF, PFR and Type 42
	 *				sounds: WAV, OGG/Vorbis and FLAC
	 *				textures: bmp, png, tga, jpg, gif, psd, hdr and pic
	*/
	class Assets {
	public:
        static const std::string ASSETS_PATH;

		/**
		 * @brief	Getter for fonts. Returns reference to first font stored inside the class if one with the given name doesn't exist.
		 * @param name	Name of the font
		 * @return	Reference to font
		*/
		static const sf::Font& getFont(const std::string_view& name);
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
		static sf::Texture& getTexture(const std::string_view& name);


	private:
		//////////
		// Core //
		//////////
		friend Core;
		/**
		 * @brief	Reads and stores global assets from the corresponding files.
		 * @return	0 - in case of success
		*/
		static int load();

		// Helper functions //
		static int loadFont(const std::string& name, const std::string& filePath);
		static int loadSoundBuffer(const std::string& name, const std::string& filePath);
		static int loadTexture(const std::string& name, const std::string& filePath);



		///////////////
		// Variables //
		///////////////

		static std::map<const std::string, const sf::Font, std::less<>> _fonts;
		static std::map<const std::string, const sf::SoundBuffer, std::less<>> _soundBuffers;
		static std::map<const std::string, sf::Texture, std::less<>> _textures;
	};

}
