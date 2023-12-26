//
// Created by Norbert Olkowski on 26.12.2023.
//

#pragma once

#include "Core/State/State.hpp"

namespace State {
    class State_MainMenu : public BaseState{
    public:
        State_MainMenu(StateManager *pManager);

        void OnCreate() override;

        void OnDestroy();

        void Activate();

        void Deactivate();

        void Update(const sf::Time &l_time);

        void Draw();

        void MouseClick(Event::EventDetails* l_details);
    private:
        sf::Text m_text;
        sf::Font m_font;
        sf::Vector2f m_buttonSize;
        sf::Vector2f m_buttonPos;
        unsigned int m_buttonPadding;
        sf::RectangleShape m_rects[3];
        sf::Text m_labels[3];
    };
}