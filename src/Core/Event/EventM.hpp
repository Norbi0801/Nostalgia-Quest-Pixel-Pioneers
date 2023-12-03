//
// Created by Norbert Olkowski on 28.11.2023.
//
#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <functional>
#include "../State/StateM.hpp"

namespace EventM {

/*
   The following code is derived from the book "SFML Game Development By Example".
   See detailed explanation in Chapter 4, Page 73.
*/

    enum class EventType {
        KeyDown = sf::Event::KeyPressed,
        KeyUp = sf::Event::KeyReleased,
        MButtonDown = sf::Event::MouseButtonPressed,
        MButtonUp = sf::Event::MouseButtonReleased,
        MouseWheel = sf::Event::MouseWheelMoved,
        WindowResized = sf::Event::Resized,
        GainedFocus = sf::Event::GainedFocus,
        LostFocus = sf::Event::LostFocus,
        MouseEntered = sf::Event::MouseEntered,
        MouseLeft = sf::Event::MouseLeft,
        Closed = sf::Event::Closed,
        TextEntered = sf::Event::TextEntered,
        Keyboard = sf::Event::Count + 1, Mouse, Joystick
    };

    struct EventInfo {
        EventInfo();

        explicit EventInfo(int l_event);

        union {
            int m_code;
        };
    };

    using Events = std::vector<std::pair<EventType, EventInfo>>;

    struct EventDetails {
        explicit EventDetails(const std::string &l_bindName);

        std::string m_name;
        sf::Vector2i m_size;
        sf::Uint32 m_textEntered{};
        sf::Vector2i m_mouse;
        int m_mouseWheelDelta{};
        int m_keyCode{};

        void Clear();
    };

    struct Binding {
        explicit Binding(const std::string &l_name);

        void BindEvent(EventType l_type, EventInfo l_info = EventInfo());

        Events m_events;
        std::string m_name;
        int c;
        EventDetails m_details;
    };

    using Bindings = std::unordered_map<std::string, Binding *>;

    template<class T>
    struct Callback{
        std::string m_name;
        T *CallbackInstance;

        void (T::*_callback)();

        void Call() {
            CallbackInstance->*_callback();
        }
    };

    using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
    using Callbacks = std::unordered_map<StateM::StateType, CallbackContainer>;

    class EventManager {
    public:
        EventManager();

        ~EventManager();

        bool AddBinding(Binding *l_binding);

        bool RemoveBinding(const std::string &l_name);

        void SetFocus(const bool &l_focus);

        template<class T>
        bool AddCallback(StateM::StateType l_state, const std::string& l_name, void(T::*l_func)(EventDetails*), T* l_instance){
            auto itr = m_callbacks.emplace(
                    l_state, CallbackContainer()).first;
            auto temp = std::bind(l_func, l_instance, std::placeholders::_1);
            return itr->second.emplace(l_name, temp).second;
        }

        bool RemoveCallback(StateM::StateType l_state, const std::string& l_name);

        void HandleEvent(sf::Event &l_event);

        void Update();

        static sf::Vector2i GetMousePos(sf::RenderWindow *l_wind = nullptr);

        void SetCurrentState(const StateM::StateType &type);

    private:
        void LoadBindings();

        Bindings m_bindings;
        Callbacks m_callbacks;
        StateM::StateType m_currentState;
        bool m_hasFocus;
    };

}