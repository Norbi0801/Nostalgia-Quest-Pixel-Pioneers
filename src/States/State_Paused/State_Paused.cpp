//
// Created by Norbert Olkowski on 26.12.2023.
//

#include "State_Paused.hpp"

namespace State{
    void State_Paused::OnCreate(){
        SetTransparent(true); // Set our transparency flag.
        m_font.loadFromFile("arial.ttf");
        m_text.setFont(m_font);
        m_text.setString(sf::String("PAUSED"));
        m_text.setCharacterSize(14);
        m_text.setStyle(sf::Text::Bold);
        sf::Vector2u windowSize = m_stateMgr->
                GetContext()->m_wind->GetRenderWindow().getSize();
        sf::FloatRect textRect = m_text.getLocalBounds();
        m_text.setOrigin(textRect.left + textRect.width / 2.0f,
                         textRect.top + textRect.height / 2.0f);
        m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
        m_rect.setSize(sf::Vector2f(windowSize));
        m_rect.setPosition(0,0);
        m_rect.setFillColor(sf::Color(0,0,0,150));
        Event::EventManager* evMgr = m_stateMgr->
                GetContext()->m_eventManager;
        evMgr->AddCallback(StateType::Paused,"Key_P",
                           &State_Paused::Unpause,this);
    }

    void State_Paused::OnDestroy(){
        Event::EventManager* evMgr = m_stateMgr->
                GetContext()->m_eventManager;
        evMgr->RemoveCallback(StateType::Paused,"Key_P");
    }

    void State_Paused::Draw(){
        sf::RenderWindow& wind = m_stateMgr->
                GetContext()->m_wind->GetRenderWindow();
        wind.draw(m_rect);
        wind.draw(m_text);
    }

    void State_Paused::Unpause(Event::EventDetails* l_details){
        m_stateMgr->SwitchTo(StateType::Game);
    }

    void State_Paused::Activate(){}
    void State_Paused::Deactivate(){}
    void State_Paused::Update(const sf::Time &l_time) {}

    State_Paused::State_Paused(StateManager *pManager) : BaseState(pManager) {}

}