//
// Created by Norbert Olkowski on 12.12.2023.
//

#include "SystemBase.hpp"
#include "../../Core/System/System.hpp"

namespace System {

    Base::Base(const ECS::System &l_id, SystemManager *l_systemMgr)
            : m_id(l_id), m_systemManager(l_systemMgr) {}

    Base::~Base() { Purge(); }

    bool Base::AddEntity(const Entity::EntityId &l_entity) {
        if (HasEntity(l_entity)) { return false; }
        m_entities.emplace_back(l_entity);
        return true;
    }

    bool Base::HasEntity(const Entity::EntityId &l_entity) {
        return std::find(m_entities.begin(),
                         m_entities.end(), l_entity) != m_entities.end();
    }

    bool Base::RemoveEntity(const Entity::EntityId &l_entity) {
        auto entity = std::find_if(m_entities.begin(), m_entities.end(),
                                   [&l_entity](Entity::EntityId &id) { return id = l_entity; });
        if (entity == m_entities.end()) { return false; }
        m_entities.erase(entity);
        return true;
    }

    bool Base::FitsRequirements(const Bitmask &l_bits) {
        return std::find_if(m_requiredComponents.begin(),
                            m_requiredComponents.end(), [&l_bits](Bitmask &b) {
                    return b.Matches(l_bits, b.GetMask());
                }) != m_requiredComponents.end();
    }

    void Base::Purge() { m_entities.clear(); }
}