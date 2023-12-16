//
// Created by Norbert Olkowski on 16.12.2023.
//

#pragma once

#include <unordered_map>
#include "../../Systems/Base/SystemBase.hpp"
#include "../../Utilities/EventQueue.hpp"
#include "Utilities/MessageHandler.hpp"
#include "Core/Window/Window.hpp"

namespace System{
    using SystemContainer = std::unordered_map<ECS::System,System::Base*>;
    using EntityEventContainer = std::unordered_map<
            Entity::EntityId,EventQueue>;

    class EntityManager;
    class SystemManager{
    public:
        SystemManager();
        ~SystemManager();
        void SetEntityManager(EntityManager* l_entityMgr);
        EntityManager* GetEntityManager();
        MessageHandler* GetMessageHandler();
        template<class T>
        T* GetSystem(const ECS::System& l_system){
            auto itr = m_systems.find(l_system);
            return(itr != m_systems.end() ?
                   dynamic_cast<T*>(itr->second) : nullptr);
        }
        void AddEvent(const Entity::EntityId& l_entity, const EventID& l_event);
        void Update(float l_dT);
        void HandleEvents();
        void Draw(Window::Window* l_wind, unsigned int l_elevation);
        void EntityModified(const Entity::EntityId& l_entity,
                            const Bitmask& l_bits);
        void RemoveEntity(const Entity::EntityId& l_entity);
        void PurgeEntities();
        void PurgeSystems();
    private:
        SystemContainer m_systems;
        EntityManager* m_entityManager;
        EntityEventContainer m_events;
        MessageHandler m_messages;
    };
}