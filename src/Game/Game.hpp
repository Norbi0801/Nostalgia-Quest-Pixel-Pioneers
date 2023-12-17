//
// Created by Norbert Olkowski on 17.12.2023.
//

#pragma once

#include "Core/Window/Window.hpp"
#include "Core/System/System.hpp"

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
private:
    Window::Window m_window;
    sf::Clock m_clock;
    sf::Time m_elapsed;
    double frametime;
    System::SystemManager m_systemManager;
    Entity::EntityManager m_entityManager;
};