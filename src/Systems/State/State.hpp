//
// Created by Norbert Olkowski on 26.12.2023.
//

#pragma once

#include "Systems/Base/SystemBase.hpp"
#include "Utilities/Axis.hpp"
#include "Utilities/Direction.hpp"
#include "Components/Movable/Movable.hpp"
#include "Components/Position/Position.hpp"

namespace System{
    class State : public Base {
        explicit State(SystemManager *l_systemMgr);

        ~State();

        void Update(float l_dT) override;

        void HandleEvent(const Entity::EntityId &l_entity,
                         const ECS::EntityEvent &l_event) override;

        void Notify(const Message &l_message) override;
        void ChangeState(const Entity::EntityId& l_entity,
                                const ECS::EntityState& l_state, const bool& l_force);
    };
}
