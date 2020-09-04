//
// Created by agpal on 21/03/2020.
//

#pragma once

#include "cocos2d.h"

class string;

class GameProgress
{
public:
    static GameProgress* getInstance();

    void goToLevel(int);
    void goToLastUnlockedLevel();
    void unlockLevel(int);
    int getCurrentLevel();
    int getFirstInit();
    void setFirstInit();
    std::string getCurrentLevelMap();

private:
    static GameProgress *instance;
    GameProgress();

    std::vector<std::string> _levels = { "res/map2.tmx", "res/map3.tmx", "res/map4.tmx" };
    int _currentLevel = 0;
    int _unlockedLevels = 0;
    int _first = 0;
};

