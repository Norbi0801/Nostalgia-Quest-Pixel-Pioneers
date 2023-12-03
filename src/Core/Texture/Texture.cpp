//
// Created by Norbert Olkowski on 03.12.2023.
//

#include "Texture.hpp"

namespace Texture {
    sf::Texture *TextureManager::Load(const std::string &l_path) {
        auto *texture = new sf::Texture();
        if (!texture->loadFromFile(
                Utils::GetWorkingDirectory() + l_path)) {
            delete texture;
            texture = nullptr;
            std::cerr << "! Failed to load texture: "
                      << l_path << std::endl;
        }
        return texture;
    }

    TextureManager::TextureManager() : ResourceManager("textures.cfg") {}
}