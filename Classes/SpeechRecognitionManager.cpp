//
// Created by agpal on 03/07/2020.
//

#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "cocos2d.h"
#include "SpeechRecognitionManager.h"
#include "Definitions.h"


// Android log function wrappers
static const char* kTAG = "SpeechRecognitionManager";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

// processing callback to handler class
typedef struct tick_context {
    JavaVM  *javaVM;
    jclass   jniHelperClz;
    jobject  jniHelperObj;
    jclass   mainActivityClz;
    jobject  mainActivityObj;
    pthread_mutex_t  lock;
    int      done;
} TickContext;
TickContext g_ctx;
std::string keyword;

bool SpeechRecognitionManager::IsKeywordDetected(){
    bool tmp = false;

    cocos2d::JniMethodInfo methodInfo;
    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
            "org.cocos2dx.cpp.SpeechRecognitionManager"
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

extern "C"
JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_SpeechRecognitionManager_callCppCallback(JNIEnv *env, jobject clazz, jstring jStr) {
    // TODO: implement callCppCallback()
    int estado = Fachada::getInstance()->getEstado();
    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);
    keyword = ret;

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    cocos2d::log("Callback %i",estado);
    if(estado == 1){
        if(keyword == "play"){
            MainMenuScene::publicGoToGameScene();
        }
        else if(keyword == "options"){
            MainMenuScene::publicGoToOptionsScene();
        }
        else if(keyword == "exit"){
            MainMenuScene::publicMenuCloseCallback();
        }
    }
    else if(estado == 3){
        if(keyword == "return"){
            OptionsMenuScene::publicGoToMainMenuScene();
        }
        else if(keyword == "music"){
            cocos2d::log("Callback %i",estado);
            OptionsMenuScene::ChangeMusic2();
        }
        else if(keyword == "sounds"){
            OptionsMenuScene::ChangeSounds2();
        }
        else if(keyword == "vibration"){
            OptionsMenuScene::ChangeVibration2();
        }
        else if(keyword == "credits"){
            OptionsMenuScene::publicGoToCreditsScene();
        }
    }
    else if(estado == 4 && keyword == "return"){
        CreditsScene::publicGoToOptionsMenuScene();
    }
    else if(estado == 2){
        if(keyword == "menu") {
            MapManager::GoToMainMenuScene();
        }
        else if(keyword == "finish turn") {
            MapManager::GoToMainMenuScene();
        }
    }
}