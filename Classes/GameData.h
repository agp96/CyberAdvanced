//
// Created by agpal on 07/09/2020.
//

#ifndef PROJ_ANDROID_GAMEDATA_H
#define PROJ_ANDROID_GAMEDATA_H

class GameData {
public:
    static GameData* getInstance();

    void cambiarEstado(int cambiaEstado);
    int getEstado();

    void goToLevel(int);
    void goToLastUnlockedLevel();
    void unlockLevel(int);
    int getCurrentLevel();
    int getFirstInit();
    void setFirstInit();
    std::string getCurrentLevelMap();

private:
    static GameData *instance;
    GameData();

    int estado;
    std::vector<std::string> _levels = { "res/map2.tmx", "res/map3.tmx", "res/map4.tmx" };
    int _currentLevel = 0;
    int _unlockedLevels = 0;
    int _first = 0;
};


#endif //PROJ_ANDROID_GAMEDATA_H
