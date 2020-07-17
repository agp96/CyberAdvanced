//
// Created by agpal on 03/07/2020.
//

#ifndef __SpeechRecognitionManager__
#define __SpeechRecognitionManager__

#include <iostream>
#include "cocos2d.h"
#include <map>
#include <functional>

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "MainMenuScene.h"
#include "MapManager.h"
#include "OptionsMenuScene.h"
#include "CreditsScene.h"
#include "Fachada.h"

#endif
class SpeechRecognitionManager{
public:
    void show(const char *text);
    static bool IsKeywordDetected();


};
#endif