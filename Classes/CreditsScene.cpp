//
// Created by agpal on 26/01/2020.
//

#include "CreditsScene.h"
#include "OptionsMenuScene.h"
#include "Engine2D/AudioManager.h"
#include "Fachada.h"
#include "Definitions.h"

Sprite* CreditsScene::easterEggSprite;

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
    Fachada::getInstance()->cambiarEstado(2);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto cielo = LayerGradient::create(Color4B(110,62,167,255),Color4B(73,10,206,255));
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

    auto creditSprite = Sprite::create( "credits.png" );
    creditSprite->setPosition( Point( visibleSize.width / 3 + origin.x - 15, visibleSize.height / 2 + origin.y + 40) );
    creditSprite->setScale(0.1f);

    this->addChild( creditSprite );

    labelCredits = Label::createWithBMFont("fonts/Retro Gaming2.fnt",
                                        "@agordoprieto");
    labelCredits->setScale(0.5f);
    labelCredits->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 40));

    this->addChild(labelCredits, 1);

    easterEggSprite = Sprite::create( "easterEgg.png" );
    easterEggSprite->setPosition( Point( visibleSize.width + 10 , visibleSize.height / 3 ) );
    easterEggSprite->setScale(CC_CONTENT_SCALE_FACTOR());
    easterEggSprite->setVisible(false);

    this->addChild( easterEggSprite );

    return true;
}

void CreditsScene::GoToOptionsMenuScene( cocos2d::Ref *sender )
{
    AudioManager::getInstance()->playSelect();

    auto scene = OptionsMenuScene::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void CreditsScene::publicGoToOptionsMenuScene()
{

    AudioManager::getInstance()->playSelect();

    auto scene = OptionsMenuScene::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void CreditsScene::EasterEgg()
{

    easterEggSprite->setVisible(true);
    MoveTo *actionMoveTo = MoveTo::create(3, Point( -40 , easterEggSprite->getPositionY() ));
    easterEggSprite->runAction(actionMoveTo);

}