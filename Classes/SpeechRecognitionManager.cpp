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
JNIEXPORT jint JNICALL
Java_org_cocos2dx_cpp_SpeechRecognitionManager_getEstado(JNIEnv *env, jobject thiz) {
    // TODO: implement getEstado()
    return Fachada::getInstance()->getEstado();
}

extern "C"
JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_SpeechRecognitionManager_callCppCallback(JNIEnv *env, jobject clazz, jint numWord, jint x, jint y) {
    // TODO: implement callCppCallback()
    int estado = Fachada::getInstance()->getEstado();
    cocos2d::log("Callback %i",estado);
    Ref* a;
    if(estado == 0){
        if(numWord == 0){
            MainMenuScene::publicGoToGameScene();
        }
        else if(numWord == 1){
            MainMenuScene::publicGoToOptionsScene();
        }
        else if(numWord == 2){
            MainMenuScene::publicMenuCloseCallback();
        }
    }
    else if(estado == 1){
        if(numWord == 0){
            OptionsMenuScene::publicGoToMainMenuScene();
        }
        else if(numWord == 1){
            cocos2d::log("Callback %i",estado);
            OptionsMenuScene::ChangeMusic2();
        }
        else if(numWord == 2){
            OptionsMenuScene::ChangeSounds2();
        }
        else if(numWord == 3){
            OptionsMenuScene::ChangeVibration2();
        }
        else if(numWord == 4){
            OptionsMenuScene::publicGoToCreditsScene();
        }
    }
    else if(estado == 2){
        if(numWord == 0){
            CreditsScene::publicGoToOptionsMenuScene();
        }
        else if(numWord == 1){
            CreditsScene::EasterEgg();
        }
    }
    else if(estado == 3){
        if(numWord == 0 && x == 0 && y == 0) {
            GUI::publicGoToMainMenuScene();
        }
        else if(numWord == 1 && x == 0 && y == 0) {
            GUI::publicFinishTurn();
        }
        else if(numWord == 2 && x == 0 && y == 0) {
            GUI::publicGoToInfo();
        }
        else if(numWord == 3 && x == 0 && y == 0) {
            GUI::publicContinue();
        }
        else if(numWord == 4 && x == 0 && y == 0) {
            GUI::publicRepeat();
        }
        else if(numWord == 5 && x == 0 && y == 0) {
            GUI::publicNext();
        }
        else if(numWord == 0 && x != 0 && y != 0) {
            MapManager::publicSelect(MapManager::mp, x, y);
        }
        else if((numWord == 6 || numWord == 5) && x == 0 && y == 0) {
            MapManager::publicSelectPlayer(MapManager::mp, numWord - 6);
        }
        else if((numWord == 7 || numWord == 5) && x != 0 && y != 0) {
            MapManager::publicMove(MapManager::mp, numWord - 6, x, y);
        }
    }
}