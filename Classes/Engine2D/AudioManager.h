//
// Created by agpal on 26/07/2020.
//

#ifndef PROJ_ANDROID_AUDIOMANAGER_H
#define PROJ_ANDROID_AUDIOMANAGER_H

#include "cocos2d.h"

class AudioManager {

public:
    static AudioManager* getInstance();

    void initAudio();

    static void stopMusic();
    static void stopSounds();

    void playSelect();

private:

    static AudioManager *instance;
    AudioManager();

    bool initON = false;

    static int _id_background_music;
    static bool musicON;
    static bool soundsON;
};


#endif //PROJ_ANDROID_AUDIOMANAGER_H
