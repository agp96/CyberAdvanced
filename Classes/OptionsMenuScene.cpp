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

    auto cielo = LayerGradient::create(Color4B(100,100,255,255),Color4B(0,0,100,255));
    cielo->setContentSize(Size(3392+500, visibleSize.height/2+200));
    cielo->setPosition(-500,visibleSize.height/2-170);

    this->addChild( cielo );

    auto labelMusic = Label::createWithBMFont("fonts/BMJapan.fnt",
                                             "MUSIC");

    auto musicLabelItem = MenuItemLabel::create(labelMusic);
    musicLabelItem->setScale(0.5f);
    musicLabelItem->setPosition( Point( visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y + 40) );

    auto labelSound = Label::createWithBMFont("fonts/BMJapan.fnt",
                                              "SOUNDS");
    auto soundsLabelItem = MenuItemLabel::create(labelSound);
    soundsLabelItem->setScale(0.5f);
    soundsLabelItem->setPosition( Point( visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y) );

    auto labelVibration = Label::createWithBMFont("fonts/BMJapan.fnt",
                                              "VIBRATION");
    auto vibrationLabelItem = MenuItemLabel::create(labelVibration);
    vibrationLabelItem->setScale(0.5f);
    vibrationLabelItem->setPosition( Point( visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y - 40) );

    this->addChild( musicLabelItem );
    this->addChild( soundsLabelItem );
    this->addChild( vibrationLabelItem );

    musicItem = MenuItemImage::create( "switch.png", "switchOff.png", CC_CALLBACK_0( OptionsMenuScene::ChangeMusic, this ) );
    musicItem->setPosition( Point( visibleSize.width - visibleSize.width / 3  + origin.x, visibleSize.height / 2 + origin.y + 40) );

    soundsItem = MenuItemImage::create( "switch.png", "switchOff.png", CC_CALLBACK_0( OptionsMenuScene::ChangeSounds, this ) );
    soundsItem->setPosition( Point( visibleSize.width - visibleSize.width / 3  + origin.x, visibleSize.height / 2 + origin.y) );

    vibrationItem = MenuItemImage::create( "switch.png", "switchOff.png", CC_CALLBACK_0( OptionsMenuScene::ChangeVibration, this ) );
    vibrationItem->setPosition( Point( visibleSize.width - visibleSize.width / 3  + origin.x, visibleSize.height / 2 + origin.y - 40) );

    auto labelReturn = Label::createWithBMFont("fonts/BMJapan.fnt",
                                                  "RETURN");
    auto returnItem = MenuItemLabel::create(labelReturn,
                                                    CC_CALLBACK_1(OptionsMenuScene::GoToMainMenuScene, this));
    returnItem->setScale(0.5f);
    returnItem->setPosition( Point( visibleSize.width / 12 + origin.x , visibleSize.height / 2 + origin.y - 140) );

    auto labelCredits = Label::createWithBMFont("fonts/BMJapan.fnt",
                                               "CREDITS");
    auto creditsItem = MenuItemLabel::create(labelCredits,
                                            CC_CALLBACK_1(OptionsMenuScene::GoToCreditsScene, this));
    creditsItem->setScale(0.5f);
    creditsItem->setPosition( Point( visibleSize.width - visibleSize.width / 12 + origin.x , visibleSize.height / 2 + origin.y - 140) );

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

