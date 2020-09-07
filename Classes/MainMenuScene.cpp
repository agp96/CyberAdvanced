//
// Created by agpal on 25/01/2020.
//


#include "MainMenuScene.h"
#include "OptionsMenuScene.h"
#include "MapManager.h"
#include "Engine2D/AudioManager.h"
#include "GameData.h"
#include "Game.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    GameData::getInstance()->cambiarEstado(0);
    AudioManager::getInstance()->initAudio();

    auto _listener = EventListenerCustom::create("game_custom_event1", [=](EventCustom* event){
        std::string str("Custom event 1 received, ");

        auto scene = OptionsMenuScene::createScene();

        Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto backgroundSprite = Sprite::create( "gameplayBackground.png" );
    //backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );

    //this->addChild( backgroundSprite );

    auto cielo = LayerGradient::create(Color4B(110,62,167,255),Color4B(73,10,206,255));
    cielo->setContentSize(Size(3392+500, visibleSize.height/2+200));
    cielo->setPosition(-500,visibleSize.height/2-170);

    this->addChild( cielo );

    auto title = Label::createWithBMFont("fonts/OuterSpace.fnt",
                                        "CYBER                        ");
    title->setScale(0.7f);
    title->setAnchorPoint(Vec2(0.5f, 0.5f));
    title->setPosition(origin.x + visibleSize.width*0.5f,
                           origin.y + visibleSize.height*0.9f);
    this->addChild(title);

    auto title2 = Label::createWithBMFont("fonts/OuterSpace.fnt",
                                         "               ADVANCED");
    title2->setScale(0.7f);
    title2->setAnchorPoint(Vec2(0.5f, 0.5f));
    title2->setPosition(origin.x + visibleSize.width*0.5f,
                       origin.y + visibleSize.height*0.8f);
    this->addChild(title2);

    auto characterSprite = Sprite::create("Character/human_player.png");
    characterSprite->setScale(CC_CONTENT_SCALE_FACTOR()*1.4);
    characterSprite->setPosition( Point( visibleSize.width / 5 + origin.x , visibleSize.height / 3 + origin.y)  );

    this->addChild(characterSprite);

    auto characterSprite2 = Sprite::create("Character/pet_player.png");
    characterSprite2->setScale(CC_CONTENT_SCALE_FACTOR()*1.4);
    characterSprite2->setPosition( Point( visibleSize.width / 4 + origin.x , visibleSize.height / 2 + origin.y)  );

    this->addChild(characterSprite2);

    auto characterSprite3 = Sprite::create("Character/level2_kill_enemy.png");
    characterSprite3->setScale(CC_CONTENT_SCALE_FACTOR()*1.4);
    characterSprite3->setPosition( Point( visibleSize.width - visibleSize.width / 5 + origin.x , visibleSize.height / 3 + origin.y)  );

    this->addChild(characterSprite3);

    auto characterSprite4 = Sprite::create("Character/level1_smut_enemy.png");
    characterSprite4->setScale(CC_CONTENT_SCALE_FACTOR()*1.4);
    characterSprite4->setPosition( Point( visibleSize.width - visibleSize.width / 4 + origin.x , visibleSize.height / 2 + origin.y)  );

    this->addChild(characterSprite4);

    auto labelStart = Label::createWithBMFont("fonts/BMJapan.fnt",
                                              "PLAY");
    auto playItem = MenuItemLabel::create(labelStart,
                                          CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    playItem->setScale(0.5f);

    auto labelOptions = Label::createWithBMFont("fonts/BMJapan.fnt",
                                              "OPTIONS");
    auto optionsItem = MenuItemLabel::create(labelOptions,
                                          CC_CALLBACK_1(MainMenuScene::GoToOptionsScene, this));
    optionsItem->setScale(0.5f);

    auto labelExit = Label::createWithBMFont("fonts/BMJapan.fnt",
                                              "EXIT");
    auto exitItem = MenuItemLabel::create(labelExit,
                                          CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
    exitItem->setScale(0.5f);

    auto menu = Menu::create( playItem, optionsItem, exitItem, NULL );
    menu->alignItemsVertically();
    menu->setPosition(origin.x + visibleSize.width*0.5,
                      origin.y + visibleSize.height*0.5);

    this->addChild( menu );

    return true;
}


void MainMenuScene::GoToGameScene( cocos2d::Ref *sender )
{
    AudioManager::getInstance()->playSelect();

    Game::getInstance()->initGame();
}

void MainMenuScene::publicGoToGameScene()
{
    AudioManager::getInstance()->playSelect();

    Game::getInstance()->initGame();

}

void MainMenuScene::GoToOptionsScene( cocos2d::Ref *sender )
{
    AudioManager::getInstance()->playSelect();

    auto scene = OptionsMenuScene::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void MainMenuScene::menuCloseCallback(cocos2d::Ref *sender)
{
    AudioManager::getInstance()->playSelect();

    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

void MainMenuScene::publicGoToOptionsScene()
{

    AudioManager::getInstance()->playSelect();

    EventCustom event("game_custom_event1");
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);

}

void MainMenuScene::publicMenuCloseCallback()
{
    AudioManager::getInstance()->playSelect();

    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}