//
// Created by agpal on 02/02/2020.
//

#include "Player.h"

Player::Player(const std::string& file, const std::string& type, const Vec2& initPos){

    m_state = CharacterState::Selectable;
    Character::pos = initPos;

    if(type == "dom"){
        range = 4;
        damage[0] = 0.6;
        damage[1] = 0.3;
        damage[2] = 0.5;
        damage[3] = 0.4;
        damage[4] = 0.3;
        damage[5] = 0.4;
        damage[6] = 0.3;
        damage[7] = 0.4;
        if(file == "") {
            fileSprite = "Character/domestic_player.png";
        }
        else{
            fileSprite = file;
        }
        typeCharacter = 0;
    }
    else if(type == "kill"){
        range = 3;
        damage[0] = 0.8;
        damage[1] = 0.7;
        damage[2] = 0.9;
        damage[3] = 0.8;
        damage[4] = 0.7;
        damage[5] = 0.6;
        damage[6] = 0.7;
        damage[7] = 0.6;
        if(file == "") {
            fileSprite = "Character/killer_player.png";
        }
        else{
            fileSprite = file;
        }
        typeCharacter = 1;
    }
    else if(type == "pet"){
        range = 4;
        damage[0] = 0.5;
        damage[1] = 0.2;
        damage[2] = 0.6;
        damage[3] = 0.4;
        damage[4] = 0.5;
        damage[5] = 0.2;
        damage[6] = 0.6;
        damage[7] = 0.3;
        if(file == "") {
            fileSprite = "Character/pet_player.png";
        }
        else{
            fileSprite = file;
        }
        typeCharacter = 2;
    }
    else if(type == "tpet"){
        range = 4;
        damage[0] = 0.7;
        damage[1] = 0.4;
        damage[2] = 0.7;
        damage[3] = 0.6;
        damage[4] = 0.7;
        damage[5] = 0.3;
        damage[6] = 0.6;
        damage[7] = 0.5;
        if(file == "") {
            fileSprite = "Character/tpet_player.png";
        }
        else{
            fileSprite = file;
        }
        typeCharacter = 3;
    }
    else if(type == "human"){
        range = 3;
        damage[0] = 0.6;
        damage[1] = 0.4;
        damage[2] = 0.6;
        damage[3] = 0.6;
        damage[4] = 0.6;
        damage[5] = 0.2;
        damage[6] = 0.6;
        damage[7] = 0.5;
        if(file == "") {
            fileSprite = "Character/human_player.png";
        }
        else{
            fileSprite = file;
        }
        typeCharacter = 4;
    }
    else if(type == "adv"){
        range = 2;
        damage[0] = 0.95;
        damage[1] = 0.75;
        damage[2] = 0.9;
        damage[3] = 0.9;
        damage[4] = 0.8;
        damage[5] = 0.7;
        damage[6] = 0.9;
        damage[7] = 0.8;
        if(file == "") {
            fileSprite = "Character/advanced_player.png";
        }
        else{
            fileSprite = file;
        }
        typeCharacter = 5;
    }
    else if(type == "mut"){
        range = 4;
        damage[0] = 0.6;
        damage[1] = 0.4;
        damage[2] = 0.6;
        damage[3] = 0.6;
        damage[4] = 0.5;
        damage[5] = 0.3;
        damage[6] = 0.6;
        damage[7] = 0.4;
        if(file == "") {
            fileSprite = "Character/mut_player.png";
        }
        else{
            fileSprite = file;
        }
        typeCharacter = 6;
    }
    else if(type == "smut"){
        range = 2;
        damage[0] = 0.75;
        damage[1] = 0.5;
        damage[2] = 0.7;
        damage[3] = 0.7;
        damage[4] = 0.6;
        damage[5] = 0.5;
        damage[6] = 0.8;
        damage[7] = 0.6;
        if(file == "") {
            fileSprite = "Character/smut_player.png";
        }
        else{
            fileSprite = file;
        }
        typeCharacter = 7;
    }

}

bool Player::init(){
    GameEntity::init();

    return true;
}

void Player::preloadResources(){

    //Cache de sprites
    //auto spriteFrameCache = SpriteFrameCache::getInstance();
    //Cache de animaciones
    //auto animCache = AnimationCache::getInstance();

    //Si no estaba el spritesheet en la caché lo cargo
    //if(!spriteFrameCache->getSpriteFrameByName(fileSprite)) {
    //    spriteFrameCache->addSpriteFramesWithFile("sprites.plist");
    //}

    //m_animAndar = Animation::create();
    //m_animAndar->addSpriteFrame(spriteFrameCache->getSpriteFrameByName("player.png"));
    //m_animAndar->addSpriteFrame(spriteFrameCache->getSpriteFrameByName("player.png"));
    //m_animAndar->addSpriteFrame(spriteFrameCache->getSpriteFrameByName("player.png"));
    //m_animAndar->setDelayPerUnit(0.1);

    //animCache->addAnimation(m_animAndar, "animAndar");

}

Node* Player::getNode(){

    if(m_node==NULL){
        m_node = Node::create();

        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        m_characterSprite = NULL;
        m_characterSprite = Sprite::create(fileSprite);
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