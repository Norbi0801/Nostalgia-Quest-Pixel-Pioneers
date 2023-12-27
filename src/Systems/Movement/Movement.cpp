//
// Created by Norbert Olkowski on 26.12.2023.
//



#include "Core/Map/Map.hpp"
#include "Core/System/System.hpp"
#include "Movement.hpp"
#include "Core/Tile/Tile.hpp"

namespace System {
    Movement::Movement(SystemManager *l_systemMgr)
            : Base(ECS::System::Movement, l_systemMgr) {
        Bitmask req;
        req.TurnOnBit((unsigned int) ECS::Component::Position);
        req.TurnOnBit((unsigned int) ECS::Component::Movable);
        m_requiredComponents.push_back(req);
        req.Clear();
        m_systemManager->GetMessageHandler()->
                Subscribe(ECS::EntityMessage::Is_Moving, this);
        m_gameMap = nullptr;
    }

    Movement::~Movement() = default;

    void Movement::Update(float l_dT) {
        if (!m_gameMap) { return; }
        Entity::EntityManager *entities = m_systemManager->GetEntityManager();
        for (auto &entity: m_entities) {
            auto *position = entities->
                    GetComponent<Component::Position>(entity, ECS::Component::Position);
            auto *movable = entities->
                    GetComponent<Component::Movable>(entity, ECS::Component::Movable);
            MovementStep(l_dT, movable, position);
            position->MoveBy(movable->GetVelocity() * l_dT);
        }
    }

    void Movement::MovementStep(float l_dT, Component::Movable *l_movable,
                                Component::Position *l_position) {
        sf::Vector2f f_coefficient =
                GetTileFriction(l_position->GetElevation(),
                                floor(l_position->GetPosition().x / Tile::Sheet::Tile_Size),
                                floor(l_position->GetPosition().y / Tile::Sheet::Tile_Size));
        sf::Vector2f friction(l_movable->GetSpeed().x * f_coefficient.x,
                              l_movable->GetSpeed().y * f_coefficient.y);
        l_movable->AddVelocity(l_movable->GetAcceleration() * l_dT);
        l_movable->SetAcceleration(sf::Vector2f(0.0f, 0.0f));
        l_movable->ApplyFriction(friction * l_dT);
        float magnitude = sqrt(
                (l_movable->GetVelocity().x * l_movable->GetVelocity().x) +
                (l_movable->GetVelocity().y * l_movable->GetVelocity().y));
        if (magnitude <= l_movable->GetMaxVelocity()) { return; }
        float max_V = l_movable->GetMaxVelocity();
        l_movable->SetVelocity(sf::Vector2f(
                (l_movable->GetVelocity().x / magnitude) * max_V,
                (l_movable->GetVelocity().y / magnitude) * max_V));
    }

    const sf::Vector2f &Movement::GetTileFriction(unsigned int l_elevation, unsigned int l_x,
                                                  unsigned int l_y) {
        // # TODO delete this ?
        return {0, 0};
    }

    void Movement::HandleEvent(const Entity::EntityId &l_entity,
                               const ECS::EntityEvent &l_event) {
        switch (l_event) {
            case ECS::EntityEvent::Colliding_X:
                StopEntity(l_entity, Axis::x);
                break;
            case ECS::EntityEvent::Colliding_Y:
                StopEntity(l_entity, Axis::y);
                break;
            case ECS::EntityEvent::Moving_Left:
                SetDirection(l_entity, Direction::Left);
                break;
            case ECS::EntityEvent::Moving_Right:
                SetDirection(l_entity, Direction::Right);
                break;
            case ECS::EntityEvent::Moving_Up: {
                auto *mov = m_systemManager->GetEntityManager()->
                        GetComponent<Component::Movable>(l_entity, ECS::Component::Movable);
                if (mov->GetVelocity().x == 0) {
                    SetDirection(l_entity, Direction::Up);
                }
            }
                break;
            case ECS::EntityEvent::Moving_Down: {
                auto *mov = m_systemManager->GetEntityManager()->
                        GetComponent<Component::Movable>(l_entity, ECS::Component::Movable);
                if (mov->GetVelocity().x == 0) {
                    SetDirection(l_entity, Direction::Down);
                }
            }
                break;
            case ECS::EntityEvent::Spawned:
                break;
            case ECS::EntityEvent::Despawned:
                break;
            case ECS::EntityEvent::Elevation_Change:
                break;
            case ECS::EntityEvent::Became_Idle:
                break;
            case ECS::EntityEvent::Began_Moving:
                break;
        }
    }

    void Movement::Notify(const Message &l_message) {
        Entity::EntityManager *eMgr = m_systemManager->GetEntityManager();
        auto m = (ECS::EntityMessage) l_message.m_type;
        switch (m) {
            case ECS::EntityMessage::Is_Moving: {
                if (!HasEntity(l_message.m_receiver)) { return; }
                auto *movable = eMgr->GetComponent<Component::Movable>(l_message.m_receiver, ECS::Component::Movable);
                if (movable->GetVelocity() != sf::Vector2f(0.0f, 0.0f)) {
                    return;
                }
                m_systemManager->AddEvent(l_message.m_receiver,
                                          (EventID) ECS::EntityEvent::Became_Idle);
            }
                break;
            case ECS::EntityMessage::Move:
                break;
            case ECS::EntityMessage::State_Changed:
                break;
            case ECS::EntityMessage::Direction_Changed:
                break;
            case ECS::EntityMessage::Switch_State:
                break;
            case ECS::EntityMessage::Attack_Action:
                break;
            case ECS::EntityMessage::Dead:
                break;
        }
    }

    void Movement::StopEntity(const Entity::EntityId &l_entity,
                              const Axis &l_axis) {
        auto *movable = m_systemManager->GetEntityManager()->
                GetComponent<Component::Movable>(l_entity, ECS::Component::Movable);
        if (l_axis == Axis::x) {
            movable->SetVelocity(sf::Vector2f(
                    0.f, movable->GetVelocity().y));
        } else if (l_axis == Axis::y) {
            movable->SetVelocity(sf::Vector2f(
                    movable->GetVelocity().x, 0.f));
        }
    }

    void Movement::SetDirection(const Entity::EntityId &l_entity,
                                const Direction &l_dir) {
        auto *movable = m_systemManager->GetEntityManager()->
                GetComponent<Component::Movable>(l_entity, ECS::Component::Movable);
        movable->SetDirection(l_dir);
        Message msg((MessageType) ECS::EntityMessage::Direction_Changed);
        msg.m_receiver = l_entity;
        msg.m_int = (int) l_dir;
        m_systemManager->GetMessageHandler()->Dispatch(msg);
    }

    void Movement::SetMap(Map::Map *l_gameMap) { m_gameMap = l_gameMap; }
}