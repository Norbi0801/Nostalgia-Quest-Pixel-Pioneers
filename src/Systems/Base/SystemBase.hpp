//
// Created by Norbert Olkowski on 12.12.2023.
//

#pragma once

#include <vector>

#include "../../Utilities/Bitmask.hpp"
#include "../../Core/Entity/Entity.hpp"


namespace System {

    using EntityList = std::vector<Entity::EntityId>;
    using Requirements = std::vector<Bitmask>;

    class SystemManager;

    class Base {
    public:
        Base(const ECS::System &l_id, SystemManager *l_systemMgr);

        virtual ~Base();

        bool AddEntity(const Entity::EntityId &l_entity);

        bool HasEntity(const Entity::EntityId &l_entity);

        bool RemoveEntity(const Entity::EntityId &l_entity);

        ECS::System GetId();

        bool FitsRequirements(const Bitmask &l_bits);

        void Purge();

        virtual void Update(float l_dT) = 0;

        virtual void HandleEvent(const Entity::EntityId &l_entity,
                                 const Entity::EntityId &l_event) = 0;

    protected:
        ECS::System m_id;
        Requirements m_requiredComponents;
        EntityList m_entities;
        SystemManager *m_systemManager;
    };
}