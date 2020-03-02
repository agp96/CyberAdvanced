//
// Created by agpal on 26/01/2020.
//

#include <SimpleAudioEngine.h>
#include "OptionsMenuScene.h"
#include "MainMenuScene.h"
#include "CreditsScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* OptionsMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = OptionsMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OptionsMenuScene::init()
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
    cocos2d::log("something5 %f", backgroundSprite->getBoundingBox().size.width);
    cocos2d::log("something5 %f", backgroundSprite->getCenterRect().size.width);
    cocos2d::log("something5 %f", backgroundSprite->getContentSize().width);
    cocos2d::log("something5 %f", backgroundSprite->getContentSize().height);

    auto cielo = LayerGradient::create(Color4B(100,100,255,255),Color4B(0,0,100,255));
    cielo->setContentSize(Size(3392+500, visibleSize.height/2+200));
    cielo->setPosition(-500,visibleSize.height/2-102);

    this->addChild( cielo );

    MenuItemFont::setFontName( "Retro Gaming" );
    MenuItemFont::setFontSize( SCORE_FONT_SIZE );

    auto musicLabel = MenuItemFont::create("Music", CC_CALLBACK_1(OptionsMenuScene::GoToMainMenuScene, this));
    musicLabel->setPosition( Point( visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y + 40) );

    auto soundsLabel = MenuItemFont::create("Sounds", CC_CALLBACK_1(OptionsMenuScene::GoToMainMenuScene, this));
    soundsLabel->setPosition( Point( visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y) );

    auto vibrationLabel = MenuItemFont::create("Vibration", CC_CALLBACK_1(OptionsMenuScene::GoToMainMenuScene, this));
    vibrationLabel->setPosition( Point( visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y - 40) );

    this->addChild( musicLabel );
    this->addChild( soundsLabel );
    this->addChild( vibrationLabel );

    musicItem = MenuItemImage::create( "switch.png", "switchOff.png", CC_CALLBACK_0( OptionsMenuScene::ChangeMusic, this ) );
    musicItem->setPosition( Point( visibleSize.width - visibleSize.width / 3  + origin.x, visibleSize.height / 2 + origin.y + 40) );

    soundsItem = MenuItemImage::create( "switch.png", "switchOff.png", CC_CALLBACK_0( OptionsMenuScene::ChangeSounds, this ) );
    soundsItem->setPosition( Point( visibleSize.width - visibleSize.width / 3  + origin.x, visibleSize.height / 2 + origin.y) );

    vibrationItem = MenuItemImage::create( "switch.png", "switchOff.png", CC_CALLBACK_0( OptionsMenuScene::ChangeVibration, this ) );
    vibrationItem->setPosition( Point( visibleSize.width - visibleSize.width / 3  + origin.x, visibleSize.height / 2 + origin.y - 40) );

    auto returnItem = MenuItemFont::create("Return", CC_CALLBACK_1(OptionsMenuScene::GoToMainMenuScene, this));
    returnItem->setPosition( Point( visibleSize.width / 12 + origin.x , visibleSize.height / 2 + origin.y - 100) );

    auto creditsItem = MenuItemFont::create("Credits", CC_CALLBACK_1(OptionsMenuScene::GoToCreditsScene, this));
    creditsItem->setPosition( Point( visibleSize.width - visibleSize.width / 12 + origin.x , visibleSize.height / 2 + origin.y - 100) );

    auto menu = Menu::create( creditsItem, returnItem, musicItem, soundsItem, vibrationItem, NULL );
    menu->setPosition( Point::ZERO );

    this->addChild( menu );

    return true;
}

void OptionsMenuScene::GoToMainMenuScene( cocos2d::Ref *sender )
{
    auto scene = MainMenuScene::createScene( );

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void OptionsMenuScene::GoToCreditsScene( cocos2d::Ref *sender )
{
    auto scene = CreditsScene::createScene( );

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void OptionsMenuScene::ChangeMusic()
{
    if(music)
    {
        music = false;
        musicItem->setNormalImage(Sprite::create("switchOff.png"));
    }
    else
    {
        music = true;
        musicItem->setNormalImage(Sprite::create("switch.png"));
    }
}

void OptionsMenuScene::ChangeSounds()
{
    if(sounds)
    {
        sounds = false;
        soundsItem->setNormalImage(Sprite::create("switchOff.png"));
    }
    else
    {
        sounds = true;
        soundsItem->setNormalImage(Sprite::create("switch.png"));
    }
}

void OptionsMenuScene::ChangeVibration()
{
    if(vibration)
    {
        vibration = false;
        vibrationItem->setNormalImage(Sprite::create("switchOff.png"));
    }
    else
    {
        vibration = true;
        vibrationItem->setNormalImage(Sprite::create("switch.png"));
    }
}

