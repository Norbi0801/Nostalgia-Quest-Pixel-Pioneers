//
// Created by Norbert Olkowski on 30.11.2023.
//

#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>
#include "../Event/Event.hpp"
#include "../Window/Window.hpp"

namespace State {

    enum class StateType {
        Intro = 1, MainMenu, Game, Paused, GameOver, Credits
    };

    struct SharedContext {
        SharedContext() : m_wind(nullptr), m_eventManager(nullptr) {}

        Window::Window *m_wind;
        Event::EventManager *m_eventManager;
    };

    class StateManager;

    class BaseState {
        friend class StateManager;

    public:
        explicit BaseState(StateManager *l_stateManager)
                : m_stateMgr(l_stateManager), m_transparent(false),
                  m_transcendent(false) {}

        virtual ~BaseState() = default;

        virtual void OnCreate() = 0;

        virtual void OnDestroy() = 0;

        virtual void Activate() = 0;

        virtual void Deactivate() = 0;

        virtual void Update(const sf::Time &l_time) = 0;

        virtual void Draw() = 0;

        void SetTransparent(const bool &l_transparent) {
            m_transparent = l_transparent;
        }

        [[nodiscard]] bool IsTransparent() const { return m_transparent; }

        void SetTranscendent(const bool &l_transcendence) {
            m_transcendent = l_transcendence;
        }

        [[nodiscard]] bool IsTranscendent() const { return m_transcendent; }

        StateManager *GetStateManager() { return m_stateMgr; }

        sf::View& GetView(){ return m_view; }
    protected:
        StateManager *m_stateMgr;
        bool m_transparent;
        bool m_transcendent;
        sf::View m_view;
    };

    using StateContainer = std::vector<std::pair<StateType, BaseState *>>;
    using TypeContainer = std::vector<StateType>;
    using StateFactory = std::unordered_map<StateType, std::function<BaseState *(void)>>;

    class StateManager {
    public:
        explicit StateManager(SharedContext *l_shared);

        ~StateManager();

        void Update(const sf::Time &l_time);

        void Draw();

        void ProcessRequests();

        SharedContext *GetContext();

        bool HasState(const StateType &l_type);

        void SwitchTo(const StateType &l_type);

        void Remove(const StateType &l_type);

    private:
        void CreateState(const StateType &l_type);

        void RemoveState(const StateType &l_type);

        template<class T>
        void RegisterState(const StateType &l_type) {
            m_stateFactory[l_type] = [this]() -> BaseState * {
                return new T(this);
            };
        }

        SharedContext *m_shared;
        StateContainer m_states;
        TypeContainer m_toRemove;
        StateFactory m_stateFactory;
    };

}