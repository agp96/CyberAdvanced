//
// Created by agpal on 25/01/2020.
//

#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "Definitions.h"
#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);

    static void publicGoToGameScene();
    static void publicMenuCloseCallback();
    static void publicGoToOptionsScene();

private:
    void GoToGameScene(cocos2d::Ref *sender );
    void GoToOptionsScene( cocos2d::Ref *sender );
    void menuCloseCallback( cocos2d::Ref *sender );

};

#endif // __MAIN_MENU_SCENE_H__
