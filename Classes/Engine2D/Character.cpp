//
// Created by agpal on 05/02/2020.
//

#include "Character.h"

Character::~Character(){
    cocos2d::log("Character Attack");
    m_characterSprite->removeFromParent();//this->m_node->removeAllChildren();
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
        pos = posNew;
        m_characterSprite->setPosition(pos.x * 32, pos.y * 32);
        labelLife->setPosition(Point(((pos.x + 1) * 32) - 20, ((pos.y + 1) * 32)));
    }
}

void Character::setState(const CharacterState& stateNew) {
    if(stateNew == CharacterState::Selected && m_state == CharacterState::Selectable) {
        m_state = CharacterState::Selected;
    }
    else if(stateNew == CharacterState::UnSelectable && m_state == CharacterState::Attack) {
        m_state = CharacterState::UnSelectable;
    }
    else if(stateNew == CharacterState::Attack && m_state == CharacterState::Selected) {
        m_state = CharacterState::Attack;
    }
    else if(stateNew == CharacterState::UnSelected && m_state == CharacterState::Attack) {
        m_state = CharacterState::UnSelected;
    }
    else if(stateNew == CharacterState::Attack && m_state == CharacterState::UnSelected) {
        m_state = CharacterState::Attack;
    }
    else if(stateNew == CharacterState::Selectable && m_state == CharacterState::UnSelectable) {
        m_state = CharacterState::Selectable;
    }
    else if(stateNew == CharacterState::UnSelectable && m_state == CharacterState::Selected) {
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

float Character::getDamage(const int& character){
    return damage[character];
}

Texture2D* Character::getCharacterSprite(){
    return m_characterSprite->getTexture();
}