//
// Created by agpal on 26/01/2020.
//

#ifndef __CREDITS_SCENE_H__
#define __CREDITS_SCENE_H__

#include "cocos2d.h"

class CreditsScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(CreditsScene);

private:
    void GoToOptionsMenuScene( cocos2d::Ref *sender );

};


#endif //__CREDITS_SCENE_H__
