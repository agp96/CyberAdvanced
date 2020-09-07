//
// Created by agpal on 25/01/2020.
//

#include "LogoScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* LogoScene::createScene()
{
    return LogoScene::create();
}

bool LogoScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleOnce( schedule_selector( LogoScene::GoToMainMenuScene ), DISPLAY_TIME_SPLASH_SCENE );
    auto backgroundSprite = Sprite::create( "logo.PNG" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );

    this->addChild( backgroundSprite );

    return true;
}

void LogoScene::GoToMainMenuScene( float dt )
{
    auto scene = MainMenuScene::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}