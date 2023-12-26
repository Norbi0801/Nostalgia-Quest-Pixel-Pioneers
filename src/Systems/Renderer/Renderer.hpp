//
// Created by Norbert Olkowski on 16.12.2023.
//

#include "Core/System/System.hpp"
#include "Core/SpriteSheet/SpriteSheet.hpp"

namespace System{
    class Renderer : public Base{
    public:
        explicit Renderer(SystemManager* l_systemMgr);
        ~Renderer();
        void Update(float l_dT) override;
        void HandleEvent(const Entity::EntityId& l_entity,
                         const ECS::EntityEvent& l_event) override;
        void Notify(const Message& l_message) override;
        void Render(Window::Window* l_wind, unsigned int l_layer);
    private:
        void SetSheetDirection(const Entity::EntityId& l_entity,
                               const Direction& l_dir);
        void SortDrawables();
    };
}
