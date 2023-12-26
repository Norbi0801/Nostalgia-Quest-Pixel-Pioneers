//
// Created by Norbert Olkowski on 17.12.2023.
//

#pragma once

#include "Core/Window/Window.hpp"
#include "Core/System/System.hpp"
#include "Core/State/State.hpp"

class Game{
public:
    Game();
    ~Game();
    void HandleInput();
    void Update();
    void Render();
    Window::Window* GetWindow();
    sf::Time GetElapsed();
    void RestartClock();
    void LateUpdate();
private:
    Window::Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    double frametime;
    System::SystemManager m_systemManager;
    Entity::EntityManager m_entityManager;
    Texture::TextureManager m_textureManager;
    State::StateManager m_stateManager;
    State::SharedContext m_context;
};