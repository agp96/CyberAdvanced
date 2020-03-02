//
// Created by agpal on 05/02/2020.
//

#pragma once

#define DEBUG false

#define ACTION_ANIM     001
#define ACTION_JUMP     002
#define ACTION_BLINK    003

#include "GameManager.h"

enum CharacterState {
    Selectable,
    Selected,
    UnSelected,
    Attack,
    UnSelectable
};

class Character : public GameEntity{
public:

    ~Character();

    const Vec2& getPosition();
    void setPosition(const Vec2& pos);

    const Vec2& getMapPos();
    void setMapPos(const Vec2& posNew);

    void setState(const CharacterState& stateNew);
    CharacterState getState();

    int getLife();
    void setLife(const int& newLife);

    float getDamage(const int& character);

    Texture2D* getCharacterSprite();

    void move();
    void walk(bool right);
    void stop();
    void attack();
    void die();

protected:
    Sprite *m_characterSprite;
    Animation *m_animAndar;
    CharacterState m_state;
    Label *labelLife;
    int life = 100;
    float damage[5];

    Vec2 pos;


};

