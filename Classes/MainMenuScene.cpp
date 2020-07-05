//
// Created by agpal on 25/01/2020.
//


#include "MainMenuScene.h"
#include "OptionsMenuScene.h"
#include "MapManager.h"
#include "Definitions.h"

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

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create( "Background.png" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );

    this->addChild( backgroundSprite );

    auto cielo = LayerGradient::create(Color4B(100,100,255,255),Color4B(0,0,100,255));
    cielo->setContentSize(Size(3392+500, visibleSize.height/2+200));
    cielo->setPosition(-500,visibleSize.height/2-170);

    this->addChild( cielo );

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
    auto scene = MapManager::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void MainMenuScene::GoToGameScene2()
{
    auto scene = MapManager::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void MainMenuScene::GoToOptionsScene( cocos2d::Ref *sender )
{
    auto scene = OptionsMenuScene::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void MainMenuScene::menuCloseCallback(cocos2d::Ref *sender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}