#include "Assets.hpp"

#include <iostream>
#include <filesystem>

using namespace engine;


/**
 * @brief	Relative path from executable to assets folder
*/
const std::string Assets::ASSETS_PATH = "../../../assets/";



// Class static variables //
std::map<const std::string, const sf::Font, std::less<>> Assets::_fonts;
std::map<const std::string, const sf::SoundBuffer, std::less<>> Assets::_soundBuffers;
std::map<const std::string, const sf::Texture, std::less<>> Assets::_textures;



////////////
// Public //
////////////
const sf::Font& Assets::getFont(const std::string_view& name) {
	if (auto it = _fonts.find(name); it != _fonts.end()) {
		return it->second;
	}
	std::cerr << "\nAssets: The following font could not be found: \"" << name << "\"\n";
	return _fonts.begin()->second;
}

sf::Sound Assets::getSound(const std::string_view& name) {
	if (auto it = _soundBuffers.find(name); it != _soundBuffers.end()) {
		return sf::Sound(it->second);
	}
	std::cerr << "\nAssets: The following sound could not be found: \"" << name << "\"\n";
	return sf::Sound{};
}

const sf::Texture& Assets::getTexture(const std::string_view& name) {
	if (auto it = _textures.find(name); it != _textures.end()) {
		return it->second;
	}
	std::cerr << "\nAssets: The following texture could not be found: \"" << name << "\"\n";
	return _textures.begin()->second;
}


///////////////////////
// Loaders (Helpers) //
///////////////////////
int Assets::loadFont(const std::string& name, const std::string& filePath) {
	if (_fonts.contains(name)) {
		std::cerr
			<< "\nAssets: Failed loading font \"" << name << "\" from '" << filePath
			<< "', as one with the same name is already loaded.\n";
	}
	else {
		if (sf::Font tmp; tmp.loadFromFile(filePath)) {
			_fonts.try_emplace(name, tmp);
		}
		else {
			return 1;
		}
	}

	return 0;
}

int Assets::loadSoundBuffer(const std::string& name, const std::string& filePath) {
	if (_soundBuffers.contains(name)) {
		std::cerr
			<< "\nAssets: Failed loading sound buffer \"" << name << "\" from '" << filePath
			<< "', as one with the same name is already loaded.\n";
	}
	else {
		if (sf::SoundBuffer tmp; tmp.loadFromFile(filePath)) {
			_soundBuffers.try_emplace(name, tmp);
		}
		else {
			return 1;
		}
	}

	return 0;
}

int Assets::loadTexture(const std::string& name, const std::string& filePath) {
	if (_textures.contains(name)) {
		std::cerr
			<< "\nAssets: Failed loading texture \"" << name << "\" from '" << filePath
			<< "', as one with the same name is already loaded.\n";
	}
	else {
		if (sf::Texture tmp; tmp.loadFromFile(filePath)) {
			_textures.try_emplace(name, tmp);
		}
		else {
			return 1;
		}
	}

	return 0;
}


//////////////////////////////////////
// Load assets from 'assets' folder //
//////////////////////////////////////
int Assets::load() {
	// Load fonts
	for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(Assets::ASSETS_PATH + "fonts/")) {
		if (!dir_entry.is_directory()) {
			auto path = dir_entry.path();
			auto filePath = path.generic_string();
			auto name = path.replace_extension("").generic_string().substr((Assets::ASSETS_PATH + "fonts/").length());

			if (loadFont(name, filePath) != 0) {
				return 1;
			}
		}
	}
	if (_fonts.empty()) {
		_fonts.try_emplace("Empty" /* emplacing a default constructed object */);
	}

	// Load sounds
	for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(Assets::ASSETS_PATH + "sounds/")) {
		if (!dir_entry.is_directory()) {
			auto path = dir_entry.path();
			auto filePath = path.generic_string();
			auto name = path.replace_extension("").generic_string().substr((Assets::ASSETS_PATH + "sounds/").length());

			if (loadSoundBuffer(name, filePath) != 0) {
				return 1;
			}
		}
	}

	// Load textures
	for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(Assets::ASSETS_PATH + "textures/")) {
		if (!dir_entry.is_directory()) {
			auto path = dir_entry.path();
			auto filePath = path.generic_string();
			auto name = path.replace_extension("").generic_string().substr((Assets::ASSETS_PATH + "textures/").length());

			if (loadTexture(name, filePath) != 0) {
				return 1;
			}
		}
	}
	if (_textures.empty()) {
		_textures.try_emplace("Empty" /* emplacing a default constructed object */);
	}
	
	return 0;
}
