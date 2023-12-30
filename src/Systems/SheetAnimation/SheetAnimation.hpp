//
// Created by Norbert Olkowski on 30.12.2023.
//

#pragma once


#include "Core/System/System.hpp"

namespace System{
    class SheetAnimation : public Base {
        explicit SheetAnimation(SystemManager *l_systemMgr);

        ~SheetAnimation();

        void Update(float l_dT) override;

        void HandleEvent(const Entity::EntityId &l_entity,
                         const ECS::EntityEvent &l_event) override;

        void Notify(const Message &l_message) override;
        void ChangeState(const Entity::EntityId& l_entity,
                         const ECS::EntityState& l_state, const bool& l_force);

        void ChangeAnimation(const Entity::EntityId &l_entity, const std::string &l_anim, bool l_play, bool l_loop);
    };
}
