//
// Created by agpal on 06/02/2020.
//

#include <cocos/math/CCAffineTransform.h>
#include "MainMenuScene.h"
#include "MapManager.h"
#include "GameProgress.h"
#include "Definitions.h"
#include "Fachada.h"

Scene* MapManager::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MapManager::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

MapManager::~MapManager(){
    m_gui->release();
    m_world->release();
    for(unsigned int i=0;i<numPlayers;i++){
        m_player.at(i)->release();
    }
    for(unsigned int j=0;j<numEnemies;j++){
        m_enemy.at(j)->release();
    }
}

void MapManager::preloadResources(){
    preloadEachGameEntity();
}

void MapManager::start() {
    Node *scrollable = Node::create();

    addEachGameEntityNodeTo(scrollable);

    addChild(scrollable);
    //addChild(m_gui->getNode());
}

// on "init" you need to initialize your instance
bool MapManager::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    Fachada::getInstance()->cambiarEstado(2);

    _level = GameProgress::getInstance()->getCurrentLevel();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    numPlayers = 2;
    numEnemies = 2;

    m_world = World::create();
    m_world->retain();
    addGameEntity(m_world);

    m_gui = GUI::create();
    m_gui->retain();
    addGameEntity(m_gui);

    m_player.push_back(new Player("Character/human.png", "human", Vec2(1,1)));
    m_player.at(0)->retain();
    charactersPos[0][0] = Vec2(1,1);

    m_player.push_back(new Player("Character/pet.png", "pet", Vec2(2,2)));
    m_player.at(1)->retain();
    charactersPos[0][1] = Vec2(2,2);

    m_enemy.push_back(new Enemy("Character/domestic_enemy.png", "domestic", Vec2(3,3)));
    m_enemy.at(0)->retain();
    charactersPos[1][0] = Vec2(3,3);

    m_enemy.push_back(new Enemy("Character/killer_enemy.png", "killer", Vec2(4,4)));
    m_enemy.at(1)->retain();
    charactersPos[1][1] = Vec2(4,4);

    GameManager::init();

    for(unsigned int i = 0; i<2; i++){
        addGameEntity(m_player.at(i));
    }
    for(unsigned int i = 0; i<2; i++){
        addGameEntity(m_enemy.at(i));
    }

    preloadResources();
    start();

    cocos2d::log("Test");
    //this->scheduleUpdate( );

    return true;
}

bool MapManager::onTouchBegan(Touch *touch, cocos2d::Event *event){

    Vec2 v = touch->getLocation();
    Vec2 v2 = touch->getLocationInView();
    log(v.x);
    log(v.y);
    //cocos2d::log("something1 %f", v.x);
    //cocos2d::log("something1 %f", v.y);
    Point p = m_world->tileCoordForPosition(v);
    Point p2 = m_world->tileCoordForPosition(v2);
    Rect r = m_world->tileRectForPosition(p);
    Vec2 v3 = Vec2(v.x, -v.y);
    int idTile = m_world->getTileGIDAtPosition(v);
    //cocos2d::log("something2 %f", p.x);
    //cocos2d::log("something2 %f", p.y);
    cocos2d::log("something2 %f", p2.x);
    cocos2d::log("something2 %f", p2.y);
    //cocos2d::log("something3 %f", r.getMinX());
    //cocos2d::log("something3 %f", r.getMinY());
    //cocos2d::log("something4 %f", selectSprite->getPositionX());
    //cocos2d::log("something4 %f", selectSprite->getPositionY());
    //cocos2d::log("something5 8 %d", m_world->getTileGIDAtPosition(v));
    //cocos2d::log("something5 %d", m_world->getTileGIDAtPosition(p));
    //cocos2d::log("something6 %f", m_world->getTileSize().width);
    //cocos2d::log("something6 %f", m_world->getTileSize().height);

    pos = p2;

    if(p2.x < 8 && p2.x > -1 && p2.y < 8 && p2.y > -1) {
        m_gui->setSelectPosition(Point(POSITION_X_MAP + 16 + (32 * (p2.x)), 51 + (32 *
                                                                                  (p2.y)))); //convertToWorldSpace convertToNodeSpace

        m_gui->updateGUI(idTile);

        if (checkCharacterPos()) {
            m_gui->setCharacterTexture(characterSelect, lifeCharacterSelect);
        } else {
            m_gui->setVisibleTexture();
        }

        bool selected = false;

        for (unsigned int i = 0; i < numPlayers; i++) {
            if (pos.x == m_player.at(i)->getMapPos().x &&
                pos.y == m_player.at(i)->getMapPos().y) {
                cocos2d::log("aaaaaaaaaaaaaaaaaaa1 %f", static_cast<double>(i));
                if (m_player.at(i)->getState() == CharacterState::Selectable ||
                    m_player.at(i)->getState() == CharacterState::UnSelected) {
                    cocos2d::log("aaaaaaaaaaaaaaaaaaa1 %f", static_cast<double>(i));
                    selected = true;
                    //cocos2d::log("Pos s %f", pos.x);
                    //cocos2d::log("Pos s %f", pos.y);
                    //cocos2d::log("Pos s %f", m_player.at(i)->getMapPos().x);
                    //cocos2d::log("Pos s %f", m_player.at(i)->getMapPos().y);
                    unselectOthers();
                    m_player.at(i)->setState(CharacterState::Selected);
                    enemyNear(m_player.at(i)->getMapPos());
                    m_world->changeTiles(m_player.at(i)->getMapPos(), charactersPos,
                                         m_player.at(i)->getCharacterType(),
                                         m_player.at(i)->getRange());
                    //cocos2d::log("Enemy Selectable");
                }
            }
        }
            for (unsigned int i = 0; i < numPlayers; i++) {
                if (!selected) {
                    cocos2d::log("aaaaaaaaaaaaaaaaaaa2 %f", static_cast<double>(i));
                    if (m_player.at(i)->getState() == CharacterState::Selected) {
                        cocos2d::log("aaaaaaaaaaaaaaaaaaa2 %f", static_cast<double>(i));
                        if (checkCorrectPos()) {
                            m_player.at(i)->setMapPos(pos);
                            m_player.at(i)->setState(CharacterState::Attack);
                            enemyNear(m_player.at(i)->getMapPos());
                            m_gui->setCharacterTexture(characterSelect, lifeCharacterSelect);
                            m_world->initialTiles();
                            //cocos2d::log("Enemy Selected");
                        }
                        else if(enemyNear(m_player.at(i)->getMapPos())){
                            m_world->initialTiles();
                            bool attacked = false;
                            for (unsigned int j = 0; j < numEnemies; j++) {
                                if (pos == m_enemy.at(j)->getMapPos()) {
                                    cocos2d::log("attttttack1");
                                    attackPlayer(i, j);
                                    attacked = true;
                                }
                            }
                            if (!attacked) {
                                //cocos2d::log("Enemy Attack");
                                m_gui->disableAttackPosition();
                                m_player.at(i)->setState(CharacterState::UnSelected);
                            }
                        }
                    } else if (m_player.at(i)->getState() == CharacterState::Attack) {
                        m_world->initialTiles();
                        bool attacked = false;
                        for (unsigned int j = 0; j < numEnemies; j++) {
                            if (pos == m_enemy.at(j)->getMapPos() && enemyNear(m_player.at(i)->getMapPos())) {
                                cocos2d::log("attttttack2");
                                attackPlayer(i, j);
                                attacked = true;
                            }
                        }
                        if (!attacked) {
                            //cocos2d::log("Enemy Attack");
                            m_gui->disableAttackPosition();
                            m_player.at(i)->setState(CharacterState::UnSelected);
                        }
                    }
                }
            }
        if(!isSelected()){
            m_world->initialTiles();
        }
    }

    event->stopPropagation();

    return true;
}

void MapManager::onTouchMoved(Touch *touch, cocos2d::Event *event){

}

void MapManager::onTouchEnded(Touch *touch, cocos2d::Event *event){

}

bool MapManager::checkCorrectPos(){

    for (unsigned int i = 0; i < numPlayers; i++) {
        if (pos == m_player.at(i)->getMapPos()) {
            return false;
        }
    }
    for (unsigned int j = 0; j < numEnemies; j++) {
        if (pos == m_enemy.at(j)->getMapPos()) {
            return false;
        }
    }

    return true;
}

bool MapManager::checkCharacterPos(){

    for (unsigned int i = 0; i < numPlayers; i++) {
        if (m_player.at(i)->getMapPos() == pos) {
            characterSelect = m_player.at(i)->getCharacterSprite();
            lifeCharacterSelect = m_player.at(i)->getLife();
            return true;
        }
    }
    for (unsigned int j = 0; j < numEnemies; j++) {
        if (pos == m_enemy.at(j)->getMapPos()) {
            characterSelect = m_enemy.at(j)->getCharacterSprite();
            lifeCharacterSelect = m_enemy.at(j)->getLife();
            return true;
        }
    }

    return false;
}

bool MapManager::checkNextTurn(){

    int players = 0;
    for (unsigned int i = 0; i < numPlayers; i++) {
        if (m_player.at(i)->getState() == CharacterState::UnSelectable) {
            players++;
        }
    }
    if(numPlayers == players){
        return true;
    }
    return false;
}

bool MapManager::enemyNear(const Vec2& posPlayer){

    for (unsigned int j = 0; j < numEnemies; j++) {
        if (posPlayer.x == m_enemy.at(j)->getMapPos().x - 1 ||
                posPlayer.x == m_enemy.at(j)->getMapPos().x + 1 ||
                posPlayer.y == m_enemy.at(j)->getMapPos().y - 1 ||
                posPlayer.y == m_enemy.at(j)->getMapPos().y + 1) {
            if (posPlayer.y == m_enemy.at(j)->getMapPos().y &&
                posPlayer.x == m_enemy.at(j)->getMapPos().x - 1 ||
                posPlayer.y == m_enemy.at(j)->getMapPos().y &&
                posPlayer.x == m_enemy.at(j)->getMapPos().x + 1 ||
                posPlayer.y == m_enemy.at(j)->getMapPos().y - 1 &&
                posPlayer.x == m_enemy.at(j)->getMapPos().x ||
                posPlayer.y == m_enemy.at(j)->getMapPos().y + 1 &&
                posPlayer.x == m_enemy.at(j)->getMapPos().x) {
                m_gui->setAttackPosition(
                        Vec2(m_enemy.at(j)->getMapPos().x, m_enemy.at(j)->getMapPos().y));
                return true;
            }
        }
    }
    return false;
}

void MapManager::updateEachFrame(float delta){

    updateEachGameEntityWithDelta(delta);

    update();

}

void MapManager::update(){

    //cocos2d::log("Pos %d", movement);
    //cocos2d::log("Pos %d", turn);
    //cocos2d::log("Pos %f", pos.x);
    //cocos2d::log("Pos %f", pos.y);
    //cocos2d::log("Pos 2 %f", m_player->getPos().x);
    //cocos2d::log("Pos 2 %f", m_player->getPos().y);
    //cocos2d::log("Pos 2 %f", m_enemy->getPos().x);
    //cocos2d::log("Pos 2 %f", m_enemy->getPos().y);

    if(m_gui->getNextLevel() == 0){
        Director::getInstance()->replaceScene(
                TransitionFadeUp::create(0.5f, MapManager::createScene()));
    }
    else if(m_gui->getNextLevel() == 1){
        GameProgress::getInstance()->goToLevel(GameProgress::getInstance()->getCurrentLevel()+1);
        Director::getInstance()->replaceScene(
                TransitionFlipX::create(0.5f, MapManager::createScene()));
    }
    if(m_gui->getTurn()){
        turn = 1;
        m_gui->setTurn(false);
        cocos2d::log("Turn %d", turn);
    }
    if(turn == 0){
        if(checkNextTurn()) {
            m_world->initialTiles();
            turn = 1;
            turnEnemy();
            for (unsigned int j = 0; j < numEnemies; j++) {
                moveEnemies();
            }
            turnPlayer();
            turn = 0;
        }
    }
    if(turn == 1){
        m_world->initialTiles();
        cocos2d::log("Turn %d", turn);
        turnEnemy();
        for (unsigned int j = 0; j < numEnemies; j++) {
            moveEnemies();
        }
        turnPlayer();
        turn = 0;
    }
}

void MapManager::attackPlayer(unsigned int player, unsigned int enemy){

    int randomEnemy = rand() % 6;
    int randomPlayer = rand() % 6;
    int v1 = rand() % 1;
    int v2 = rand() % 1;

    if(VIBRATION == 1) {
        Device::vibrate(0.1);
    }

    if(v1 == 1){
        randomEnemy = -randomEnemy;
    }
    if(v2 == 1){
        randomPlayer = -randomPlayer;
    }

    cocos2d::log("Life %f", m_player.at(player)->getDamage(m_enemy.at(enemy)->getCharacterType())*m_player.at(player)->getLife());
    cocos2d::log("Life %d", m_enemy.at(enemy)->getLife());

    float damagePlayerToEnemy = m_player.at(player)->getDamage(m_enemy.at(enemy)->getCharacterType())*m_player.at(player)->getLife();
    if(damagePlayerToEnemy > 5) {
        m_enemy.at(enemy)->setLifeLabel(
                m_enemy.at(enemy)->getLife() - damagePlayerToEnemy + randomEnemy);
    }
    else{
        m_enemy.at(enemy)->setLifeLabel(
                m_enemy.at(enemy)->getLife() - damagePlayerToEnemy);
    }

    cocos2d::log("Life %f", m_enemy.at(enemy)->getDamage(m_player.at(player)->getCharacterType()));
    cocos2d::log("Life %d", m_player.at(player)->getLife());
    float damageEnemyToPlayer = m_enemy.at(enemy)->getDamage(m_player.at(player)->getCharacterType())*m_enemy.at(enemy)->getLife();
    if(damageEnemyToPlayer > 5) {
        m_player.at(player)->setLifeLabel(
                m_player.at(player)->getLife() - damageEnemyToPlayer + randomPlayer);
    }
    else{
        m_player.at(player)->setLifeLabel(
                m_player.at(player)->getLife() - damageEnemyToPlayer);
    }

    cocos2d::log("Life %f", damagePlayerToEnemy);
    cocos2d::log("Life %d", randomEnemy);
    cocos2d::log("Life %f", damageEnemyToPlayer);
    cocos2d::log("Life %d", randomPlayer);
    cocos2d::log("Life %d", m_enemy.at(enemy)->getLife());

    m_player.at(player)->setState(CharacterState::UnSelectable);
    m_gui->disableAttackPosition();
    //cocos2d::log("Life %d", m_enemy.at(j)->getLife());

    if(m_enemy.at(enemy)->getLife() <= 0){
        m_enemy.at(enemy)->release();
        removeGameEntity(m_enemy.at(enemy));
        delete(m_enemy.at(enemy));
        m_enemy.erase(m_enemy.begin()+enemy);
        numEnemies = numEnemies-1;
        if(numEnemies == 0){
            m_gui->showFinishMenu(true);
        }
        cocos2d::log("Size %d", m_enemy.size());
    }

    if(m_player.at(player)->getLife() <= 0){
        m_player.at(player)->release();
        removeGameEntity(m_player.at(player));
        delete(m_player.at(player));
        m_player.erase(m_player.begin()+player);
        numPlayers = numPlayers-1;
        if(numPlayers == 0){
            m_gui->showFinishMenu(false);
        }
        cocos2d::log("Size %d", m_player.size());
    }

}

void MapManager::moveEnemies(){
    for (unsigned int j = 0; j < numEnemies; j++) {
        if(m_enemy.at(j)->getState() == CharacterState::Selectable) {
                    cocos2d::log("Enemy Move ");
                    m_enemy.at(j)->move();
        }
    }
}

void MapManager::turnPlayer(){
    for (unsigned int i = 0; i < numPlayers; i++) {
        if(m_player.at(i)->getState() == CharacterState::UnSelectable) {
            m_player.at(i)->setState(CharacterState::Selectable);
        }
    }
}

void MapManager::turnEnemy(){
    for (unsigned int i = 0; i < numPlayers; i++) {
        if(m_player.at(i)->getState() != CharacterState::UnSelectable) {
            m_player.at(i)->setState(CharacterState::UnSelectable);
        }
    }
    for (unsigned int i = 0; i < numEnemies; i++) {
        if(m_enemy.at(i)->getState() == CharacterState::UnSelectable) {
            m_enemy.at(i)->setState(CharacterState::Selectable);
        }
    }
}

void MapManager::GoToMainMenuScene()
{
    auto scene = MainMenuScene::createScene( );

    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

bool MapManager::isSelected()
{
    for (unsigned int i = 0; i < numPlayers; i++) {
        if (m_player.at(i)->getState() == CharacterState::Selected) {
            return true;
        }
    }
    return false;
}


void MapManager::unselectOthers()
{
    for (unsigned int i = 0; i < numPlayers; i++) {
        if (m_player.at(i)->getState() == CharacterState::Selected) {
            m_player.at(i)->setState(CharacterState::UnSelected);
            m_world->initialTiles();
        }
    }
}