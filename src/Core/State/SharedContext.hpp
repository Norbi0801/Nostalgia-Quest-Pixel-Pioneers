//
// Created by Norbert Olkowski on 08.12.2023.
//

#pragma once

#include "../Window/Window.hpp"
#include "../Texture/Texture.hpp"
#include "../Event/Event.hpp"

namespace Map{
  class Map ;
}

namespace State{
    struct SharedContext {
        SharedContext() : m_wind(nullptr), m_eventManager(nullptr), m_textureManager(nullptr), m_gameMap(nullptr) {}

        Window::Window *m_wind;
        Event::EventManager *m_eventManager;
        Texture::TextureManager *m_textureManager;
        Map::Map *m_gameMap;
    };
}