//
// Created by Norbert Olkowski on 30.12.2023.
//

#include "Core/System/System.hpp"
#include "Control.hpp"

namespace System {
    Control::Control(SystemManager* l_systemMgr)
    :Base(ECS::System::Control,l_systemMgr)
    {
        Bitmask req;
        req.TurnOnBit((unsigned int)ECS::Component::Position);
        req.TurnOnBit((unsigned int)ECS::Component::Movable);
        req.TurnOnBit((unsigned int)ECS::Component::Controller);
        m_requiredComponents.push_back(req);
        req.Clear();
    }

    void Control::HandleEvent(const Entity::EntityId& l_entity,
                                const ECS::EntityEvent& l_event)
    {
        switch(l_event){
            case ECS::EntityEvent::Moving_Left:
                MoveEntity(l_entity,Direction::Left); break;
            case ECS::EntityEvent::Moving_Right:
                MoveEntity(l_entity, Direction::Right); break;
            case ECS::EntityEvent::Moving_Up:
                MoveEntity(l_entity, Direction::Up); break;
            case ECS::EntityEvent::Moving_Down:
                MoveEntity(l_entity, Direction::Down); break;
        }
    }

    void Control::MoveEntity(const Entity::EntityId& l_entity,
                             const Direction& l_dir)
    {
        auto* mov = m_systemManager->GetEntityManager()->
                GetComponent<Component::Movable>(l_entity, ECS::Component::Movable);
        mov->Move(l_dir);
    }
}