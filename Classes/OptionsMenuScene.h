//
// Created by agpal on 26/01/2020.
//

#ifndef __OPTIONS_MENU_SCENE_H__
#define __OPTIONS_MENU_SCENE_H__

#include "cocos2d.h"

class OptionsMenuScene : public cocos2d::Layer
    {
        public:
        // there's no 'id' in cpp, so we recommend returning the class instance pointer
        static cocos2d::Scene* createScene();

        // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
        virtual bool init();

        // implement the "static create()" method manually
        CREATE_FUNC(OptionsMenuScene);

        static void publicGoToMainMenuScene();
        static void publicGoToCreditsScene();
        void ChangeMusic();
        static void ChangeMusic2();
        static void ChangeSounds2();
        static void ChangeVibration2();
        void ChangeSounds();
        void ChangeVibration();

        private:
        void GoToMainMenuScene( cocos2d::Ref *sender );
        void GoToCreditsScene( cocos2d::Ref *sender );

        static cocos2d::MenuItemImage *musicItem;
        static cocos2d::MenuItemImage *soundsItem;
        static cocos2d::MenuItemImage *vibrationItem;

        static bool music;
        static bool sounds;
        static bool vibration;
};

#endif // __OPTIONS_MENU_SCENE_H__
