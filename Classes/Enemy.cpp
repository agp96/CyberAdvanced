//
// Created by agpal on 05/02/2020.
//

#include "Enemy.h"


Enemy::Enemy(const std::string& file, const std::string& type, const Vec2& initPos){

    m_state = CharacterState::Selectable;
    pos = initPos;

    if(type == "domestic"){
        damage[0] = 0.6;
        damage[1] = 0.3;
        damage[2] = 0.5;
        damage[3] = 0.4;
        damage[4] = 0.3;
        fileSprite = "Character/domestic_enemy.png";
        typeCharacter = 0;
    }
    else if(type == "killer"){
        damage[0] = 0.8;
        damage[1] = 0.7;
        damage[2] = 0.9;
        damage[3] = 0.7;
        damage[4] = 0.6;
        fileSprite = "Character/killer_enemy.png";
        typeCharacter = 1;
    }
    else if(type == "pet"){
        damage[0] = 0.6;
        damage[1] = 0.2;
        damage[2] = 0.6;
        damage[3] = 0.5;
        damage[4] = 0.2;
        fileSprite = "Character/pet_enemy.png";
        typeCharacter = 2;
    }
    else if(type == "human"){
        damage[0] = 0.6;
        damage[1] = 0.3;
        damage[2] = 0.6;
        damage[3] = 0.6;
        damage[4] = 0.2;
        fileSprite = "Character/human_enemy.png";
        typeCharacter = 3;
    }
    else if(type == "advanced"){
        damage[0] = 0.95;
        damage[1] = 0.75;
        damage[2] = 0.9;
        damage[3] = 0.8;
        damage[4] = 0.7;
        fileSprite = "Character/advanced_enemy.png";
        typeCharacter = 4;
    }

}

bool Enemy::init(){


    GameEntity::init();
    m_characterSprite = Sprite::create();


    return true;
}

void Enemy::preloadResources(){

    //Cache de sprites
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    //Cache de animaciones
    auto animCache = AnimationCache::getInstance();

    //Si no estaba el spritesheet en la caché lo cargo
    if(!spriteFrameCache->getSpriteFrameByName(fileSprite)) {
        spriteFrameCache->addSpriteFramesWithFile("sprites.plist");
    }

    m_animAndar = Animation::create();
    m_animAndar->addSpriteFrame(spriteFrameCache->getSpriteFrameByName("player.png"));
    m_animAndar->addSpriteFrame(spriteFrameCache->getSpriteFrameByName("player.png"));
    m_animAndar->addSpriteFrame(spriteFrameCache->getSpriteFrameByName("player.png"));
    m_animAndar->setDelayPerUnit(0.1);

    animCache->addAnimation(m_animAndar, "animAndar");

}

Node* Enemy::getNode(){

    if(m_node==NULL){
        m_node= Node::create();

        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        m_characterSprite = Sprite::create( fileSprite );
        m_characterSprite->setScale(CC_CONTENT_SCALE_FACTOR());
        m_characterSprite->setAnchorPoint(Vec2(0, -0.8));
        m_characterSprite->setPosition(Point(pos.x*32, pos.y*32));
        m_node->addChild(m_characterSprite, 1);

        cocos2d::log("Enemy Attack %f", pos.x);
        cocos2d::log("Enemy Attack %f", pos.y);
        std::string s = __String::createWithFormat( "%i", life )->_string;
        labelLife = Label::createWithTTF(s, "fonts/Retro Gaming.ttf", 8);
        labelLife->setPosition( Point(((pos.x+1)*32)-20, ((pos.y+1)*32)) );
        labelLife->setVisible(false);

        m_node->addChild(labelLife, 1);
    }

    return m_node;


}

void Enemy::move() {

    if (pos.x + 1 < 8 && pos.x + 1 > -1 && pos.y + 1 < 8 && pos.y + 1 > -1){
        setState(CharacterState::Selected);
        setMapPos(Point(pos.x + 1, pos.y + 1));
        labelLife->setPosition(Point(((pos.x + 1) * 32) - 20, ((pos.y + 1) * 32)));
        setState(CharacterState::UnSelectable);
    }
}

void Enemy::walk(bool right) {

}

void Enemy::stop() {

}

void Enemy::attack(){

}

void Enemy::setLifeLabel(const int& newLife){
    setLife(newLife);

    if(life < 100) {
        labelLife->setPosition(Point(((pos.x + 1) * 32) - 20, ((pos.y + 1) * 32)));
        std::string s = __String::createWithFormat("%i", life)->_string;
        labelLife->setString(s);
        labelLife->setVisible(true);
    }
}

int Enemy::getCharacterType(){
    return typeCharacter;
}