//
// Created by agpal on 26/01/2020.
//

#ifndef __CREDITS_SCENE_H__
#define __CREDITS_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class CreditsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(CreditsScene);

    static void publicGoToOptionsMenuScene();
    static void EasterEgg();

private:
    void GoToOptionsMenuScene( cocos2d::Ref *sender );

    cocos2d::Label *labelCredits;

    static Sprite *easterEggSprite;

};


#endif //__CREDITS_SCENE_H__
