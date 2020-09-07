//
// Created by agpal on 26/07/2020.
//

#include "AudioManager.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

using namespace experimental;

bool AudioManager::musicON = true;
bool AudioManager::soundsON = true;
int AudioManager::_id_background_music = 0;

AudioManager* AudioManager::instance = NULL;

AudioManager::AudioManager() {
}

AudioManager* AudioManager::getInstance() {
    if(instance==NULL) {
        instance = new AudioManager();
    }
    return instance;
}

void AudioManager::initAudio(){
    if(!initON) {
        _id_background_music = AudioEngine::play2d("Sounds/Ask_Again_-_Lets_Apocalypse_Later.mp3", true);
        AudioEngine::setVolume(_id_background_music, 0.5);
        AudioEngine::preload("Sounds/select.mp3");
        initON = true;
    }
}

void AudioManager::stopMusic(){
    if(musicON) {
        AudioEngine::pause(_id_background_music);
        musicON = false;
        //cocos2d::log("Stop");
    }
    else{
        AudioEngine::resume(_id_background_music);
        musicON = true;
        //cocos2d::log("Continue");
    }
}

void AudioManager::stopSounds(){
    if(soundsON) {
        soundsON = false;
    }
    else{
        soundsON = true;
    }
}

void AudioManager::playSelect(){
    if(soundsON) {
        AudioEngine::play2d("Sounds/select.mp3");
    }
}