//
// Created by Norbert Olkowski on 08.12.2023.
//

#include "Tile.hpp"

namespace Tile {

    TileInfo::TileInfo(State::SharedContext *l_context, const std::string &l_texture, TileID l_id)
            : m_context(l_context), m_id(0), m_deadly(false) {
        Texture::TextureManager *tmgr = l_context->m_textureManager;
        if (l_texture.empty()) {
            m_id = l_id;
            return;
        }
        if (!tmgr->RequireResource(l_texture)) { return; }
        m_texture = l_texture;
        m_id = l_id;
        m_sprite.setTexture(*tmgr->GetResource(m_texture));
        sf::IntRect tileBoundaries(m_id %
                                   (Sheet::Sheet_Width / Sheet::Tile_Size) * Sheet::Tile_Size,
                                   m_id / (Sheet::Sheet_Height / Sheet::Tile_Size) * Sheet::Tile_Size,
                                   Sheet::Tile_Size, Sheet::Tile_Size);
        m_sprite.setTextureRect(tileBoundaries);
    }

    TileInfo::~TileInfo() {
        if (m_texture.empty()) { return; }
        m_context->m_textureManager->ReleaseResource(m_texture);
    }

}