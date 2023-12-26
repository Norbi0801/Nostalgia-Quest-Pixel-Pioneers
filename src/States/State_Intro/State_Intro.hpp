//
// Created by Norbert Olkowski on 26.12.2023.
//

#pragma once

#include "Core/State/State.hpp"

namespace State {
    class State_Intro : public BaseState{
    public:
        void OnCreate() override;

        void OnDestroy();

        void Activate();

        void Deactivate();

        void Update(const sf::Time &l_time);

        void Draw();

        void Continue(Event::EventDetails* l_details);
    private:
        sf::Texture m_introTexture;
        sf::Sprite m_introSprite;
        sf::Text m_text;
        sf::Font m_font;
        float m_timePassed;
    };
}