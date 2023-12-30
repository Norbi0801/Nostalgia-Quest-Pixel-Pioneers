//
// Created by Norbert Olkowski on 30.12.2023.
//

#include "SheetAnimation.hpp"
#include "Components/SpriteSheet/SpriteSheet.hpp"
#include "Components/State/State.hpp"

namespace System {
    SheetAnimation::SheetAnimation(SystemManager* l_systemMgr)
    : S_Base(System::SheetAnimation,l_systemMgr)
    {
        Bitmask req;
        req.TurnOnBit((unsigned int)ECS::Component::SpriteSheet);
        req.TurnOnBit((unsigned int)ECS::Component::State);
        m_requiredComponents.push_back(req);
        m_systemManager->GetMessageHandler()->
        Subscribe(ECS::EntityMessage::State_Changed,this);
    }

    void SheetAnimation::Update(float l_dT){
        auto* entities = m_systemManager->GetEntityManager();
        for(auto &entity : m_entities){
            auto* sheet = entities->
                    GetComponent<Component::SpriteSheet>(entity, ECS::Component::SpriteSheet);
            auto* state = entities->
                    GetComponent<Component::State>(entity, ECS::Component::State);
            sheet->GetSpriteSheet()->Update(l_dT);
            const std::string& animName = sheet->
                    GetSpriteSheet()->GetCurrentAnim()->GetName();
            if(animName == "Attack"){
                if(!sheet->GetSpriteSheet()->GetCurrentAnim()->IsPlaying())
                {
                    Message msg((MessageType)ECS::EntityMessage::Switch_State);
                    msg.m_receiver = entity;
                    msg.m_int = (int)ECS::EntityState::Idle;
                    m_systemManager->GetMessageHandler()->Dispatch(msg);
                } else if(sheet->GetSpriteSheet()->
                        GetCurrentAnim()->IsInAction())
                {
                    Message msg((MessageType)ECS::EntityMessage::Attack_Action);
                    msg.m_sender = entity;
                    m_systemManager->GetMessageHandler()->Dispatch(msg);
                }
            } else if(animName == "Death" &&
                      !sheet->GetSpriteSheet()->GetCurrentAnim()->IsPlaying())
            {
                Message msg((MessageType)ECS::EntityMessage::Dead);
                msg.m_receiver = entity;
                m_systemManager->GetMessageHandler()->Dispatch(msg);
            }
        }
    }

    void SheetAnimation::Notify(const Message& l_message){
        if(HasEntity(l_message.m_receiver)){
            auto m = (ECS::EntityMessage)l_message.m_type;
            switch(m){
                case ECS::EntityMessage::State_Changed:
                {
                    ECS::EntityState s = (ECS::EntityState)l_message.m_int;
                    switch(s){
                        case ECS::EntityState::Idle:
                            ChangeAnimation(l_message.m_receiver,"Idle",true,true);
                            break;
                        case ECS::EntityState::Walking:
                            ChangeAnimation(l_message.m_receiver,"Walk",true,true);
                            break;
                        case ECS::EntityState::Attacking:
                            ChangeAnimation(l_message.m_receiver,
                                            "Attack",true,false);
                            break;
                        case ECS::EntityState::Hurt: break;
                        case ECS::EntityState::Dying:
                            ChangeAnimation(l_message.m_receiver,
                                            "Death",true,false);
                            break;
                    }
                }
                    break;
            }
        }
    }

    void SheetAnimation::ChangeAnimation(const Entity::EntityId& l_entity,
                                           const std::string& l_anim, bool l_play, bool l_loop)
    {
        auto* sheet = m_systemManager->GetEntityManager()->
                GetComponent<Component::SpriteSheet>(l_entity,ECS::Component::SpriteSheet);
        sheet->GetSpriteSheet()->SetAnimation(l_anim,l_play,l_loop);
    }

}