//
// Created by Norbert Olkowski on 12.12.2023.
//

#pragma once

#include "sstream"
#include "../../Core/ECS/ECS.hpp"

namespace Component{
    class Base{
    public:
        Base(const ECS::Component& l_type): m_type(l_type){}
        virtual ~Base(){}
        ECS::Component GetType(){ return m_type; }
        friend std::stringstream& operator >>(
                std::stringstream& l_stream, Base& b)
        {
            b.ReadIn(l_stream);
            return l_stream;
        }
        virtual void ReadIn(std::stringstream& l_stream) = 0;
    protected:
        ECS::Component m_type;
    };
}