//
// Created by Norbert Olkowski on 03.12.2023.
//
#pragma once

#include "SFML/Graphics/Texture.hpp"
#include "../Resource/Resource.hpp"

namespace Texture {

    class TextureManager :
            public Resource::ResourceManager<TextureManager, sf::Texture> {
    public:
        TextureManager();

        sf::Texture *Load(const std::string &l_path);
    };

}
