//
// Created by Norbert Olkowski on 12.12.2023.
//

#pragma once

namespace ECS {

    using ComponentType = unsigned int;
#define N_COMPONENT_TYPES 32
    enum class Component {
        Position = 0, SpriteSheet, State, Movable, Controller, Collidable
    };
    enum class System {
        Renderer = 0, Movement, Collision, Control, State, SheetAnimation
    };

    enum class EntityEvent {
        Spawned, Despawned, Colliding_X, Colliding_Y,
        Moving_Left, Moving_Right, Moving_Up, Moving_Down,
        Elevation_Change, Became_Idle, Began_Moving
    };

    enum class EntityMessage{
        Move, Is_Moving, State_Changed, Direction_Changed,
        Switch_State, Attack_Action, Dead
    };

}