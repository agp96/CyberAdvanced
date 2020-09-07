//
// Created by agpal on 05/02/2020.
//

#include "GUI.h"
#include "MainMenuScene.h"
#include "GameData.h"
#include "Engine2D/AudioManager.h"
#include "Definitions.h"

bool GUI::turn = false;
GUI* GUI::gui = NULL;

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

        pause = false;
        finish = false;

        auto labelInfo = Label::createWithBMFont("fonts/BMJapan.fnt",
                                                 "INFO");
        labelInfo->setAnchorPoint(Vec2(1.0f, 1.0f));
        auto infoItem = MenuItemLabel::create(labelInfo,
                                              CC_CALLBACK_1(GUI::GoToInfo, this));
        infoItem->setScale(0.5f);
        infoItem->setPosition( Point( visibleSize.width - visibleSize.width / 5 + origin.x , visibleSize.height - visibleSize.height / 12 + origin.y) );

        info = Menu::create( infoItem, NULL );
        info->setPosition( Point::ZERO );

        m_node->addChild( info );

        auto labelMenu = Label::createWithBMFont("fonts/BMJapan.fnt",
                                                 "MENU");
        labelMenu->setAnchorPoint(Vec2(1.0f, 1.0f));
        auto menuItem = MenuItemLabel::create(labelMenu,
                                              CC_CALLBACK_1(GUI::GoToMainMenuScene, this));
        menuItem->setScale(0.5f);
        menuItem->setPosition( Point( visibleSize.width - visibleSize.width / 14 + origin.x , visibleSize.height - visibleSize.height / 12 + origin.y) );

        menu = Menu::create( menuItem, NULL );
        menu->setPosition( Point::ZERO );

        m_node->addChild( menu );

        auto labelturn = Label::createWithBMFont("fonts/BMJapan.fnt",
                                                 "FINISH TURN");
        auto turnItem = MenuItemLabel::create(labelturn,
                                              CC_CALLBACK_1(GUI::FinishTurn, this));
        turnItem->setScale(0.5f);
        turnItem->setPosition( Point( visibleSize.width - visibleSize.width / 4 + origin.x , visibleSize.height / 2 - visibleSize.height / 3 + origin.y) );

        finishTurn = Menu::create( turnItem, NULL );
        finishTurn->setPosition( Point::ZERO );

        m_node->addChild( finishTurn );

        selectSprite = Sprite::create( "select.png" );
        //cocos2d::log("something5 %f", selectSprite->getContentSize().width);
        //cocos2d::log("something5 %f", selectSprite->getContentSize().height);
        selectSprite->setScale(CC_CONTENT_SCALE_FACTOR());
        //cocos2d::log("something5 %f", selectSprite->getCenterRect().getMinX());
        //cocos2d::log("something5 %f", selectSprite->getCenterRect().getMinY());
        selectSprite->setPosition(Point(POSITION_X_MAP + 16, 50));
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

        //cocos2d::log("levelGUI %i", GameData::getInstance()->getCurrentLevel() );
        if(GameData::getInstance()->getCurrentLevel() == 0) {
            //cocos2d::log("levelGUI1 %i", GameData::getInstance()->getCurrentLevel() );
            tileSprite = Sprite::create("map2.png");
        }
        else {
            //cocos2d::log("levelGUI2 %i", GameData::getInstance()->getCurrentLevel() );
            tileSprite = Sprite::create("map3.png");
        }
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

        characterSprite = Sprite::create("Character/human_player.png");
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

    //cocos2d::log("GUI");
    return m_node;
}

void GUI::setVidas(int vidas){
    m_labelVidas->setString(StringUtils::format("Vidas: %d",vidas));
}

void GUI::updateGUI(const int &tile){

    idTile = tile;
    int def = 0;
    int f = 1;

    //cocos2d::log("updateGUI %d", idTile);

    if (idTile < 5) {
        def = idTile;
    } else if (idTile == 5) {
        def = idTile - 1;
    } else {
        def = 0;
    }

    if (idTile > 16 && idTile < 32) {
        idTile = idTile - 16;
        f = 2;
    } else if (idTile > 32 && idTile < 48) {
        idTile = idTile - 32;
        f = 3;
    }
    std::string s = "DEF " + std::to_string(def);
    labelSprite->setString(s);

    tileSprite->setTextureRect(
            Rect((tileSprite->getTexture()->getContentSize().width / 16) * (idTile - 1),
                 (tileSprite->getTexture()->getContentSize().width / 16) * (f - 1),
                 (tileSprite->getTexture()->getContentSize().width / 16),
                 (tileSprite->getTexture()->getContentSize().width / 16)));

    labelSprite->setVisible(true);
    tileSprite->setVisible(true);

}

void GUI::GoToInfo( cocos2d::Ref *sender )
{

    pause = true;

    info->setEnabled(false);
    menu->setEnabled(false);
    finishTurn->setEnabled(false);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    fondoInfo = LayerGradient::create(Color4B(216, 54, 81, 200), Color4B(216, 54, 81, 200));
    fondoInfo->setContentSize(Size(3392 + 500, visibleSize.height / 2 + 200));
    fondoInfo->setPosition(-500, visibleSize.height / 2 - 170);
    fondoInfo->setLocalZOrder(20);
    m_node->addChild(fondoInfo, 1);

    std::string s;
    if(GameData::getInstance()->getCurrentLevel() == 0) {
        s = "Human: What are those things?\n\n"
            "Pet: It's my food, but big\n\n"
            "Human: Oh I know what could happen, last night I was with\ndifferent experiments to make hair grow, one of them must have spilled\n\n"
            "Pet: I hope they're just as crunchy\n\n\n\n\n\n";
    }
    else{
        s = "Human: We're here to pick up our monthly order,\nmade in the best toilet paper factory in the universe\n\n"
            "Pet: I don't understand why humans need this so much\n\n"
            "Human: If you were more civilized you would understand\nLook! That building has exploded\n\n"
            "Pet: It seems that someone else doesn't make sense of all this\n\n\n\n\n\n";
    }

    labelInfo = Label::createWithBMFont("fonts/Retro Gaming2.fnt",
                                             s+"Say 'Human' or 'Pet' to select your characters\n\n"
                                               "Then select the position where you want to move or attack, for example '4 3' ");
    labelInfo->setScale(0.35f);
    labelInfo->setAnchorPoint(Vec2(0.5f, 0.5f));
    labelInfo->setPosition(origin.x + visibleSize.width*0.5f,
                       origin.y + visibleSize.height*0.6f);
    labelInfo->setLocalZOrder(20);
    m_node->addChild(labelInfo, 1);

    auto labelContinue = Label::createWithBMFont("fonts/BMJapan.fnt",
                                             "CONTINUE");
    labelContinue->setAnchorPoint(Vec2(1.0f, 1.0f));
    auto continueItem = MenuItemLabel::create(labelContinue,
                                          CC_CALLBACK_1(GUI::Continue, this));
    continueItem->setScale(0.5f);
    continueItem->setPosition( Point( visibleSize.width - visibleSize.width / 10 + origin.x , visibleSize.height / 12 + origin.y) );

    cont = Menu::create( continueItem, NULL );
    cont->setPosition( Point::ZERO );
    cont->setLocalZOrder(20);

    m_node->addChild( cont );
}

void GUI::showInfo()
{
    pause = true;

    info->setEnabled(false);
    menu->setEnabled(false);
    finishTurn->setEnabled(false);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    fondoInfo = LayerGradient::create(Color4B(216, 54, 81, 200), Color4B(216, 54, 81, 200));
    fondoInfo->setContentSize(Size(3392 + 500, visibleSize.height / 2 + 200));
    fondoInfo->setPosition(-500, visibleSize.height / 2 - 170);
    fondoInfo->setLocalZOrder(20);
    m_node->addChild(fondoInfo, 1);

    std::string s;
    if(GameData::getInstance()->getCurrentLevel() == 0) {
        s = "Human: What are those things?\n\n"
            "Pet: It's my food, but big\n\n"
            "Human: Oh I know what could happen, last night I was with\ndifferent experiments to make hair grow, one of them must have spilled\n\n"
            "Pet: I hope they're just as crunchy\n\n\n\n\n\n";
    }
    else{
        s = "Human: We're here to pick up our monthly order,\nmade in the best toilet paper factory in the universe\n\n"
            "Pet: I don't understand why humans need this so much\n\n"
            "Human: If you were more civilized you would understand\nLook! That building has exploded\n\n"
            "Pet: It seems that someone else doesn't make sense of all this\n\n\n\n\n\n";
    }

    labelInfo = Label::createWithBMFont("fonts/Retro Gaming2.fnt",
                                        s+"Say 'Human' or 'Pet' to select your characters\n\n"
                                          "Then select the position where you want to move or attack, for example '4 3' ");
    labelInfo->setScale(0.35f);
    labelInfo->setAnchorPoint(Vec2(0.5f, 0.5f));
    labelInfo->setPosition(origin.x + visibleSize.width*0.5f,
                           origin.y + visibleSize.height*0.55f);
    labelInfo->setLocalZOrder(20);
    m_node->addChild(labelInfo, 1);


    auto labelContinue = Label::createWithBMFont("fonts/BMJapan.fnt",
                                                 "CONTINUE");
    labelContinue->setAnchorPoint(Vec2(1.0f, 1.0f));
    auto continueItem = MenuItemLabel::create(labelContinue,
                                              CC_CALLBACK_1(GUI::Continue, this));
    continueItem->setScale(0.5f);
    continueItem->setPosition( Point( visibleSize.width - visibleSize.width / 10 + origin.x , visibleSize.height / 12 + origin.y) );

    cont = Menu::create( continueItem, NULL );
    cont->setPosition( Point::ZERO );
    cont->setLocalZOrder(20);

    m_node->addChild( cont );
}

void GUI::publicGoToInfo()
{

    if(!gui->finish) {
        gui->pause = true;

        gui->info->setEnabled(false);
        gui->menu->setEnabled(false);
        gui->finishTurn->setEnabled(false);

        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        gui->fondoInfo = LayerGradient::create(Color4B(110, 62, 167, 255),
                                               Color4B(73, 10, 206, 255));
        gui->fondoInfo->setContentSize(Size(3392 + 500, visibleSize.height / 2 + 200));
        gui->fondoInfo->setPosition(-500, visibleSize.height / 2 - 170);
        gui->fondoInfo->setLocalZOrder(20);
        gui->m_node->addChild(gui->fondoInfo, 1);

        std::string s;
        if(GameData::getInstance()->getCurrentLevel() == 0) {
            s = "Human: What are those things?\n\n"
                "Pet: It's my food, but big\n\n"
                "Human: Oh I know what could happen, last night I was with\ndifferent experiments to make hair grow, one of them must have spilled\n\n"
                "Pet: I hope they're just as crunchy\n\n\n\n\n\n";
        }
        else{
            s = "Human: We're here to pick up our monthly order,\nmade in the best toilet paper factory in the universe\n\n"
                "Pet: I don't understand why humans need this so much\n\n"
                "Human: If you were more civilized you would understand\nLook! That building has exploded\n\n"
                "Pet: It seems that someone else doesn't make sense of all this\n\n\n\n\n\n";
        }

        gui->labelInfo = Label::createWithBMFont("fonts/Retro Gaming2.fnt",
                                            s+"Say 'Human' or 'Pet' to select your characters\n\n"
                                              "Then select the position where you want to move or attack, for example '4 3' ");
        gui->labelInfo->setScale(0.35f);
        gui->labelInfo->setAnchorPoint(Vec2(0.5f, 0.5f));
        gui->labelInfo->setPosition(origin.x + visibleSize.width * 0.5f,
                                    origin.y + visibleSize.height * 0.55f);
        gui->labelInfo->setLocalZOrder(20);
        gui->m_node->addChild(gui->labelInfo, 1);

        auto labelContinue = Label::createWithBMFont("fonts/BMJapan.fnt",
                                                     "CONTINUE");
        labelContinue->setAnchorPoint(Vec2(1.0f, 1.0f));
        auto continueItem = MenuItemLabel::create(labelContinue,
                                                  CC_CALLBACK_1(GUI::Continue, gui));
        continueItem->setScale(0.5f);
        continueItem->setPosition(Point(visibleSize.width - visibleSize.width / 10 + origin.x,
                                        visibleSize.height / 12 + origin.y));

        gui->cont = Menu::create(continueItem, NULL);
        gui->cont->setPosition(Point::ZERO);
        gui->cont->setLocalZOrder(20);

        gui->m_node->addChild(gui->cont);
    }
}

void GUI::Continue( cocos2d::Ref *sender )
{
    pause = false;

    fondoInfo->setVisible(false);
    labelInfo->setVisible(false);
    cont->setVisible(false);

    info->setEnabled(true);
    menu->setEnabled(true);
    finishTurn->setEnabled(true);

}

void GUI::publicContinue()
{
    if(!gui->finish) {
        gui->pause = false;

        gui->fondoInfo->setVisible(false);
        gui->labelInfo->setVisible(false);
        gui->cont->setVisible(false);

        gui->info->setEnabled(true);
        gui->menu->setEnabled(true);
        gui->finishTurn->setEnabled(true);
    }
}

void GUI::GoToMainMenuScene( cocos2d::Ref *sender )
{
    AudioManager::getInstance()->playSelect();

    auto scene = MainMenuScene::createScene( );

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void GUI::publicGoToMainMenuScene()
{
    if(!gui->pause) {
        AudioManager::getInstance()->playSelect();

        auto scene = MainMenuScene::createScene();

        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}

void GUI::FinishTurn( cocos2d::Ref *sender )
{
    AudioManager::getInstance()->playSelect();

    turn = true;

    disableAttackPosition();
}

void GUI::publicFinishTurn()
{
    if(!gui->finish && !gui->pause) {
        AudioManager::getInstance()->playSelect();

        turn = true;

        gui->disableAttackPosition();
    }
}

bool GUI::getTurn()
{
    return turn;
}

void GUI::setTurn(bool newTurn)
{
    turn = newTurn;
}

bool GUI::getPause()
{
    return pause;
}

bool GUI::getFinish()
{
    return finish;
}

void GUI::setSelectPosition(const Point& newPos)
{
    selectSprite->setPosition(newPos);
}

void GUI::setAttackPosition(const Point& newPos)
{
    bool set = false;
    for (unsigned int i = 0; i < 4; i++) {
        //cocos2d::log("Enemy 4 ");
        if (!attackSprite.at(i)->isVisible() && !set) {
            attackSprite.at(i)->setPosition(
                    Point(POSITION_X_MAP + 16 + (32 * (newPos.x)), 50 + (32 * (newPos.y))));
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

    //cocos2d::log("setLifeLabelGUI %d", lifeCharacterSelect);

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
    nextLevel = -1;
    finish = true;

    auto fondo = LayerGradient::create(Color4B(216, 54, 81, 200), Color4B(216, 54, 81, 200));
    fondo->setContentSize(Size(200, visibleSize.height / 2 + 200));
    fondo->setPosition(origin.x + visibleSize.width*0.5f-100, visibleSize.height / 2 - 170);
    fondo->setLocalZOrder(15);
    m_node->addChild(fondo, 1);

    if(completed) {
        // Etiqueta congratulations
        auto label = Label::createWithBMFont("fonts/BMJapan.fnt",
                                             "YOU WIN!");
        label->setAnchorPoint(Vec2(0.5f, 0.5f));
        label->setPosition(origin.x + visibleSize.width*0.5f,
                           origin.y + visibleSize.height*0.55f);
        label->setScale(0.8f);
        label->setLocalZOrder(20);
        m_node->addChild(label);

        //cocos2d::log("completed %d", completed);
        GameData::getInstance()->unlockLevel(GameData::getInstance()->getCurrentLevel()+1);

    } else {
        auto labelFailed = Label::createWithBMFont("fonts/BMJapan.fnt",
                                                   "YOU LOSE!");
        labelFailed->setAnchorPoint(Vec2(0.5f, 0.5f));
        labelFailed->setPosition(origin.x + visibleSize.width*0.5f,
                                 origin.y + visibleSize.height*0.55f);
        labelFailed->setScale(0.8f);
        labelFailed->setLocalZOrder(20);
        m_node->addChild(labelFailed);
    }

    //cocos2d::log("completed %d", completed);

    auto labelBack = Label::createWithBMFont("fonts/BMJapan.fnt",
                                             "MENU");
    auto backItem = MenuItemLabel::create(labelBack,
                                     CC_CALLBACK_1(GUI::GoToMainMenuScene, this));
    backItem->setScale(0.5f);
    backItem->setVisible(false);
    backItem->setLocalZOrder(20);

    auto labelRepeat = Label::createWithBMFont("fonts/BMJapan.fnt",
                                               "REPEAT");
    auto repeatItem = MenuItemLabel::create(labelRepeat,
                                       CC_CALLBACK_1(GUI::menuTryAgainCallback, this));
    repeatItem->setScale(0.5f);
    repeatItem->setVisible(false);

    auto labelNext = Label::createWithBMFont("fonts/BMJapan.fnt",
                                             "NEXT");
    auto nextItem = MenuItemLabel::create(labelNext,
                                     CC_CALLBACK_1(GUI::menuNextLevelCallback, this));
    nextItem->setScale(0.5f);
    nextItem->setVisible(false);

    if(completed) {
        //cocos2d::log("completed1 %d", completed);
        info->setVisible(false);
        menu->setVisible(false);
        finishTurn->setVisible(false);
        backItem->setVisible(true);
        repeatItem->setVisible(true);
        if(GameData::getInstance()->getCurrentLevel() == 0) {
            nextItem->setVisible(true);
        }
        if(nextItem->isVisible()) {
            auto menu = Menu::create(backItem, repeatItem, nextItem, NULL);
            menu->alignItemsVertically();
            menu->setPosition(origin.x + visibleSize.width*0.5f,
                              origin.y + visibleSize.height*0.4f);
            menu->setLocalZOrder(20);
            m_node->addChild(menu, 1);
        }
        else{
            auto menu = Menu::create(backItem, repeatItem, NULL);
            menu->alignItemsVertically();
            menu->setPosition(origin.x + visibleSize.width*0.5f,
                              origin.y + visibleSize.height*0.4f);
            menu->setLocalZOrder(20);
            m_node->addChild(menu, 1);
        }
    } else {
        //cocos2d::log("completed2 %d", completed);
        info->setVisible(false);
        menu->setVisible(false);
        finishTurn->setVisible(false);
        backItem->setVisible(true);
        repeatItem->setVisible(true);
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
    //cocos2d::log("completedTRY %d", nextLevel);
}

void GUI::publicRepeat() {
    if(gui->finish && !gui->pause) {
        gui->nextLevel = 0;
    }
}

void GUI::menuNextLevelCallback(cocos2d::Ref *pSender) {
    nextLevel = 1;
    GameData::getInstance()->goToLevel(1);
    //cocos2d::log("completedNEXT %d", nextLevel);
}

void GUI::publicNext() {
    if(gui->finish && !gui->pause) {
        gui->nextLevel = 1;
        GameData::getInstance()->goToLevel(1);
    }
}

int GUI::getNextLevel()
{
    return nextLevel;
}

void GUI::getGUI(GUI *g){
    gui = g;
}