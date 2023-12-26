//
// Created by Norbert Olkowski on 26.12.2023.
//

#pragma once

#include "Core/State/State.hpp"

namespace State {
    class State_Paused : public BaseState{
    public:
        State_Paused(StateManager *pManager);

        void OnCreate() override;

        void OnDestroy();

        void Activate();

        void Deactivate();

        void Update(const sf::Time &l_time);

        void Draw();
        void Unpause(Event::EventDetails* l_details);
    private:
        sf::Text m_text;
        sf::Font m_font;
        sf::RectangleShape m_rect;
    };
}