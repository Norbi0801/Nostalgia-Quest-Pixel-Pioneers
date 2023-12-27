//
// Created by Norbert Olkowski on 26.12.2023.
//

#pragma once

#include "SFML/System/Vector2.hpp"
#include "Components/Base/ComponentBase.hpp"
#include "Utilities/Direction.hpp"

namespace Component {

    class Movable : public Base {
    public:
        Movable() : Base(ECS::Component::Movable),
                    m_velocityMax(0.f), m_direction((Direction) 0) {};

        void ReadIn(std::stringstream &l_stream) override;

        void AddVelocity(const sf::Vector2f &l_vec);


        void ApplyFriction(const sf::Vector2f &l_vec);

        void Accelerate(const sf::Vector2f &l_vec);

        void Accelerate(float l_x, float l_y);

        void Move(const Direction &l_dir);

        sf::Vector2f GetSpeed();

        sf::Vector2f GetVelocity();

        sf::Vector2f GetAcceleration();

        float GetMaxVelocity() const;

        Direction GetDirection() const;

        void SetMaxVelocity(float maxVelocity);

        void SetDirection(Direction direction);

        void SetAcceleration(sf::Vector2<float> vector2);

        void SetVelocity(sf::Vector2<float> vector2);

    private:

        sf::Vector2f m_velocity;
        float m_velocityMax;
        sf::Vector2f m_speed;
        sf::Vector2f m_acceleration;
        Direction m_direction;


    };
}

