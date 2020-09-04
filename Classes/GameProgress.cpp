//
// Created by agpal on 21/03/2020.
//

#include "GameProgress.h"

GameProgress* GameProgress::instance = NULL;

GameProgress::GameProgress() {
}

GameProgress* GameProgress::getInstance() {
    if(instance==NULL) {
        instance = new GameProgress();
    }
    return instance;
}

void GameProgress::goToLevel(int level) {
    _currentLevel = std::min(std::max(0, level), _unlockedLevels);
}

void GameProgress::goToLastUnlockedLevel() {
    _currentLevel = _unlockedLevels;
}

void GameProgress::unlockLevel(int level) {
    _unlockedLevels = std::min(std::max(level, _unlockedLevels), (int)_levels.size() - 1);
}

int GameProgress::getCurrentLevel() {
    return _currentLevel;
}

std::string GameProgress::getCurrentLevelMap() {
    return _levels.at(_currentLevel);
}

void GameProgress::setFirstInit() {
    _first++;
}

int GameProgress::getFirstInit() {
    return _first;
}

