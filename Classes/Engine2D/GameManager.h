//
// Created by agpal on 30/01/2020.
//

#pragma once

#include "GameEntity.h"
#include "cocos2d.h"
#include "../../cocos2d/cocos/base/CCEventKeyboard.h"
#include "../../cocos2d/cocos/base/CCEventTouch.h"

USING_NS_CC;

class GameManager: public Scene {

public:
    virtual bool init();

    virtual void preloadResources()=0;
    virtual void updateEachFrame(float delta)=0;

    void addGameEntity(GameEntity *ge);
    void removeGameEntity(GameEntity *ge);

    void updateEachGameEntityWithDelta(float delta);
    void preloadEachGameEntity();
    void addEachGameEntityNodeTo(Node *node);

    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

    virtual bool onTouchBegan(Touch *touch, cocos2d::Event *event);
    virtual void onTouchMoved(Touch *touch, cocos2d::Event *event);
    virtual void onTouchEnded(Touch *touch, cocos2d::Event *event);

private:

    //Source: http://dev.bunnyhero.org/2014/01/cocos2d-x-30-beta-the-new-vector-class/
    Vector<GameEntity*> m_gameEntities;

};


