//
// Created by agpal on 07/08/2020.
//

#ifndef PROJ_ANDROID_GAME_H
#define PROJ_ANDROID_GAME_H

#include "Definitions.h"

class Game {
public:
    static Game* getInstance();

    void initGame();

    void goToLevel(int);
    void goToLastUnlockedLevel();
    void unlockLevel(int);
    int getCurrentLevel();
    std::string getCurrentLevelMap();

private:
    static Game *instance;
    Game();

    std::vector<std::string> _levels = { "res/mapa0.tmx", "res/mapa1.tmx", "res/mapa2.tmx" };
    int _currentLevel = 0;
    int _unlockedLevels = 0;
    int estado;
};


#endif //PROJ_ANDROID_GAME_H
