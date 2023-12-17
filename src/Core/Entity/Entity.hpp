//
// Created by Norbert Olkowski on 12.12.2023.
//

#pragma once

#include <vector>
#include <unordered_map>
#include <functional>

#include "Utilities/Bitmask.hpp"
#include "Components/Base/ComponentBase.hpp"
#include "Core/Texture/Texture.hpp"

namespace System {
    class SystemManager;
}

namespace Entity {

    using EntityId = unsigned int;
    using ComponentContainer = std::vector<Component::Base *>;
    using EntityData = std::pair<Bitmask, ComponentContainer>;
    using EntityContainer = std::unordered_map<EntityId, EntityData>;
    using ComponentFactory = std::unordered_map<ECS::Component, std::function<Component::Base *(void)>>;

    class EntityManager {
    public:
        EntityManager(System::SystemManager *l_sysMgr,
                      Texture::TextureManager *l_textureMgr);

        ~EntityManager();

        int AddEntity(const Bitmask &l_mask);

        int AddEntity(const std::string &l_entityFile);

        bool RemoveEntity(const EntityId &l_id);

        bool AddComponent(const EntityId &l_entity,
                          const ECS::Component &l_component);

        template<class T>
        T *GetComponent(const EntityId &l_entity,
                        const ECS::Component &l_component) {
            auto itr = m_entities.find(l_entity);
            if (itr == m_entities.end()) { return nullptr; }
            if (!itr->second.first.GetBit((unsigned int) l_component)) {
                return nullptr;
            }
            auto &container = itr->second.second;
            auto component = std::find_if(container.begin(), container.end(),
                                          [&l_component](Component::Base *c) {
                                              return c->GetType() == l_component;
                                          });
            return (component != container.end() ?
                    dynamic_cast<T *>(*component) : nullptr);
        }

        bool RemoveComponent(const EntityId &l_entity,
                             const ECS::Component &l_component);

        bool HasComponent(const EntityId &l_entity,
                          const ECS::Component &l_component);

        void Purge();

    private:
        template<class T>
        void AddComponentType(const ECS::Component &l_id) {
            m_cFactory[l_id] = []() -> Component::Base * { return new T(); };
        }

        unsigned int m_idCounter;
        EntityContainer m_entities;
        ComponentFactory m_cFactory;
        System::SystemManager *m_systems;
        Texture::TextureManager *m_textureManager;
    };

}