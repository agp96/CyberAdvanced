//
// Created by agpal on 02/02/2020.
//

#include "Player.h"

Player::Player(const std::string& file, const std::string& type, const Vec2& initPos){

    m_state = CharacterState::Selectable;
    Character::pos = initPos;

    if(type == "domestic"){
        range = 4;
        damage[0] = 0.6;
        damage[1] = 0.3;
        damage[2] = 0.5;
        damage[3] = 0.4;
        damage[4] = 0.3;
        fileSprite = "Character/domestic.png";
        typeCharacter = 0;
    }
    else if(type == "killer"){
        range = 3;
        damage[0] = 0.8;
        damage[1] = 0.7;
        damage[2] = 0.9;
        damage[3] = 0.7;
        damage[4] = 0.6;
        fileSprite = "Character/killer.png";
        typeCharacter = 1;
    }
    else if(type == "pet"){
        range = 4;
        damage[0] = 0.6;
        damage[1] = 0.2;
        damage[2] = 0.6;
        damage[3] = 0.5;
        damage[4] = 0.2;
        fileSprite = "Character/pet.png";
        typeCharacter = 2;
    }
    else if(type == "human"){
        range = 3;
        damage[0] = 0.6;
        damage[1] = 0.3;
        damage[2] = 0.6;
        damage[3] = 0.6;
        damage[4] = 0.2;
        fileSprite = "Character/human.png";
        typeCharacter = 3;
    }
    else if(type == "advanced"){
        range = 2;
        damage[0] = 0.95;
        damage[1] = 0.75;
        damage[2] = 0.9;
        damage[3] = 0.8;
        damage[4] = 0.7;
        fileSprite = "Character/advanced.png";
        typeCharacter = 4;
    }
}

bool Player::init(){
    GameEntity::init();
    m_characterSprite = Sprite::create();

    return true;
}

void Player::preloadResources(){

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

Node* Player::getNode(){

    if(m_node==NULL){
        m_node= Node::create();

        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        m_characterSprite = Sprite::create( fileSprite );
        m_characterSprite->setScale(CC_CONTENT_SCALE_FACTOR());
        m_characterSprite->setAnchorPoint(Vec2(0, -0.8));
        m_characterSprite->setPosition(Point(pos.x * 32 + 40, pos.y * 32 + 9));
        m_node->addChild(m_characterSprite, 1);

        //cocos2d::log("Enemy Attack %f", pos.x);
        //cocos2d::log("Enemy Attack %f", pos.y);
        std::string s = __String::createWithFormat( "%i", life )->_string;
        labelLife = Label::createWithBMFont("fonts/Retro Gaming2.fnt",
                                            s);
        labelLife->setScale(0.3f);
        labelLife->setPosition( Point(((pos.x+1)*32)-20, ((pos.y+1)*32)) );
        labelLife->setVisible(false);

        m_node->addChild(labelLife, 1);
    }

    return m_node;


}

void Player::move() {

}

void Player::walk(bool right) {

}

void Player::stop() {

}

void Player::attack(){

}

int Player::getCharacterType(){
    return typeCharacter;
}