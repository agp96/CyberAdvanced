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

        private:
        void GoToMainMenuScene( cocos2d::Ref *sender );
        void GoToCreditsScene( cocos2d::Ref *sender );
        void ChangeMusic();
        void ChangeSounds();
        void ChangeVibration();

        cocos2d::MenuItemImage *musicItem;
        cocos2d::MenuItemImage *soundsItem;
        cocos2d::MenuItemImage *vibrationItem;

        bool music = true;
        bool sounds = true;
        bool vibration = true;

    };

#endif // __OPTIONS_MENU_SCENE_H__
