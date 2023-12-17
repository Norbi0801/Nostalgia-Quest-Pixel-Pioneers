//
// Created by Norbert Olkowski on 03.12.2023.
//

#include "SpriteSheet.hpp"

namespace SpriteSheet {
    SpriteSheet::SpriteSheet(Texture::TextureManager *l_textMgr)
            : m_textureManager(l_textMgr), m_animationCurrent(nullptr),
              m_spriteScale(1.f, 1.f), m_direction(Direction::Right) {}

    SpriteSheet::~SpriteSheet() { ReleaseSheet(); }

    void SpriteSheet::ReleaseSheet() {
        m_textureManager->ReleaseResource(m_texture);
        m_animationCurrent = nullptr;
        while (m_animations.begin() != m_animations.end()) {
            delete m_animations.begin()->second;
            m_animations.erase(m_animations.begin());
        }
    }

    void SpriteSheet::SetSpriteSize(const sf::Vector2i &l_size) {
        m_spriteSize = l_size;
        m_sprite.setOrigin(m_spriteSize.x / 2, m_spriteSize.y);
    }

    void SpriteSheet::SetSpritePosition(const sf::Vector2f &l_pos) {
        m_sprite.setPosition(l_pos);
    }

    void SpriteSheet::SetDirection(const Direction &l_dir) {
        if (l_dir == m_direction) { return; }
        m_direction = l_dir;
        m_animationCurrent->CropSprite();
    }

    void SpriteSheet::CropSprite(const sf::IntRect &l_rect) {
        m_sprite.setTextureRect(l_rect);
    }

    bool SpriteSheet::SetAnimation(const std::string &l_name,
                                   const bool &l_play, const bool &l_loop) {
        auto itr = m_animations.find(l_name);
        if (itr == m_animations.end()) { return false; }
        if (itr->second == m_animationCurrent) { return false; }
        if (m_animationCurrent) { m_animationCurrent->Stop(); }
        m_animationCurrent = itr->second;
        m_animationCurrent->SetLooping(l_loop);
        if (l_play) { m_animationCurrent->Play(); }
        m_animationCurrent->CropSprite();
        return true;
    }

    void SpriteSheet::Update(const float &l_dT) {
        m_animationCurrent->Update(l_dT);
    }

    void SpriteSheet::Draw(sf::RenderWindow *l_wnd) {
        l_wnd->draw(m_sprite);
    }

    bool SpriteSheet::LoadSheet(const std::string &l_file) {
        std::ifstream sheet;
        sheet.open(Utils::GetWorkingDirectory() + l_file);
        if (sheet.is_open()) {
            ReleaseSheet(); // Release current sheet resources.
            std::string line;
            while (std::getline(sheet, line)) {
                if (line[0] == '|') { continue; }
                std::stringstream keystream(line);
                std::string type;
                keystream >> type;
                if (type == "Texture") {
                    if (!m_texture.empty()) {
                        std::cerr << "! Duplicate texture entries in: "
                                  << l_file << std::endl;
                        continue;
                    }
                    std::string texture;
                    keystream >> texture;
                    if (!m_textureManager->RequireResource(texture)) {
                        std::cerr << "! Could not set up the texture: "
                                  << texture << std::endl;
                        continue;
                    }
                    m_texture = texture;
                    m_sprite.setTexture(*m_textureManager->GetResource(m_texture));
                } else if (type == "Size") {
                    keystream >> m_spriteSize.x >> m_spriteSize.y;
                    SetSpriteSize(m_spriteSize);
                } else if (type == "Scale") {
                    keystream >> m_spriteScale.x >> m_spriteScale.y;
                    m_sprite.setScale(m_spriteScale);
                } else if (type == "AnimationType") {
                    keystream >> m_animType;
                } else if (type == "Animation") {
                    std::string name;
                    keystream >> name;
                    if (m_animations.find(name) != m_animations.end()) {
                        std::cerr << "! Duplicate animation(" << name
                                  << ") in: " << l_file << std::endl;
                        continue;
                    }
                    Anim_Base *anim = nullptr;
                    if (m_animType == "Directional") {
                        anim = new Anim_Directional();
                    } else {
                        std::cerr << "! Unknown animation type: "
                                  << m_animType << std::endl;
                        continue;
                    }
                    keystream >> *anim;
                    anim->SetSpriteSheet(this);
                    anim->SetName(name);
                    anim->Reset();
                    m_animations.emplace(name, anim);
                    if (m_animationCurrent) { continue; }
                    m_animationCurrent = anim;
                    m_animationCurrent->Play();
                }
            }
            sheet.close();
            return true;
        }
        std::cerr << "! Failed loading spritesheet: "
                  << l_file << std::endl;
        return false;
    }

    sf::Vector2i SpriteSheet::GetSpriteSize() {
        return m_spriteSize;
    }

    int SpriteSheet::GetDirection() {
        return 0;
    }

    Anim_Base::Anim_Base() : m_frameCurrent(0), m_frameStart(0),
                             m_frameEnd(0), m_frameRow(0), m_frameTime(0.f),
                             m_elapsedTime(0.f), m_frameActionStart(-1),
                             m_frameActionEnd(-1), m_loop(false), m_playing(false) {}

    Anim_Base::~Anim_Base() {}

    void Anim_Base::SetSpriteSheet(SpriteSheet *l_sheet) {
        m_spriteSheet = l_sheet;
    }

    void Anim_Base::SetFrame(const unsigned int &l_frame) {
        if ((l_frame >= m_frameStart && l_frame <= m_frameEnd) ||
            (l_frame >= m_frameEnd && l_frame <= m_frameStart)) {
            m_frameCurrent = l_frame;
        }
    }

    bool Anim_Base::IsInAction() {
        if (m_frameActionStart == -1 || m_frameActionEnd == -1) {
            return true;
        }
        return (m_frameCurrent >= m_frameActionStart
                && m_frameCurrent <= m_frameActionEnd);
    }

    void Anim_Base::Reset() {
        m_frameCurrent = m_frameStart;
        m_elapsedTime = 0.0f;
        CropSprite();
    }

    void Anim_Base::Update(const float &l_dT) {
        if (!m_playing) { return; }
        m_elapsedTime += l_dT;
        if (m_elapsedTime < m_frameTime) { return; }
        FrameStep();
        CropSprite();
        m_elapsedTime = 0;
    }

    void Anim_Base::Play() { m_playing = true; }

    void Anim_Base::Pause() { m_playing = false; }

    void Anim_Base::Stop() {
        m_playing = false;
        Reset();
    }

    void Anim_Base::SetLooping(const bool &i) {
        m_loop = i;
    }

    void Anim_Base::SetName(std::string& basicString) {
        m_name = basicString;
    }

    void Anim_Directional::CropSprite() {
        sf::IntRect rect(
                m_spriteSheet->GetSpriteSize().x * m_frameCurrent,
                m_spriteSheet->GetSpriteSize().y *
                (m_frameRow + (short) m_spriteSheet->GetDirection()),
                m_spriteSheet->GetSpriteSize().x,
                m_spriteSheet->GetSpriteSize().y);
        m_spriteSheet->CropSprite(rect);
    }

    void Anim_Directional::FrameStep() {
        if (m_frameStart < m_frameEnd) { ++m_frameCurrent; }
        else { --m_frameCurrent; }
        if ((m_frameStart < m_frameEnd && m_frameCurrent > m_frameEnd) ||
            (m_frameStart > m_frameEnd && m_frameCurrent < m_frameEnd)) {
            if (m_loop) {
                m_frameCurrent = m_frameStart;
                return;
            }
            m_frameCurrent = m_frameEnd;
            Pause();
        }
    }

    void Anim_Directional::ReadIn(std::stringstream &l_stream) {
        l_stream >> m_frameStart >> m_frameEnd >> m_frameRow
                 >> m_frameTime >> m_frameActionStart >> m_frameActionEnd;
    }
}