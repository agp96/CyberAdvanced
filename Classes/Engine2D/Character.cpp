//
// Created by agpal on 05/02/2020.
//

#include "Character.h"

Character::~Character(){
    cocos2d::log("Character Attack");
    m_characterSprite->removeFromParent();
    m_characterSprite->release();
    //this->m_node->removeAllChildren();
    labelLife->removeFromParent();
}

const Vec2& Character::getPosition(){
    return m_characterSprite->getPosition();
};

void Character::setPosition(const Vec2& pos) {
    m_characterSprite->setPosition(pos);
}

const Vec2& Character::getMapPos(){
    return pos;
};

void Character::setMapPos(const Vec2& posNew) {
    if(m_state == CharacterState::Selected && posNew != pos) {
        cocos2d::log("Player3 %f", pos.x);
        cocos2d::log("Player3 %f", pos.y);
        pos = posNew;
        m_characterSprite->setPosition(pos.x * 32 + 40, pos.y * 32 + 9);
        if(life < 100) {
            labelLife->setPosition(Point(((pos.x + 1) * 32 + 14), ((pos.y + 1) * 32 + 6)));
        }
    }
}

void Character::setState(const CharacterState& stateNew) {
    if(stateNew == CharacterState::Selected && m_state == CharacterState::Selectable) {
        m_state = CharacterState::Selected;
    }
    if(stateNew == CharacterState::Selected && m_state == CharacterState::UnSelected) {
        m_state = CharacterState::Selected;
    }
    else if(stateNew == CharacterState::Attack && m_state == CharacterState::Selected) {
        m_state = CharacterState::Attack;
    }
    else if(stateNew == CharacterState::UnSelected && m_state == CharacterState::Selected) {
        m_state = CharacterState::UnSelected;
    }
    else if(stateNew == CharacterState::Attack && m_state == CharacterState::UnSelected) {
        m_state = CharacterState::Attack;
    }
    else if(stateNew == CharacterState::Selectable && m_state == CharacterState::UnSelectable) {
        m_state = CharacterState::Selectable;
    }
    else if(stateNew == CharacterState::UnSelectable) {
        m_state = CharacterState::UnSelectable;
    }
}

CharacterState Character::getState() {
    return m_state;
}

int Character::getLife(){
    return life;
}

void Character::setLife(const int& newLife){
    life = newLife;
}

void Character::setLifeLabel(const int& newLife){

    cocos2d::log("setLifeLabelCharacter %i", newLife);

    if(newLife > 0 && newLife < 100){
        setLife(newLife);
    }
    else if(newLife < 0){
        life = 0;
    }

    if(life < 100) {
        labelLife->setPosition(Point(((pos.x + 1) * 32 + 14), ((pos.y + 1) * 32 + 6)));
        cocos2d::log("setLifeLabelCharacter3 %i", life);
        std::string s = __String::createWithFormat("%i", life)->_string;
        labelLife->setString(s);
        if(labelLife->isVisible() == false) {
            labelLife->setVisible(true);
        }
    }
}

float Character::getDamage(const int& character){
    return damage[character];
}

int Character::getRange(){
    return range;
}

Texture2D* Character::getCharacterSprite(){
    return m_characterSprite->getTexture();
}