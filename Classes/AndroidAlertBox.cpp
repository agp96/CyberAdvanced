//
// Created by agpal on 03/07/2020.
//

#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "cocos2d.h"
#include "AndroidAlertBox.h"
#include "Definitions.h"

void AndroidAlertBox::show(const char *text){
    cocos2d::JniMethodInfo methodInfo;
    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
    "org.cocos2dx.cpp.AndroidAlertBox",
    "show",
    "(Ljava/lang/String;)V")) {
        CCLOG("Could not load method information. Wrong signature?");
        return;
    }
    jstring javaText = methodInfo.env->NewStringUTF(text);
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
                                         methodInfo.methodID,
                                         javaText);
    cocos2d::log("something5 %s", text);
}

bool AndroidAlertBox::IsKeywordDetected(){
    bool tmp = false;

    cocos2d::JniMethodInfo methodInfo;
    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
            "org.cocos2dx.cpp.AndroidAlertBox"
            , "IsKeywordDetected"
            , "()Z"))
    {
        CCLOG("Could not load method information. Wrong signature?");
        return tmp;
    }
    tmp = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
    cocos2d::log("IsKeywordDetected %d", tmp);
    return tmp;
}
