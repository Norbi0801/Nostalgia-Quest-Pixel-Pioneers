//
// Created by norbe on 10.12.2023.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "StateType.hpp"
#include "BaseState.hpp"
#include <functional>
#include <unordered_map>

namespace State {

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

        sf::View &GetView() { return m_view; }

    protected:
        StateManager *m_stateMgr;
        bool m_transparent;
        bool m_transcendent;
        sf::View m_view;
    };

    using StateContainer = std::vector<std::pair<StateType, BaseState *>>;
    using TypeContainer = std::vector<StateType>;
    using StateFactory = std::unordered_map<StateType, std::function<BaseState *(void)>>;
}