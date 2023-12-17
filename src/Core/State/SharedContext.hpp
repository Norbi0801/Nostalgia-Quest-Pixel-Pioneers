//
// Created by Norbert Olkowski on 08.12.2023.
//

#pragma once

#include "../Window/Window.hpp"
#include "../Texture/Texture.hpp"
#include "../Event/Event.hpp"
#include "Core/System/System.hpp"

namespace Map{
  class Map ;
}

namespace State{
    struct SharedContext {
        SharedContext() : m_wind(nullptr), m_eventManager(nullptr), m_textureManager(nullptr), m_gameMap(nullptr),m_systemManager(nullptr),
                          m_entityManager(nullptr) {}

        Window::Window *m_wind;
        Event::EventManager *m_eventManager;
        Texture::TextureManager *m_textureManager;
        Map::Map *m_gameMap;
        System::SystemManager* m_systemManager;
        Entity::EntityManager* m_entityManager;
    };
}