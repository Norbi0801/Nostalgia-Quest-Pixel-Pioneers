//
// Created by Norbert Olkowski on 30.12.2023.
//

#pragma once

#include "Systems/Base/SystemBase.hpp"
#include "Utilities/Axis.hpp"
#include "Utilities/Direction.hpp"
#include "Components/Movable/Movable.hpp"
#include "Components/Position/Position.hpp"

namespace System{
    class Control : public Base {
        explicit Control(SystemManager *l_systemMgr);

        ~Control();

        void Update(float l_dT) override;

        void HandleEvent(const Entity::EntityId &l_entity,
                         const ECS::EntityEvent &l_event) override;

        void Notify(const Message &l_message) override;

        void MoveEntity(const EntityId &l_entity, const Direction &l_dir);
    };
}
