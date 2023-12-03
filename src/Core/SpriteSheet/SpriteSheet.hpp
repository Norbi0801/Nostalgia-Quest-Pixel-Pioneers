//
// Created by Norbert Olkowski on 03.12.2023.
//
#pragma once

#include "../Texture/Texture.hpp"
#include "SFML/Graphics.hpp"

namespace SpriteSheet {

    enum class Direction {
        Right = 0, Left
    };


    class SpriteSheet;

    using Frame = unsigned int;

    class Anim_Base {
        friend class SpriteSheet;

    public:
        Anim_Base();

        virtual ~Anim_Base();

        void Play();

        void Pause();

        void Stop();

        void Reset();

        virtual void Update(const float &l_dT);

        void SetSpriteSheet(SpriteSheet *l_sheet);

        bool IsInAction();

        void SetFrame(const unsigned int &l_frame);

        void SetLooping(const bool &i);

        friend std::stringstream &operator>>(
                std::stringstream &l_stream, Anim_Base &a) {
            a.ReadIn(l_stream);
            return l_stream;
        }

    protected:
        virtual void FrameStep() = 0;

        virtual void CropSprite() = 0;

        virtual void ReadIn(std::stringstream &l_stream) = 0;

        Frame m_frameCurrent;
        Frame m_frameStart;
        Frame m_frameEnd;
        Frame m_frameRow;
        int m_frameActionStart;
        int m_frameActionEnd;
        float m_frameTime;
        float m_elapsedTime;
        bool m_loop;
        bool m_playing;
        std::string m_name;
        SpriteSheet *m_spriteSheet;
    };

    using Animations = std::unordered_map<std::string, Anim_Base *>;

    class SpriteSheet {
    public:
        SpriteSheet(Texture::TextureManager *l_textMgr);

        ~SpriteSheet();

        void CropSprite(const sf::IntRect &l_rect);

        bool LoadSheet(const std::string &l_file);

        void ReleaseSheet();

        void SetSpriteSize(const sf::Vector2i &l_size);

        void SetSpritePosition(const sf::Vector2f &l_pos);

        void SetDirection(const Direction &l_dir);

        Anim_Base *GetCurrentAnim();

        bool SetAnimation(const std::string &l_name,
                          const bool &l_play = false,
                          const bool &l_loop = false);

        void Update(const float &l_dT);

        void Draw(sf::RenderWindow *l_wnd);

        sf::Vector2i GetSpriteSize();

        int GetDirection();

    private:
        std::string m_texture;
        sf::Sprite m_sprite;
        sf::Vector2i m_spriteSize;
        sf::Vector2f m_spriteScale;
        Direction m_direction;
        std::string m_animType;
        Animations m_animations;
        Anim_Base *m_animationCurrent;
        Texture::TextureManager *m_textureManager;
    };

    class Anim_Directional : public Anim_Base{
    protected:
        void FrameStep();
        void CropSprite();
        void ReadIn(std::stringstream& l_stream);
    };
};