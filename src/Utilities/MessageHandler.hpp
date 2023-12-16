//
// Created by Norbert Olkowski on 16.12.2023.
//

#pragma once

#include <unordered_map>
#include "Observer.hpp"
#include "Core/ECS/ECS.hpp"
#include "Communicator.hpp"

using Subscribtions = std::unordered_map<ECS::EntityMessage,Communicator>;

class MessageHandler{
public:
    bool Subscribe(const ECS::EntityMessage& l_type,
                   Observer* l_observer)
    {
        return m_communicators[l_type].AddObserver(l_observer);
    }
    bool Unsubscribe(const ECS::EntityMessage& l_type,
                     Observer* l_observer)
    {
        return m_communicators[l_type].RemoveObserver(l_observer);
    }
    void Dispatch(const Message& l_msg){
        auto itr = m_communicators.find(
                (ECS::EntityMessage)l_msg.m_type);
        if (itr == m_communicators.end()){ return; }
        itr->second.Broadcast(l_msg);
    }
private:
    Subscribtions m_communicators;
};