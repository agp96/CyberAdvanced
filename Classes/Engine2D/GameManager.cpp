//
// Created by agpal on 30/01/2020.
//

#include "GameManager.h"


bool GameManager::init(){

    //Super
    Scene::init();

    //Update
    this->schedule(schedule_selector(GameManager::updateEachFrame));

    //Creo listeners del teclado
    auto listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameManager::onKeyPressed,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(GameManager::onKeyReleased,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    auto listener1 = cocos2d::EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = CC_CALLBACK_2(GameManager::onTouchBegan ,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);

    listener1 = cocos2d::EventListenerTouchOneByOne::create();
    listener1->onTouchMoved = CC_CALLBACK_2(GameManager::onTouchMoved ,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);

    listener1 = cocos2d::EventListenerTouchOneByOne::create();
    listener1->onTouchEnded = CC_CALLBACK_2(GameManager::onTouchEnded ,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);

    return true;
}

void GameManager::addGameEntity(GameEntity *ge){
    m_gameEntities.pushBack(ge);
}

void GameManager::removeGameEntity(GameEntity *ge){
    m_gameEntities.eraseObject(ge);
}

void GameManager::updateEachGameEntityWithDelta(float delta){
    for (auto e: this->m_gameEntities){
        e->update(delta);
    }
}
void GameManager::preloadEachGameEntity(){
    for (auto e: this->m_gameEntities){
        e->preloadResources();
    }
}
void GameManager::addEachGameEntityNodeTo(Node *node){
    for (auto e: this->m_gameEntities){
        node->addChild(e->getNode());
    }
}


void GameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event){};
void GameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){};

bool GameManager::onTouchBegan(Touch *touch, cocos2d::Event *event){};
void GameManager::onTouchMoved(Touch *touch, cocos2d::Event *event){};
void GameManager::onTouchEnded(Touch *touch, cocos2d::Event *event){};

