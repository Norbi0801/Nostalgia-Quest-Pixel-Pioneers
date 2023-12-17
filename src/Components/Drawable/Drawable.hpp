//
// Created by Norbert Olkowski on 16.12.2023.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "../../Core/ECS/ECS.hpp"
#include "Components/Base/ComponentBase.hpp"


namespace Component{

class Drawable : public Base{
public:
    explicit Drawable(const ECS::Component& l_type) : Base(l_type){}
    ~Drawable() override= default;
    virtual void UpdatePosition(const sf::Vector2f& l_vec) = 0;
    virtual const sf::Vector2i & GetSize() = 0;
    virtual void Draw(sf::RenderWindow& l_wind) = 0;
private:
};

}