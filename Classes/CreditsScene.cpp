//
// Created by agpal on 26/01/2020.
//

#include "CreditsScene.h"
#include "OptionsMenuScene.h"
#include "Definitions.h"
#include "Fachada.h"

USING_NS_CC;

Scene* CreditsScene::createScene()
{
    return CreditsScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool CreditsScene::init()
{
    Fachada::getInstance()->cambiarEstado(4);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create( "Background.png" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );

    this->addChild( backgroundSprite );

    auto cielo = LayerGradient::create(Color4B(100,100,255,255),Color4B(0,0,100,255));
    cielo->setContentSize(Size(3392+500, visibleSize.height/2+200));
    cielo->setPosition(-500,visibleSize.height/2-170);

    this->addChild( cielo );

    auto labelReturn = Label::createWithBMFont("fonts/BMJapan.fnt",
                                             "RETURN");
    auto returnItem = MenuItemLabel::create(labelReturn,
                                          CC_CALLBACK_1(CreditsScene::GoToOptionsMenuScene, this));
    returnItem->setScale(0.5f);
    returnItem->setPosition( Point( visibleSize.width / 12 + origin.x , visibleSize.height / 2 + origin.y - 140) );

    auto menu = Menu::create( returnItem, NULL );
    menu->setPosition( Point::ZERO );

    this->addChild( menu );


    return true;
}

void CreditsScene::GoToOptionsMenuScene( cocos2d::Ref *sender )
{
    auto scene = OptionsMenuScene::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void CreditsScene::publicGoToOptionsMenuScene()
{

    auto scene = OptionsMenuScene::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}