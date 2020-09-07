//
// Created by agpal on 07/09/2020.
//

#include <cocos/platform/CCStdC.h>
#include <cocos/base/CCConsole.h>
#include "GameData.h"

GameData* GameData::instance = NULL;

GameData::GameData() {
    estado = 0;
}

GameData* GameData::getInstance() {
    if(instance==NULL) {
        instance = new GameData();
    }
    return instance;
}


void GameData::cambiarEstado(int cambiaEstado){
    estado = cambiaEstado;
}

int GameData::getEstado(){
    return estado;
}

void GameData::goToLevel(int level) {
    _currentLevel = std::min(std::max(0, level), _unlockedLevels);
}

void GameData::goToLastUnlockedLevel() {
    _currentLevel = _unlockedLevels;
}

void GameData::unlockLevel(int level) {
    _unlockedLevels = std::min(std::max(level, _unlockedLevels), (int)_levels.size() - 1);
}

int GameData::getCurrentLevel() {
    return _currentLevel;
}

std::string GameData::getCurrentLevelMap() {
    return _levels.at(_currentLevel);
}

void GameData::setFirstInit() {
    _first++;
}

int GameData::getFirstInit() {
    return _first;
}

