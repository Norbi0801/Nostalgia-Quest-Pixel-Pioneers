//
// Created by Norbert Olkowski on 30.11.2023.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "SharedContext.hpp"
#include <unordered_map>
#include "BaseState.hpp"

namespace State {

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