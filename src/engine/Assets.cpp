#include "Assets.hpp"

#include <iostream>

using namespace engine;


///////////		{ "<name>", "<filePath>" }
// Fonts //		Supported formats: TrueType, Type 1, CFF, OpenType, SFNT, X11 PCF, Windows FNT, BDF, PFR and Type 42
///////////		"<name>" is what you will use to access this font within the program
static const std::map<const std::string, const std::string, std::less<>> fonts = {
	//{ "test", "test.ttf" },
	//{ "test2", "../Assets/test2.ttf" }
};

////////////	{ "<name>", "<filePath>" }
// Images //	Supported formats: bmp, png, tga, jpg, gif, psd, hdr and pic
////////////	"<name>" is what you will use to get this image within the program
static const std::map<const std::string, const std::string, std::less<>> images = {
	//{ "test", "test" },
	//{ "test2", "../Assets/test2.png" }
};

//////////////////	{ "<name>", "<filePath>" }
// SoundBuffers //	Supported formats: WAV, OGG/Vorbis and FLAC
//////////////////	"<name>" is what you will use to get this sound within the program
static const std::map<const std::string, const std::string, std::less<>> soundBuffers = {
	//{ "test", "test" },
	//{ "test2", "../Assets/test2.wav" }
};

//////////////	{ "<name>", "<filePath>" }
// Textures //	Supported formats: bmp, png, tga, jpg, gif, psd, hdr and pic
//////////////	"<name>" is what you will use to access this texture within the program
static const std::map<const std::string, const std::string, std::less<>> textures = {
	//{ "test", "test" },
	//{ "test2", "../Assets/test2.png" }
};


// Class static variables //
std::map<const std::string, const sf::Font, std::less<>> Assets::_fonts;
std::map<const std::string, const sf::Image, std::less<>> Assets::_images;
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

const sf::Image& engine::Assets::getImage(const std::string_view& name) {
	if (auto it = _images.find(name); it != _images.end()) {
		return it->second;
	}
	std::cerr << "\nAssets: The following image could not be found: \"" << name << "\"\n";
	return _images.begin()->second;
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


/////////////
// Loaders //
/////////////
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

int engine::Assets::loadImage(const std::string& name, const std::string& filePath) {
	if (_images.contains(name)) {
		std::cerr
			<< "\nAssets: Failed loading image \"" << name << "\" from '" << filePath
			<< "', as one with the same name is already loaded.\n";
	}
	else {
		if (sf::Image tmp; tmp.loadFromFile(filePath)) {
			_images.try_emplace(name, tmp);
		}
		else {
			return 1;
		}
	}

	return 0;
}

int engine::Assets::loadSoundBuffer(const std::string& name, const std::string& filePath) {
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


/////////////////////////////////////////
// Load global assets from top of file //
/////////////////////////////////////////
int Assets::load_global() {
	// Load fonts
	for (auto const& [name, filePath] : fonts) {
		if (loadFont(name, filePath) != 0) {
			return 1;
		}
	}
	if (_fonts.empty()) {
		_fonts.try_emplace("Empty" /* emplacing a default constructed object */);
	}

	// Load images
	for (auto const& [name, filePath] : fonts) {
		if (loadImage(name, filePath) != 0) {
			return 1;
		}
	}
	if (_images.empty()) {
		_images.try_emplace("Empty" /* emplacing a default constructed object */);
	}

	// Load sound buffers
	for (auto const& [name, filePath] : soundBuffers) {
		if (loadSoundBuffer(name, filePath) != 0) {
			return 1;
		}
	}

	// Load textures
	for (auto const& [name, filePath] : textures) {
		if (loadTexture(name, filePath) != 0) {
			return 1;
		}
	}
	if (_textures.empty()) {
		_textures.try_emplace("Empty" /* emplacing a default constructed object */);
	}

	return 0;
}
