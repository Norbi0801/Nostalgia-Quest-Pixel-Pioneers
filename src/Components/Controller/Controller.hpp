//
// Created by Norbert Olkowski on 30.12.2023.
//

#pragma once

#include "Components/Base/ComponentBase.hpp"

namespace Component {
    class Controller : public Base{
    public:
        Controller() : Base(COMPONENT_CONTROLLER){}
        void ReadIn(std::stringstream& l_stream){}
    };
}