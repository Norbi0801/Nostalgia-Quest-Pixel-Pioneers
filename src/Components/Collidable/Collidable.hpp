//
// Created by Norbert Olkowski on 30.12.2023.
//

#pragma once

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "Components/Base/ComponentBase.hpp"

enum class Origin{ Top_Left, Abs_Centre, Mid_Bottom };

namespace Component{

    class Collidable : public Base{
        Collidable(): Base(ECS::Component::Collidable),
                        m_origin(Origin::Mid_Bottom), m_collidingOnX(false),
                        m_collidingOnY(false)
        {};
        void ReadIn(std::stringstream& l_stream){
            unsigned int origin = 0;
            l_stream >> m_AABB.width >> m_AABB.height >> m_offset.x
                     >> m_offset.y >> origin;
            m_origin = (Origin)origin;
        }
        void CollideOnX(){ m_collidingOnX = true; }
        void CollideOnY(){ m_collidingOnY = true; }
        void ResetCollisionFlags(){
            m_collidingOnX = false;
            m_collidingOnY = false;
        }
        void SetSize(const sf::Vector2f& l_vec){
            m_AABB.width = l_vec.x;
            m_AABB.height = l_vec.y;
        }
        void SetPosition(const sf::Vector2f& l_vec){
            switch(m_origin){
                case(Origin::Top_Left):
                    m_AABB.left = l_vec.x + m_offset.x;
                    m_AABB.top = l_vec.y + m_offset.y;
                    break;
                case(Origin::Abs_Centre):
                    m_AABB.left = l_vec.x - (m_AABB.width / 2) + m_offset.x;
                    m_AABB.top = l_vec.y - (m_AABB.height / 2) + m_offset.y;
                    break;
                case(Origin::Mid_Bottom):
                    m_AABB.left = l_vec.x - (m_AABB.width / 2) + m_offset.x;
                    m_AABB.top = l_vec.y - m_AABB.height + m_offset.y;
                    break;
            }
        }
    private:
        sf::FloatRect m_AABB;
        sf::Vector2f m_offset;
        Origin m_origin;
        bool m_collidingOnX;
        bool m_collidingOnY;
    };
}