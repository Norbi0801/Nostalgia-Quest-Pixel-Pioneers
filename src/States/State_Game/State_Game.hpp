//
// Created by Norbert Olkowski on 17.12.2023.
//

#pragma once

#include "Core/State/BaseState.hpp"
#include "Core/Event/Event.hpp"

namespace State {

    class State_Game : public BaseState {
    public:
        State_Game(StateManager *pManager);

        void OnCreate() override;

        void OnDestroy();

        void Activate();

        void Deactivate();

        void Update(const sf::Time &l_time);

        void Draw();

        void MainMenu(Event::EventDetails *l_details);

        void Pause(Event::EventDetails *l_details);

    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Vector2f m_increment;
        Map::Map* m_gameMap;
    };
}