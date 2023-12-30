//
// Created by Norbert Olkowski on 30.12.2023.
//

#pragma once

#include "Components/Base/ComponentBase.hpp"

namespace Component {

    class State : public Base {
    public:
        State(): Base(ECS::Component::State){}
        void ReadIn(std::stringstream& l_stream) override{
            unsigned int state = 0;
            l_stream >> state;
            m_state = (ECS::EntityState)state;
        }
        ECS::EntityState GetState(){ return m_state; }
        void SetState(const ECS::EntityState& l_state){
            m_state = l_state;
        }

    private:
        ECS::EntityState m_state;
    };
}