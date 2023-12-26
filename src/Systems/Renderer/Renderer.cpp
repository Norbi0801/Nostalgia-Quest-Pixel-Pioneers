//
// Created by Norbert Olkowski on 16.12.2023.
//


#include <algorithm>

#include "Core/Entity/Entity.hpp"
#include "Components/SpriteSheet/SpriteSheet.hpp"
#include "Components/Position/Position.hpp"
#include "Renderer.hpp"

namespace System {
    void Renderer::SetSheetDirection(const Entity::EntityId &l_entity,
                                     const Direction &l_dir) {
        Entity::EntityManager *entities = m_systemManager->GetEntityManager();
        if (!entities->HasComponent(l_entity,
                                    ECS::Component::SpriteSheet)) {
            return;
        }
        auto *sheet = entities->
                GetComponent<Component::SpriteSheet>(l_entity, ECS::Component::SpriteSheet);
        sheet->GetSpriteSheet()->SetDirection(l_dir);
    }

    void Renderer::SortDrawables() {
        Entity::EntityManager *e_mgr = m_systemManager->GetEntityManager();
        std::ranges::sort(m_entities, [e_mgr](unsigned int l_1, unsigned int l_2) {
            auto pos1 = e_mgr->GetComponent<Component::Position>(l_1, ECS::Component::Position);
            auto pos2 = e_mgr->GetComponent<Component::Position>(l_2, ECS::Component::Position);
            if (pos1->GetElevation() == pos2->GetElevation()) {
                return pos1->GetPosition().y < pos2->GetPosition().y;
            }
            return pos1->GetElevation() < pos2->GetElevation();
        });
    }

    Renderer::Renderer(SystemManager *l_systemMgr)
            : Base(ECS::System::Renderer, l_systemMgr) {
        Bitmask req;
        req.TurnOnBit((unsigned int) ECS::Component::Position);
        req.TurnOnBit((unsigned int) ECS::Component::SpriteSheet);
        m_requiredComponents.push_back(req);
        req.Clear();
        m_systemManager->GetMessageHandler()->
                Subscribe(ECS::EntityMessage::Direction_Changed, this);
    }

    Renderer::~Renderer() = default;

    void Renderer::Update(float l_dT) {
        Entity::EntityManager *entities = m_systemManager->GetEntityManager();
        for (auto &entity: m_entities) {
            auto *position = entities->
                    GetComponent<Component::Position>(entity, ECS::Component::Position);
            Component::Drawable *drawable = nullptr;
            if (entities->HasComponent(entity, ECS::Component::SpriteSheet)) {
                drawable = entities->
                        GetComponent<Component::Drawable>(entity, ECS::Component::SpriteSheet);
            } else { continue; }
            drawable->UpdatePosition(position->GetPosition());
        }
    }

    void Renderer::HandleEvent(const Entity::EntityId &l_entity,
                               const ECS::EntityEvent &l_event) {
        if (l_event == ECS::EntityEvent::Moving_Left ||
            l_event == ECS::EntityEvent::Moving_Right ||
            l_event == ECS::EntityEvent::Moving_Up ||
            l_event == ECS::EntityEvent::Moving_Down ||
            l_event == ECS::EntityEvent::Elevation_Change ||
            l_event == ECS::EntityEvent::Spawned) {
            SortDrawables();
        }
    }

    void Renderer::Notify(const Message &l_message) {
        if (HasEntity(l_message.m_receiver)) {
            auto m = (ECS::EntityMessage) l_message.m_type;
            switch (m) {
                case ECS::EntityMessage::Direction_Changed:
                    SetSheetDirection(l_message.m_receiver,
                                      (Direction) l_message.m_int);
                    break;
            }
        }
    }

    void Renderer::Render(Window::Window *l_wind, unsigned int l_layer) {
        Entity::EntityManager *entities = m_systemManager->GetEntityManager();
        for (auto &entity: m_entities) {
            auto *position = entities->
                    GetComponent<Component::Position>(entity, ECS::Component::Position);
            if (position->GetElevation() < l_layer) { continue; }
            if (position->GetElevation() > l_layer) { break; }
            Component::Drawable *drawable = nullptr;
            if (!entities->HasComponent(entity,
                                        ECS::Component::SpriteSheet)) {
                continue;
            }
            drawable = entities->
                    GetComponent<Component::Drawable>(entity, ECS::Component::SpriteSheet);
            sf::FloatRect drawableBounds;
            drawableBounds.left = position->GetPosition().x -
                                  (drawable->GetSize().x / 2);
            drawableBounds.top = position->GetPosition().y -
                                 drawable->GetSize().y;
            drawableBounds.width = drawable->GetSize().x;
            drawableBounds.height = drawable->GetSize().y;
            if (!l_wind->GetViewSpace().intersects(
                    drawableBounds)) {
                continue;
            }
            drawable->Draw(l_wind->GetRenderWindow());
        }
    }

}