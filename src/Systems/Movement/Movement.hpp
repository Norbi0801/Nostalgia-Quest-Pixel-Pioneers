//
// Created by Norbert Olkowski on 26.12.2023.
//

#pragma once

#include "Systems/Base/SystemBase.hpp"
#include "Utilities/Axis.hpp"
#include "Utilities/Direction.hpp"
#include "Components/Movable/Movable.hpp"
#include "Components/Position/Position.hpp"

namespace Map{
    class Map;
}

namespace System{
    class Movement : public Base{
        explicit Movement(SystemManager* l_systemMgr);
        ~Movement();
        void Update(float l_dT) override;
        void HandleEvent(const Entity::EntityId& l_entity,
                         const ECS::EntityEvent& l_event) override;
        void Notify(const Message& l_message) override;

    public:
        void SetMap(Map::Map* l_gameMap);

    private:
        void StopEntity(const Entity::EntityId& l_entity,
                        const Axis& l_axis);
        void SetDirection(const Entity::EntityId& l_entity,
                          const Direction& l_dir);
        const sf::Vector2f& GetTileFriction(unsigned int l_elevation,
                                            unsigned int l_x, unsigned int l_y);
        void MovementStep(float l_dT, Component::Movable* l_movable,
                          Component::Position* l_position);
        Map::Map* m_gameMap;
    };
}
