//
// Created by agpal on 05/02/2020.
//

#include "GUI.h"
#include "MainMenuScene.h"
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
        m_node->addChild(m_labelVidas, 1);


        MenuItemFont::setFontName( "Retro Gaming" );
        MenuItemFont::setFontSize( SCORE_FONT_SIZE );

        auto menuItem = MenuItemFont::create("Menu", CC_CALLBACK_1(GUI::GoToMainMenuScene, this));
        menuItem->setPosition( Point( visibleSize.width - visibleSize.width / 14 + origin.x , visibleSize.height - visibleSize.height / 12 + origin.y) );

        auto menu = Menu::create( menuItem, NULL );
        menu->setPosition( Point::ZERO );

        m_node->addChild( menu );

        auto turnItem = MenuItemFont::create("Finish Turn", CC_CALLBACK_1(GUI::FinishTurn, this));
        turnItem->setPosition( Point( visibleSize.width - visibleSize.width / 4 + origin.x , visibleSize.height / 2 - visibleSize.height / 4 + origin.y) );

        auto finishTurn = Menu::create( turnItem, NULL );
        finishTurn->setPosition( Point::ZERO );

        m_node->addChild( finishTurn );

        selectSprite = Sprite::create( "select.png" );
        cocos2d::log("something5 %f", selectSprite->getContentSize().width);
        cocos2d::log("something5 %f", selectSprite->getContentSize().height);
        selectSprite->setScale(CC_CONTENT_SCALE_FACTOR());
        cocos2d::log("something5 %f", selectSprite->getCenterRect().getMinX());
        cocos2d::log("something5 %f", selectSprite->getCenterRect().getMinY());
        selectSprite->setPosition(Point(16, 41));
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
        tileSprite->setPosition( Point( visibleSize.width - visibleSize.width / 4 + origin.x , visibleSize.height / 2 + origin.y)  );
        tileSprite->setVisible(false);

        m_node->addChild(tileSprite, 1);

        int def = 0;
        std::string s = "DEF "+__String::createWithFormat( "%i", def )->_string;
        labelSprite = Label::createWithTTF(s, "fonts/Retro Gaming.ttf", 12);
        labelSprite->setPosition( Point( visibleSize.width - visibleSize.width / 4 + origin.x , visibleSize.height / 2 - visibleSize.width / 12 + origin.y)  );
        labelSprite->setVisible(false);

        m_node->addChild(labelSprite, 1);

        characterSprite = Sprite::create("player.png");
        characterSprite->setScale(CC_CONTENT_SCALE_FACTOR()*1.4);
        characterSprite->setPosition( Point( visibleSize.width - visibleSize.width / 10 + origin.x , visibleSize.height / 2 + origin.y)  );
        characterSprite->setVisible(false);

        m_node->addChild(characterSprite, 1);
    }

    return m_node;
}

void GUI::setVidas(int vidas){
    m_labelVidas->setString(StringUtils::format("Vidas: %d",vidas));
}

void GUI::updateGUI(const int &tile){
    idTile = tile;
    labelSprite->setVisible(true);
    int def = 0;
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
    std::string s = "DEF "+__String::createWithFormat( "%i", def )->_string;
    labelSprite->setString(s);

    tileSprite->setVisible(true);
    int f = 1;
    if(idTile > 16){
        idTile = idTile - 16;
        f = 2;
    }
    tileSprite->setTextureRect(Rect((tileSprite->getTexture()->getContentSize().width / 16) * (idTile - 1),(tileSprite->getTexture()->getContentSize().width / 16) * (f - 1),(tileSprite->getTexture()->getContentSize().width / 16) ,(tileSprite->getTexture()->getContentSize().width / 16)));


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
                        Point(16 + (32 * (newPos.x)), 41 + (32 * (newPos.y))));
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

void GUI::setCharacterTexture(Texture2D * newTexture)
{
    characterSprite->setTexture(newTexture);
    characterSprite->setVisible(true);
}

void GUI::setVisibleTexture()
{
    characterSprite->setVisible(false);
}