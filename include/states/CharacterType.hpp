#pragma once

#include "engine/Assets.hpp"

enum CharacterType {
    BOY, GIRL, GRANDPA, DOGE
};

static const std::string characterTextures[] = {
        "Figures/blu",
        "Figures/gren",
        "Figures/red",
        "Figures/yelow"
};

inline sf::Texture& getCharacterTexture(CharacterType type) {
    return engine::Assets::getTexture(characterTextures[type]);
}