//
// Created by Norbert Olkowski on 08.12.2023.
//
#pragma once

#include "../State/State.hpp"
#include "../Texture/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <string>

namespace Tile {

    enum Sheet {
        Tile_Size = 32, Sheet_Width = 256, Sheet_Height = 256
    };

    using TileID = unsigned int;

    struct TileInfo {
        explicit TileInfo(State::SharedContext *l_context,
                          const std::string &l_texture = "", TileID l_id = 0);

        ~TileInfo();

        sf::Sprite m_sprite;
        TileID m_id;
        std::string m_name;
        sf::Vector2f m_friction;
        bool m_deadly;
        State::SharedContext *m_context;
        std::string m_texture;
    };

    struct Tile {
        TileInfo *m_properties;
        bool m_warp;
    };

}