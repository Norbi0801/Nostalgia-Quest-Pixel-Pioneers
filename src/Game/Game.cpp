//
// Created by Norbert Olkowski on 17.12.2023.
//

#include "Game.hpp"

Game::Game(): m_window("Chapter 2", sf::Vector2u(800,600)),m_entityManager(&m_systemManager, &m_textureManager),
              m_stateManager(&m_context){
    m_systemManager.SetEntityManager(&m_entityManager);
    m_context.m_systemManager = &m_systemManager;
    m_context.m_entityManager = &m_entityManager;
    m_context.m_wind = &m_window;
    m_context.m_eventManager = &m_window.GetEventManager();
    m_stateManager.SwitchTo(State::StateType::Intro);
}

Game::~Game() = default;

void Game::Update(){
    m_window.Update();
}

void Game::Render(){
    m_window.BeginDraw();
   /* m_window.Draw();*/
    m_window.EndDraw();
}

sf::Time Game::GetElapsed(){ return m_elapsed; }
void Game::RestartClock(){
    m_elapsed += m_clock.restart();
}

Window::Window *Game::GetWindow() {
    return &m_window;
}
