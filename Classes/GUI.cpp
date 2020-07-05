//
// Created by agpal on 05/02/2020.
//

#include "GUI.h"
#include "MainMenuScene.h"
#include "GameProgress.h"
#include "Definitions.h"

bool GUI::init(){
    GameEntity::init();

    return true;
}

void GUI::preloadResources(){
    m_labelVidas = Label::createWithTTF("Vidas:", "fonts/Marker Felt.ttf", 24);
}


Node* GUI::getNode(){
    if(m_node==NULL) {


        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        // position the label on the center of the screen
        m_labelVidas->setPosition(Vec2(origin.x + visibleSize.width/2,
                                       origin.y + visibleSize.height - m_labelVidas->getContentSize().height));

        m_node= Node::create();
        // add the label as a child to this layer, orden de dibujado +1
        //m_node->addChild(m_labelVidas, 1);

        auto labelMenu = Label::createWithBMFont("fonts/BMJapan.fnt",
                                                 "MENU");
        labelMenu->setAnchorPoint(Vec2(1.0f, 1.0f));
        auto menuItem = MenuItemLabel::create(labelMenu,
                                              CC_CALLBACK_1(GUI::GoToMainMenuScene, this));
        menuItem->setScale(0.5f);
        menuItem->setPosition( Point( visibleSize.width - visibleSize.width / 14 + origin.x , visibleSize.height - visibleSize.height / 12 + origin.y) );

        auto menu = Menu::create( menuItem, NULL );
        menu->setPosition( Point::ZERO );

        m_node->addChild( menu );

        auto labelturn = Label::createWithBMFont("fonts/BMJapan.fnt",
                                                 "FINISH TURN");
        auto turnItem = MenuItemLabel::create(labelturn,
                                              CC_CALLBACK_1(GUI::FinishTurn, this));
        turnItem->setScale(0.5f);
        turnItem->setPosition( Point( visibleSize.width - visibleSize.width / 4 + origin.x , visibleSize.height / 2 - visibleSize.height / 3 + origin.y) );

        auto finishTurn = Menu::create( turnItem, NULL );
        finishTurn->setPosition( Point::ZERO );

        m_node->addChild( finishTurn );

        selectSprite = Sprite::create( "select.png" );
        cocos2d::log("something5 %f", selectSprite->getContentSize().width);
        cocos2d::log("something5 %f", selectSprite->getContentSize().height);
        selectSprite->setScale(CC_CONTENT_SCALE_FACTOR());
        cocos2d::log("something5 %f", selectSprite->getCenterRect().getMinX());
        cocos2d::log("something5 %f", selectSprite->getCenterRect().getMinY());
        selectSprite->setPosition(Point(POSITION_X_MAP + 16, 51));
        m_node->addChild( selectSprite );

        attackSprite.push_back(Sprite::create( "attack.png" ));
        attackSprite.push_back(Sprite::create( "attack.png" ));
        attackSprite.push_back(Sprite::create( "attack.png" ));
        attackSprite.push_back(Sprite::create( "attack.png" ));
        attackSprite.at(0)->setScale(CC_CONTENT_SCALE_FACTOR());
        attackSprite.at(1)->setScale(CC_CONTENT_SCALE_FACTOR());
        attackSprite.at(2)->setScale(CC_CONTENT_SCALE_FACTOR());
        attackSprite.at(3)->setScale(CC_CONTENT_SCALE_FACTOR());
        attackSprite.at(0)->setVisible(false);
        attackSprite.at(1)->setVisible(false);
        attackSprite.at(2)->setVisible(false);
        attackSprite.at(3)->setVisible(false);

        m_node->addChild( attackSprite.at(0) );
        m_node->addChild( attackSprite.at(1) );
        m_node->addChild( attackSprite.at(2) );
        m_node->addChild( attackSprite.at(3) );

        tileSprite = Sprite::create("map2.png");
        tileSprite->setScale(CC_CONTENT_SCALE_FACTOR()*1.4);
        tileSprite->setPosition( Point( visibleSize.width / 2 + visibleSize.width / 5 + origin.x , visibleSize.height / 2 + origin.y)  );
        tileSprite->setVisible(false);

        m_node->addChild(tileSprite, 1);

        int def = 0;
        std::string s = "DEF " + std::to_string(def);
        labelSprite = Label::createWithBMFont("fonts/BMJapan.fnt", s);
        labelSprite->setPosition( Point( visibleSize.width / 2 + visibleSize.width / 5 + origin.x , visibleSize.height / 2 - visibleSize.width / 16 + origin.y)  );
        labelSprite->setScale(0.4f);
        labelSprite->setVisible(false);

        m_node->addChild(labelSprite, 1);

        characterSprite = Sprite::create("player.png");
        characterSprite->setScale(CC_CONTENT_SCALE_FACTOR()*1.4);
        characterSprite->setPosition( Point( visibleSize.width - visibleSize.width / 5 + origin.x , visibleSize.height / 2 + origin.y)  );
        characterSprite->setVisible(false);

        m_node->addChild(characterSprite, 1);

        int life = 100;
        std::string s2 = std::to_string(life);
        labelLife = Label::createWithBMFont("fonts/BMJapan.fnt", s2);
        labelLife->setPosition( Point( visibleSize.width - visibleSize.width / 5 + origin.x , visibleSize.height / 2 - visibleSize.width / 16 + origin.y)  );
        labelLife->setScale(0.4f);
        labelLife->setVisible(false);

        m_node->addChild(labelLife, 1);
    }

    return m_node;
}

void GUI::setVidas(int vidas){
    m_labelVidas->setString(StringUtils::format("Vidas: %d",vidas));
}

void GUI::updateGUI(const int &tile){
    idTile = tile;
    int def = 0;
    int f = 1;

    if(idTile > 16 && idTile < 32){
        idTile = idTile - 16;
        f = 2;
    }
    else if(idTile > 32 && idTile < 48){
        idTile = idTile - 32;
        f = 3;
    }

    if(idTile == 1){
        def = 1;
    }
    else if(idTile == 2){
        def = 2;
    }
    else if(idTile == 3){
        def = 3;
    }
    else if(idTile == 5){
        def = 4;
    }
    std::string s = "DEF " + std::to_string(def);
    labelSprite->setString(s);

    tileSprite->setTextureRect(Rect((tileSprite->getTexture()->getContentSize().width / 16) * (idTile - 1),(tileSprite->getTexture()->getContentSize().width / 16) * (f - 1),(tileSprite->getTexture()->getContentSize().width / 16) ,(tileSprite->getTexture()->getContentSize().width / 16)));

    labelSprite->setVisible(true);
    tileSprite->setVisible(true);

}

void GUI::GoToMainMenuScene( cocos2d::Ref *sender )
{
    auto scene = MainMenuScene::createScene( );

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void GUI::FinishTurn( cocos2d::Ref *sender )
{
    turn = true;
}

bool GUI::getTurn()
{
    return turn;
}

void GUI::setTurn(bool newTurn)
{
    turn = newTurn;
}

void GUI::setSelectPosition(const Point& newPos)
{
    selectSprite->setPosition(newPos);
}

void GUI::setAttackPosition(const Point& newPos)
{
    bool set = false;
    for(unsigned int i=0;i<4;i++) {
            cocos2d::log("Enemy 4 ");
            if(!attackSprite.at(i)->isVisible() && !set) {
                attackSprite.at(i)->setPosition(
                        Point(POSITION_X_MAP + 16 + (32 * (newPos.x)), 51 + (32 * (newPos.y))));
                attackSprite.at(i)->setVisible(true);
                set = true;
            }
    }
}

void GUI::disableAttackPosition()
{
    for(unsigned int i=0;i<4;i++) {
        if(attackSprite.at(i)->isVisible()) {
            attackSprite.at(i)->setVisible(false);
        }
    }
}

void GUI::setCharacterTexture(Texture2D * newTexture, int lifeCharacterSelect)
{
    characterSprite->setTexture(newTexture);
    characterSprite->setVisible(true);

    cocos2d::log("IDDDDDDDDDDDD s %d", lifeCharacterSelect);

    std::string s2 = std::to_string(lifeCharacterSelect);
    labelLife->setString(s2);
    labelLife->setVisible(true);
}

void GUI::setVisibleTexture()
{
    characterSprite->setVisible(false);
    labelLife->setVisible(false);
}

void GUI::showFinishMenu(bool completed) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if(completed) {
        // Etiqueta congratulations
        auto label = Label::createWithBMFont("fonts/BMJapan.fnt",
                                             "CONGRATULATIONS!");
        label->setAnchorPoint(Vec2(0.5f, 0.5f));
        label->setPosition(origin.x + visibleSize.width*0.5f,
                           origin.y + visibleSize.height*0.7f);
        label->setScale(0.8f);
        label->setLocalZOrder(20);
        m_node->addChild(label);

        GameProgress::getInstance()->unlockLevel(GameProgress::getInstance()->getCurrentLevel()+1);

    } else {

        auto labelFailed = Label::createWithBMFont("fonts/BMJapan.fnt",
                                                   "YOU FAILED!");
        labelFailed->setAnchorPoint(Vec2(0.5f, 0.5f));
        labelFailed->setPosition(origin.x + visibleSize.width*0.5f,
                                 origin.y + visibleSize.height*0.7f);
        labelFailed->setScale(0.8f);
        labelFailed->setLocalZOrder(20);
        m_node->addChild(labelFailed);
    }

// Menu

    auto labelBack = Label::createWithBMFont("fonts/BMJapan.fnt",
                                             "BACK TO TITLE");
    auto backItem = MenuItemLabel::create(labelBack,
                                          CC_CALLBACK_1(GUI::GoToMainMenuScene, this));
    backItem->setScale(0.5f);

    auto labelRepeat = Label::createWithBMFont("fonts/BMJapan.fnt",
                                               "REPEAT");
    auto repeatItem = MenuItemLabel::create(labelRepeat,
                                            CC_CALLBACK_1(GUI::menuTryAgainCallback, this));
    repeatItem->setScale(0.5f);

    auto labelNext = Label::createWithBMFont("fonts/BMJapan.fnt",
                                             "NEXT");
    auto nextItem = MenuItemLabel::create(labelNext,
                                          CC_CALLBACK_1(GUI::menuNextLevelCallback, this));
    nextItem->setScale(0.5f);

    if(completed) {

        auto menu = Menu::create(backItem, repeatItem, nextItem, NULL);
        menu->alignItemsVertically();
        menu->setPosition(origin.x + visibleSize.width*0.5f,
                          origin.y + visibleSize.height*0.4f);
        menu->setLocalZOrder(20);
        m_node->addChild(menu, 1);
    } else {

        auto menu = Menu::create(backItem, repeatItem, NULL);
        menu->alignItemsVertically();
        menu->setPosition(origin.x + visibleSize.width*0.5f,
                          origin.y + visibleSize.height*0.4f);
        menu->setLocalZOrder(20);
        m_node->addChild(menu, 1);
    }

}

void GUI::menuTryAgainCallback(cocos2d::Ref *pSender) {
    nextLevel = 0;
}

void GUI::menuNextLevelCallback(cocos2d::Ref *pSender) {
    nextLevel = 1;
}

int GUI::getNextLevel()
{
    return nextLevel;
}