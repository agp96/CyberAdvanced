//
// Created by agpal on 07/08/2020.
//

#include <cocos/platform/CCStdC.h>
#include <cocos/base/CCConsole.h>
#include "Game.h"
#include "MapManager.h"

Game* Game::instance = NULL;

Game::Game() {
    estado = 0;
}

Game* Game::getInstance() {
    if(instance==NULL) {
        instance = new Game();
    }
    return instance;
}

void Game::initGame(){

    auto scene = MapManager::create();

    scene->getMP(scene);

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );

}

