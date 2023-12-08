//
// Created by Norbert Olkowski on 08.12.2023.
//

#pragma once

#include "../../Core/State/State.hpp"
#include "../Tile/Tile.hpp"
#include <unordered_map>

namespace Map {
    using TileMap = std::unordered_map<Tile::TileID, Tile::Tile *>;
    using TileSet = std::unordered_map<Tile::TileID, Tile::TileInfo *>;

    class Map {
    public:
        Map(State::SharedContext *l_context, State::BaseState *l_currentState);

        ~Map();

        Tile::Tile *GetTile(unsigned int l_x, unsigned int l_y);

        Tile::TileInfo *GetDefaultTile();

        float GetGravity() const;

        unsigned int GetTileSize() const;

        const sf::Vector2u &GetMapSize() const;

        const sf::Vector2f &GetPlayerStart() const;

        void LoadMap(const std::string &l_path);

        void LoadNext();

        void Update(float l_dT);

        void Draw();

    private:
        unsigned int ConvertCoords(unsigned int l_x, unsigned int l_y) const;

        void LoadTiles(const std::string &l_path);

        void PurgeMap();

        void PurgeTileSet();

        TileSet m_tileSet;
        TileMap m_tileMap;
        sf::Sprite m_background;
        Tile::TileInfo m_defaultTile;
        sf::Vector2u m_maxMapSize;
        sf::Vector2f m_playerStart;
        unsigned int m_tileCount;
        unsigned int m_tileSetCount;
        float m_mapGravity;
        std::string m_nextMap;
        bool m_loadNextMap;
        std::string m_backgroundTexture;
        State::BaseState *m_currentState;
        State::SharedContext *m_context;
    };
}