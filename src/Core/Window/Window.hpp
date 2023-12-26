//
// Created by Norbert Olkowski on 03.12.2023.
//
#pragma once

#include "SFML/Graphics.hpp"
#include "Core/Event/Event.hpp"
#include <string>

namespace Window {

    class Window{
    public:
        Window();
        Window(const std::string& l_title,const sf::Vector2u& l_size);
        ~Window();
        void BeginDraw();
        void EndDraw();
        void Update();
        bool IsDone() const;
        bool IsFullscreen() const;
        sf::Vector2u GetWindowSize();
        void ToggleFullscreen();
        void Draw(sf::Drawable& l_drawable);
        sf::RenderWindow& GetRenderWindow();
        sf::FloatRect GetViewSpace();
        bool IsFocused();
        Event::EventManager& GetEventManager();
        void ToggleFullscreen(Event::EventDetails* l_details);
        void Close(Event::EventDetails* l_details = nullptr);

    private:
        void Setup(const std::string& l_title, const sf::Vector2u& l_size);
        void Destroy();
        void Create();
        sf::RenderWindow m_window;
        sf::Vector2u m_windowSize;
        std::string m_windowTitle;
        bool m_isDone{};
        bool m_isFullscreen{};
        Event::EventManager m_eventManager;
        bool m_isFocused;
    };

}