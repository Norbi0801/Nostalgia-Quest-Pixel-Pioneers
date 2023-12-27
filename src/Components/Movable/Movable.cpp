//
// Created by Norbert Olkowski on 26.12.2023.
//

#include "Movable.hpp"

namespace Component {
    void Movable::ReadIn(std::stringstream& l_stream){
        l_stream >> m_velocityMax >> m_speed.x >> m_speed.y;
        unsigned int dir = 0;
        l_stream >> dir;
        m_direction = (Direction)dir;
    }

    void Movable::AddVelocity(const sf::Vector2f& l_vec){
        m_velocity += l_vec;
        if(std::abs(m_velocity.x) > m_velocityMax){
            m_velocity.x = m_velocityMax *
                           (m_velocity.x / std::abs(m_velocity.x));
        }
        if(std::abs(m_velocity.y) > m_velocityMax){
            m_velocity.y = m_velocityMax *
                           (m_velocity.y / std::abs(m_velocity.y));
        }
    }

    void Movable::ApplyFriction(const sf::Vector2f& l_vec){
        if(m_velocity.x != 0 && l_vec.x != 0){
            if(std::abs(m_velocity.x) - std::abs(l_vec.x) < 0){
                m_velocity.x = 0;
            } else {
                m_velocity.x += (m_velocity.x > 0 ? l_vec.x * -1 : l_vec.x);
            }
        }
        if(m_velocity.y != 0 && l_vec.y != 0){
            if(std::abs(m_velocity.y) - std::abs(l_vec.y) < 0){
                m_velocity.y = 0;
            } else {
                m_velocity.y += (m_velocity.y > 0 ? l_vec.y * -1 : l_vec.y);
            }
        }
    }

    void Movable::Accelerate(const sf::Vector2f& l_vec){
        m_acceleration += l_vec;
    }
    void Movable::Accelerate(float l_x, float l_y){
        m_acceleration += sf::Vector2f(l_x,l_y);
    }

    void Movable::Move(const Direction& l_dir){
        if(l_dir == Direction::Up){
            m_acceleration.y -= m_speed.y;
        } else if (l_dir == Direction::Down){
            m_acceleration.y += m_speed.y;
        } else if (l_dir == Direction::Left){
            m_acceleration.x -= m_speed.x;
        } else if (l_dir == Direction::Right){
            m_acceleration.x += m_speed.x;
        }
    }

    sf::Vector2f Movable::GetVelocity() {
        return m_velocity;
    }

    sf::Vector2f Movable::GetSpeed() {
        return m_speed;
    }

    sf::Vector2f Movable::GetAcceleration() {
        return m_acceleration;
    }

    float Movable::GetMaxVelocity() const {
        return m_velocityMax;
    }

    Direction Movable::GetDirection() const {
        return m_direction;
    }

    void Movable::SetMaxVelocity(float maxVelocity) {
        m_velocityMax = maxVelocity;
    }

    void Movable::SetDirection(Direction direction) {
        m_direction = direction;
    }

    void Movable::SetAcceleration(sf::Vector2<float> vector2) {
        m_acceleration = vector2;
    }

    void Movable::SetVelocity(const sf::Vector2<float> vector2) {
        m_velocity = vector2;
    }
}