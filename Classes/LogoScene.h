//
// Created by agpal on 25/01/2020.
//

#ifndef __LOGOSCENE_H__
#define __LOGOSCENE_H__

#include "cocos2d.h"

class LogoScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(LogoScene);

private:
    void GoToMainMenuScene(float dt);

};


#endif //__LOGOSCENE_H__
