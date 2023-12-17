//
// Created by Norbert Olkowski on 16.12.2023.
//

#include "../Entity/Entity.hpp"
#include "System.hpp"
#include "Systems/Renderer/Renderer.hpp"

namespace System{
    SystemManager::SystemManager(): m_entityManager(nullptr){
        //m_systems[ECS::System::State] = new System::State(this);
        //m_systems[ECS::System::Control] = new System::Control(this);
        //m_systems[ECS::System::Movement] = new System::Movement(this);
        //m_systems[ECS::System::Collision] = new System::Collision(this);
        //m_systems[ECS::System::SheetAnimation] = new System::SheetAnimation(this);
        m_systems[ECS::System::Renderer] = new System::Renderer(this);
    }

    SystemManager::~SystemManager(){
        PurgeSystems();
    }

    void SystemManager::SetEntityManager(Entity::EntityManager* l_entityMgr){
        if(!m_entityManager){ m_entityManager = l_entityMgr; }
    }

    Entity::EntityManager* SystemManager::GetEntityManager(){
        return m_entityManager;
    }

    MessageHandler* SystemManager::GetMessageHandler(){
        return &m_messages;
    }

    void SystemManager::AddEvent(const Entity::EntityId& l_entity,
                                 const EventID& l_event)
    {
        m_events[l_entity].AddEvent(l_event);
    }

    void SystemManager::Update(float l_dT){
        for(auto &itr : m_systems){
            itr.second->Update(l_dT);
        }
        HandleEvents();
    }

    void SystemManager::HandleEvents(){
        for(auto &event : m_events){
            EventID id = 0;
            while(event.second.ProcessEvents(id)){
                for(auto &system : m_systems)
                {
                    if(system.second->HasEntity(event.first)){
                        system.second->HandleEvent(event.first,(ECS::EntityEvent)id);
                    }
                }
            }
        }
    }

    void SystemManager::Draw(Window::Window* l_wind,
                             unsigned int l_elevation)
    {
        auto itr = m_systems.find(ECS::System::Renderer);
        if (itr == m_systems.end()){ return; }
        auto* system = (System::Renderer*)itr->second;
        system->Render(l_wind, l_elevation);
    }

    void SystemManager::EntityModified(const Entity::EntityId& l_entity,
                                       const Bitmask& l_bits)
    {
        for(auto &s_itr : m_systems){
            System::Base* system = s_itr.second;
            if(system->FitsRequirements(l_bits)){
                if(!system->HasEntity(l_entity)){
                    system->AddEntity(l_entity);
                }
            } else {
                if(system->HasEntity(l_entity)){
                    system->RemoveEntity(l_entity);
                }
            }
        }
    }

    void SystemManager::RemoveEntity(const Entity::EntityId& l_entity){
        for(auto &system : m_systems){
            system.second->RemoveEntity(l_entity);
        }
    }

    void SystemManager::PurgeEntities(){
        for(auto &system : m_systems){
            system.second->Purge();
        }
    }

    void SystemManager::PurgeSystems(){
        for (auto &system : m_systems){
            delete system.second;
        }
        m_systems.clear();
    }
}