//
// Created by Norbert Olkowski on 26.12.2023.
//

#include "Core/System/System.hpp"
#include "Components/State/State.hpp"
#include "State.hpp"

namespace System {
    State::State(SystemManager* l_systemMgr)
    : Base(ECS::System::State,l_systemMgr)
{
    Bitmask req;
    req.TurnOnBit((unsigned int)ECS::Component::State);
    m_requiredComponents.push_back(req);
    m_systemManager->GetMessageHandler()->
    Subscribe(ECS::EntityMessage::Move,this);
    m_systemManager->GetMessageHandler()->
    Subscribe(ECS::EntityMessage::Switch_State,this);
}

    State::~State() = default;

    void State::Update(float l_dT){
        Entity::EntityManager* entities = m_systemManager->GetEntityManager();
        for(auto &entity : m_entities){
            Component::State* state = entities->
                    GetComponent<Component::State>(entity, ECS::Component::State);
            if(state->GetState() == ECS::EntityState::Walking){
                Message msg((MessageType)ECS::EntityMessage::Is_Moving);
                msg.m_receiver = entity;
                m_systemManager->GetMessageHandler()->Dispatch(msg);
            }
        }
    }

    void State::HandleEvent(const Entity::EntityId& l_entity,
                              const ECS::EntityEvent& l_event)
    {
        switch(l_event){
            case ECS::EntityEvent::Became_Idle:
                ChangeState(l_entity,ECS::EntityState::Idle,false);
                break;
        }
    }

    void State::Notify(const Message& l_message){
        if (!HasEntity(l_message.m_receiver)){ return; }
        ECS::EntityMessage m = (ECS::EntityMessage)l_message.m_type;
        switch(m){
            case ECS::EntityMessage::Move:
            {
                auto* state = m_systemManager->GetEntityManager()->
                        GetComponent<Component::State>(l_message.m_receiver,
                                              ECS::Component::State);
                if (state->GetState() == ECS::EntityState::Dying){ return; }
                ECS::EntityEvent e;
                if (l_message.m_int == (int)Direction::Up){
                    e = ECS::EntityEvent::Moving_Up;
                } else if (l_message.m_int == (int)Direction::Down){
                    e = ECS::EntityEvent::Moving_Down;
                } else if(l_message.m_int == (int)Direction::Left){
                    e = ECS::EntityEvent::Moving_Left;
                } else if (l_message.m_int == (int)Direction::Right){
                    e = ECS::EntityEvent::Moving_Right;
                }
                m_systemManager->AddEvent(l_message.m_receiver, (EventID)e);
                ChangeState(l_message.m_receiver,
                            ECS::EntityState::Walking,false);
            }
                break;
            case ECS::EntityMessage::Switch_State:
                ChangeState(l_message.m_receiver,
                            (ECS::EntityState)l_message.m_int,false);
                break;
        }
    }

    void State::ChangeState(const Entity::EntityId& l_entity,
                              const ECS::EntityState& l_state, const bool& l_force)
    {
        Entity::EntityManager* entities = m_systemManager->GetEntityManager();
        Component::State* state = entities->
                GetComponent<Component::State>(l_entity, ECS::Component::State);
        if (!l_force && state->GetState() == ECS::EntityState::Dying){
            return;
        }
        state->SetState(l_state);
        Message msg((MessageType)ECS::EntityMessage::State_Changed);
        msg.m_receiver = l_entity;
        msg.m_int = (int)l_state;
        m_systemManager->GetMessageHandler()->Dispatch(msg);
    }

}