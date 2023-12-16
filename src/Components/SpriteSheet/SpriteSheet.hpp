//
// Created by Norbert Olkowski on 16.12.2023.
//

#pragma once

#include "Components/Drawable/Drawable.hpp"
#include "Core/SpriteSheet/SpriteSheet.hpp"

using SpriteSheetClass = SpriteSheet::SpriteSheet;

namespace Component{
    class SpriteSheet : public Drawable{
    public:
        SpriteSheet(): Drawable(ECS::Component::SpriteSheet),
                         m_spriteSheet(nullptr){}
        ~SpriteSheet() override{
            delete m_spriteSheet;
        }
        void ReadIn(std::stringstream& l_stream) override{
            l_stream >> m_sheetName;
        }
        void Create(Texture::TextureManager* l_textureMgr,
                    const std::string& l_name = "")
        {
            if (m_spriteSheet){ return; }
            m_spriteSheet = new SpriteSheetClass(l_textureMgr);
            m_spriteSheet->LoadSheet("media/Spritesheets/" +
                                     (!l_name.empty() ? l_name : m_sheetName) + ".sheet");
        }
        SpriteSheetClass* GetSpriteSheet(){ return m_spriteSheet; }
        void UpdatePosition(const sf::Vector2f& l_vec) override{
            m_spriteSheet->SetSpritePosition(l_vec);
        }
        const sf::Vector2u& GetSize() override{
            return m_spriteSheet->GetSpriteSize();
        }
        void Draw(sf::RenderWindow* l_wind) override{
            if (!m_spriteSheet){ return; }
            m_spriteSheet->Draw(l_wind);
        }
    private:
        SpriteSheetClass* m_spriteSheet;
        std::string m_sheetName;
    };
}