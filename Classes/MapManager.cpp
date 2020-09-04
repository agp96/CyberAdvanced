//
// Created by agpal on 06/02/2020.
//

#include <cocos/math/CCAffineTransform.h>
#include "MainMenuScene.h"
#include "MapManager.h"
#include "GameProgress.h"
#include "OptionsMenuScene.h"
#include "Engine2D/AudioManager.h"
#include "Fachada.h"

MapManager* MapManager::mp = NULL;

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
        cocos2d::log("MapManagerPlayer");
    }
    for(unsigned int j=0;j<numEnemies;j++){
        m_enemy.at(j)->release();
    }

    cocos2d::log("MapManager1");
}

void MapManager::preloadResources(){
    preloadEachGameEntity();
}

void MapManager::start() {
    Node *scrollable = Node::create();
    cocos2d::log("MapManager8");

    addEachGameEntityNodeTo(scrollable);
    cocos2d::log("MapManager8");

    addChild(scrollable);
    cocos2d::log("MapManager8");
    //addChild(m_gui->getNode());
}

// on "init" you need to initialize your instance
bool MapManager::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    Fachada::getInstance()->cambiarEstado(3);

    UserDefault *def = UserDefault::sharedUserDefault();
    if(def->getIntegerForKey("level") == 1){
        GameProgress::getInstance()->goToLevel(1);
    }
    level = GameProgress::getInstance()->getCurrentLevel();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    m_world = World::create();
    m_world->setLevel(level);
    m_world->retain();
    addGameEntity(m_world);

    if(level == 0) {
        m_player.push_back(new Player("Character/human_player.png", "human", Vec2(2, 1)));
        m_player.at(0)->retain();
        charactersPos[0][0] = Vec2(2, 1);

        m_player.push_back(new Player("Character/pet_player.png", "pet", Vec2(1, 1)));
        m_player.at(1)->retain();
        charactersPos[0][1] = Vec2(1, 1);

        m_enemy.push_back(new Enemy("Character/level1_mut_enemy.png", "mut", Vec2(5, 4)));
        m_enemy.at(0)->retain();
        charactersPos[1][0] = Vec2(5, 4);

        m_enemy.push_back(new Enemy("Character/level1_mut_enemy.png", "mut", Vec2(4, 4)));
        m_enemy.at(1)->retain();
        charactersPos[1][1] = Vec2(4, 4);

        m_enemy.push_back(new Enemy("Character/level1_smut_enemy.png", "smut", Vec2(7, 5)));
        m_enemy.at(2)->retain();
        charactersPos[1][2] = Vec2(7, 5);

        m_enemy.push_back(new Enemy("Character/level1_mut_enemy.png", "mut", Vec2(6, 3)));
        m_enemy.at(3)->retain();
        charactersPos[1][3] = Vec2(6, 3);

    }
    else if(level == 1){
        cocos2d::log("level");
        m_player.push_back(new Player("Character/human_player.png", "human", Vec2(4, 2)));
        m_player.at(0)->retain();
        charactersPos[0][0] = Vec2(4, 2);

        m_player.push_back(new Player("Character/pet_player.png", "pet", Vec2(5, 2)));
        m_player.at(1)->retain();
        charactersPos[0][1] = Vec2(5, 2);

        m_enemy.push_back(new Enemy("Character/level2_dom_enemy.png", "dom", Vec2(6, 6)));
        m_enemy.at(0)->retain();
        charactersPos[1][0] = Vec2(3, 6);

        m_enemy.push_back(new Enemy("Character/level2_dom_enemy.png", "dom", Vec2(0, 5)));
        m_enemy.at(1)->retain();
        charactersPos[1][1] = Vec2(0, 5);

        m_enemy.push_back(new Enemy("Character/level2_dom_enemy.png", "dom", Vec2(1, 4)));
        m_enemy.at(2)->retain();
        charactersPos[1][2] = Vec2(1, 4);

        m_enemy.push_back(new Enemy("Character/level2_kill_enemy.png", "kill", Vec2(3, 6)));
        m_enemy.at(3)->retain();
        charactersPos[1][3] = Vec2(3, 6);
    }

    numPlayers = m_player.size();
    numEnemies = m_enemy.size();

    GameManager::init();

    for(unsigned int i = 0; i<numPlayers; i++){
        addGameEntity(m_player.at(i));
    }
    for(unsigned int i = 0; i<numEnemies; i++){
        addGameEntity(m_enemy.at(i));
    }

    m_gui = GUI::create();
    m_gui->retain();
    addGameEntity(m_gui);
    m_gui->getGUI(m_gui);

    cocos2d::log("MapManager7");
    preloadResources();
    cocos2d::log("MapManager8");
    start();

    cocos2d::log("Test");
    //this->scheduleUpdate( );k

    m_gui->setSelectPosition(Point(POSITION_X_MAP + 16, 50));
    m_gui->updateGUI(level+2);

    if(GameProgress::getInstance()->getFirstInit() == 0 && level == 0){
        m_gui->showInfo();
        GameProgress::getInstance()->setFirstInit();
    }
    else if(GameProgress::getInstance()->getFirstInit() == 1 && level == 1){
        m_gui->showInfo();
        GameProgress::getInstance()->setFirstInit();
    }

    //characterSelect = m_player.at(0)->getCharacterSprite();
    //lifeCharacterSelect = m_player.at(0)->getLife();
    //m_gui->setCharacterTexture(characterSelect, lifeCharacterSelect);

    return true;
}

void MapManager::initLevel(int lvl, int mod){

    level = lvl;
    mode = mod;
}

bool MapManager::onTouchBegan(Touch *touch, cocos2d::Event *event){

    if(!m_gui->getFinish() && !m_gui->getPause()) {
        Vec2 v = touch->getLocation();
        Vec2 v2 = touch->getLocationInView();
        log(v.x);
        log(v.y);
        cocos2d::log("something1 %f", v.x);
        cocos2d::log("something1 %f", v.y);
        Point p = m_world->tileCoordForPosition(v);
        Point p2 = m_world->tileCoordForPosition(v2);
        Rect r = m_world->tileRectForPosition(p);
        Vec2 v3 = Vec2(v.x, -v.y);
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

        if (p2.x < 8 && p2.x > -1 && p2.y < 8 && p2.y > -1) {

            bool selected = false;

            for (unsigned int i = 0; i < numPlayers; i++) {
                if (pos.x == m_player.at(i)->getMapPos().x &&
                    pos.y == m_player.at(i)->getMapPos().y) {
                    cocos2d::log("aaaaaaaaaaaaaaaaaaa1 %f", static_cast<double>(i));
                    if (m_player.at(i)->getState() == CharacterState::Selectable ||
                        m_player.at(i)->getState() == CharacterState::UnSelected ||
                        m_player.at(i)->getState() == CharacterState::Attack) {
                        cocos2d::log("aaaaaaaaaaaaaaaaaaa1 %f", static_cast<double>(i));
                        selected = true;
                        //cocos2d::log("Pos s %f", pos.x);
                        //cocos2d::log("Pos s %f", pos.y);
                        //cocos2d::log("Pos s %f", m_player.at(i)->getMapPos().x);
                        //cocos2d::log("Pos s %f", m_player.at(i)->getMapPos().y);
                        unselectOthers();
                        m_gui->disableAttackPosition();
                        m_player.at(i)->setState(CharacterState::Selected);
                        enemyNear(m_player.at(i)->getMapPos());
                        m_world->changeTiles2(m_player.at(i)->getMapPos(), charactersPos,
                                              numPlayers, numEnemies,
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
                        if (checkCorrectPos(pos) && checkCorrectRange(pos)) {
                            cocos2d::log("aaaaaaaaaaaaaaaaaaa2 %f", static_cast<double>(i));
                            m_player.at(i)->setMapPos(pos);
                            charactersPos[0][i] = m_player.at(i)->getMapPos();
                            m_player.at(i)->setState(CharacterState::Attack);
                            m_gui->disableAttackPosition();
                            enemyNear(m_player.at(i)->getMapPos());
                            m_gui->setCharacterTexture(characterSelect, lifeCharacterSelect);
                            m_world->initialTiles();
                            cocos2d::log("isSelected1 ");
                            //cocos2d::log("Enemy Selected");
                        } else if (enemyNear(m_player.at(i)->getMapPos())) {
                            m_world->initialTiles();
                            bool attacked = false;
                            for (unsigned int j = 0; j < numEnemies; j++) {
                                if (pos == m_enemy.at(j)->getMapPos() && enemyNearAttack(m_player.at(i)->getMapPos(),
                                                                                         m_enemy.at(j)->getMapPos())) {
                                    cocos2d::log("attttttack1");
                                    attackPlayer(i, j, m_player.at(i)->getMapPos(),
                                                 m_enemy.at(j)->getMapPos());
                                    attacked = true;
                                }
                            }
                            if (!attacked) {
                                //cocos2d::log("Enemy Attack");
                                m_gui->disableAttackPosition();
                                m_player.at(i)->setState(CharacterState::UnSelected);
                            }
                        }
                    } else if (m_player.at(i)->getState() == CharacterState::Selected ||
                               m_player.at(i)->getState() == CharacterState::Attack) {
                        bool attacked = false;
                        for (unsigned int j = 0; j < numEnemies; j++) {
                            if (pos == m_enemy.at(j)->getMapPos() &&
                                enemyNear(m_player.at(i)->getMapPos()) && enemyNearAttack(m_player.at(i)->getMapPos(),
                                                                                         m_enemy.at(j)->getMapPos())) {
                                cocos2d::log("attttttack2");
                                attackPlayer(i, j, m_player.at(i)->getMapPos(),
                                             m_enemy.at(j)->getMapPos());
                                m_world->initialTiles();
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
            if (!isSelected()) {
                cocos2d::log("isSelected ");
                m_world->initialTiles();
            }

            int idTile = m_world->getTileGIDAtPosition(v);
            m_gui->setSelectPosition(Point(POSITION_X_MAP + 16 + (32 * (p2.x)), 50 + (32 *
                                                                                      (p2.y)))); //convertToWorldSpace convertToNodeSpace
            m_gui->updateGUI(idTile);

            cocos2d::log("something1 %d", idTile);

            if (checkCharacterPos()) {
                m_gui->setCharacterTexture(characterSelect, lifeCharacterSelect);
            } else {
                m_gui->setVisibleTexture();
            }
        }
    }
    event->stopPropagation();

    return true;
}

void MapManager::onTouchMoved(Touch *touch, cocos2d::Event *event){

}

void MapManager::onTouchEnded(Touch *touch, cocos2d::Event *event){

}

bool MapManager::checkCorrectPos(const Vec2& p){

    cocos2d::log("checkCorrectPos %d", numPlayers);
    cocos2d::log("checkCorrectPos %d", numEnemies);
    cocos2d::log("checkCorrectPos %d", pos.x);
    cocos2d::log("checkCorrectPos %d", pos.y);

    for (unsigned int i = 0; i < numPlayers; i++) {
        if (p == m_player.at(i)->getMapPos()) {
            cocos2d::log("checkCorrectPos1");
            return false;
        }
    }
    for (unsigned int j = 0; j < numEnemies; j++) {
        if (p == m_enemy.at(j)->getMapPos()) {
            cocos2d::log("checkCorrectPos2");
            return false;
        }
    }

    return true;
}

bool MapManager::checkCorrectRange(const Vec2& p){

    bool correct = false;

    for (unsigned int k = 0; k < m_world->getMoveMap().size(); k++) {
        if (p.x == m_world->getMoveMap().at(k)->x && p.y == 7-m_world->getMoveMap().at(k)->y) {
            cocos2d::log("checkCorrectPos32 %f", m_world->getMoveMap().at(k)->x);
            cocos2d::log("checkCorrectPos32 %f", m_world->getMoveMap().at(k)->y);
            correct = true;
        }
    }

    return correct;
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

    cocos2d::log("Players4 %f", static_cast<double>(numPlayers));
    bool pasa = false;
    for (unsigned int j = 0; j < numEnemies; j++) {
        if (posPlayer.x == m_enemy.at(j)->getMapPos().x - 1 ||
                posPlayer.x == m_enemy.at(j)->getMapPos().x + 1 ||
                posPlayer.y == m_enemy.at(j)->getMapPos().y - 1 ||
                posPlayer.y == m_enemy.at(j)->getMapPos().y + 1) {
            cocos2d::log("Players4 %f", static_cast<double>(j));
            if ((posPlayer.y == m_enemy.at(j)->getMapPos().y &&
                posPlayer.x == m_enemy.at(j)->getMapPos().x - 1) ||
                    (posPlayer.y == m_enemy.at(j)->getMapPos().y &&
                posPlayer.x == m_enemy.at(j)->getMapPos().x + 1) ||
                    (posPlayer.y == m_enemy.at(j)->getMapPos().y - 1 &&
                posPlayer.x == m_enemy.at(j)->getMapPos().x) ||
                    (posPlayer.y == m_enemy.at(j)->getMapPos().y + 1 &&
                posPlayer.x == m_enemy.at(j)->getMapPos().x)) {
                m_gui->setAttackPosition(
                        Vec2(m_enemy.at(j)->getMapPos().x, m_enemy.at(j)->getMapPos().y));
                cocos2d::log("Players45 %f", static_cast<double>(j));
                pasa = true;
            }
        }
    }
    if(pasa){
        return true;
    }
    return false;
}


bool MapManager::enemyNearAttack(const Vec2& posPlayer, const Vec2& posEnemy){

    cocos2d::log("Players4 %f", static_cast<double>(numPlayers));
    bool pasa = false;
        if (posPlayer.x == posEnemy.x - 1 ||
            posPlayer.x == posEnemy.x + 1 ||
            posPlayer.y == posEnemy.y - 1 ||
            posPlayer.y == posEnemy.y + 1) {
            if ((posPlayer.y == posEnemy.y &&
                 posPlayer.x == posEnemy.x - 1) ||
                (posPlayer.y == posEnemy.y &&
                 posPlayer.x == posEnemy.x + 1) ||
                (posPlayer.y == posEnemy.y - 1 &&
                 posPlayer.x == posEnemy.x) ||
                (posPlayer.y == posEnemy.y + 1 &&
                 posPlayer.x == posEnemy.x)) {
                pasa = true;
            }
        }
    if(pasa){
        return true;
    }
    return false;
}

int MapManager::playerNear(const Vec2& posEnemy){

    for (unsigned int j = 0; j < numPlayers; j++) {
        if (posEnemy.x == m_player.at(j)->getMapPos().x - 1 ||
                posEnemy.x == m_player.at(j)->getMapPos().x + 1 ||
                posEnemy.y == m_player.at(j)->getMapPos().y - 1 ||
                posEnemy.y == m_player.at(j)->getMapPos().y + 1) {
            if ((posEnemy.y == m_player.at(j)->getMapPos().y &&
                    posEnemy.x == m_player.at(j)->getMapPos().x - 1) ||
                (posEnemy.y == m_player.at(j)->getMapPos().y &&
                        posEnemy.x == m_player.at(j)->getMapPos().x + 1) ||
                (posEnemy.y == m_player.at(j)->getMapPos().y - 1 &&
                        posEnemy.x == m_player.at(j)->getMapPos().x) ||
                (posEnemy.y == m_player.at(j)->getMapPos().y + 1 &&
                        posEnemy.x == m_player.at(j)->getMapPos().x)) {
                return j;
            }
        }
    }

    return -1;
}

bool MapManager::playerNearAttack(const Vec2& posEnemy, const Vec2& posPlayer){

    cocos2d::log("Players4 %f", static_cast<double>(numPlayers));
    bool pasa = false;
    if (posPlayer.x == posEnemy.x - 1 ||
        posPlayer.x == posEnemy.x + 1 ||
        posPlayer.y == posEnemy.y - 1 ||
        posPlayer.y == posEnemy.y + 1) {
        if ((posPlayer.y == posEnemy.y &&
             posPlayer.x == posEnemy.x - 1) ||
            (posPlayer.y == posEnemy.y &&
             posPlayer.x == posEnemy.x + 1) ||
            (posPlayer.y == posEnemy.y - 1 &&
             posPlayer.x == posEnemy.x) ||
            (posPlayer.y == posEnemy.y + 1 &&
             posPlayer.x == posEnemy.x)) {
            pasa = true;
        }
    }
    if(pasa){
        return true;
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

    if(m_gui->getFinish() && m_gui->getNextLevel() == 0){
        //Director::getInstance()->getRunningScene()->release();
        //Director::getInstance()->getRunningScene()->removeAllChildrenWithCleanup(true);
        Director::getInstance()->replaceScene(
                TransitionFadeUp::create(0.5f, MapManager::createScene()));
        cocos2d::log("completedTRY %d", level);
        level = 0;
    }
    else if(m_gui->getNextLevel() == 1 && m_gui->getFinish()){
        cocos2d::log("completedNEXT %d", level);
            level = 1;
            UserDefault *def = UserDefault::sharedUserDefault();
            def->setIntegerForKey("level", 1);
            Director::getInstance()->replaceScene(
                    TransitionFadeUp::create(0.5f, MapManager::createScene()));
    }

    if(m_gui->getTurn()){
        turn = 1;
        m_gui->setTurn(false);
        cocos2d::log("Turn %d", turn);
    }
    if(turn == 0 && !m_gui->getFinish()){
        if(checkNextTurn()) {
            m_world->initialTiles();
            turn = 1;
            turnEnemy();
            moveEnemies();
            turnPlayer();
            turn = 0;
        }
    }
    if(turn == 1 && !m_gui->getFinish()){
        m_world->initialTiles();
        cocos2d::log("Turn %d", turn);
        turnEnemy();
        moveEnemies();
        turnPlayer();
        turn = 0;
    }
}

void MapManager::attackPlayer(unsigned int player, unsigned int enemy, Vec2 posP, Vec2 posE){

    int randomEnemy = rand() % 6;
    int randomPlayer = rand() % 6;
    int v1 = rand() % 1;
    int v2 = rand() % 1;
    int defPlayer = m_world->getDefenseAt(posP.x, posP.y);
    int defEnemy = m_world->getDefenseAt(posE.x, posE.y);
    int diffPlayer = (defPlayer-defEnemy)*10;
    int diffEnemy = (defEnemy-defPlayer)*10;

    if(OptionsMenuScene::vibration == 1) {
        Device::vibrate(0.1);
    }

    if(v1 == 1){
        randomEnemy = -randomEnemy;
    }
    if(v2 == 1){
        randomPlayer = -randomPlayer;
    }

    cocos2d::log("Def %d", defPlayer);
    cocos2d::log("Def %d", defEnemy);
    cocos2d::log("Random %d", randomEnemy);
    cocos2d::log("Random %d", randomPlayer);

    cocos2d::log("Life %f", m_player.at(player)->getDamage(m_enemy.at(enemy)->getCharacterType()));
    cocos2d::log("Life %d", m_enemy.at(enemy)->getLife());

    float damagePlayerToEnemy = m_player.at(player)->getDamage(m_enemy.at(enemy)->getCharacterType())*m_player.at(player)->getLife();
    cocos2d::log("Damage %f", damagePlayerToEnemy);
    cocos2d::log("Def %f", (diffPlayer * damagePlayerToEnemy) / 100);
    damagePlayerToEnemy = damagePlayerToEnemy + ((diffPlayer * damagePlayerToEnemy) / 100);
    if(damagePlayerToEnemy > 5) {
        m_enemy.at(enemy)->setLifeLabel(
                m_enemy.at(enemy)->getLife() - damagePlayerToEnemy + randomEnemy);
        cocos2d::log("Damage2 %f", m_enemy.at(enemy)->getLife() - damagePlayerToEnemy + randomEnemy);
    }
    else{
        cocos2d::log("Damage3 %f", m_enemy.at(enemy)->getLife() - damagePlayerToEnemy);
        m_enemy.at(enemy)->setLifeLabel(
                m_enemy.at(enemy)->getLife() - damagePlayerToEnemy);
    }

    cocos2d::log("Life %f", m_enemy.at(enemy)->getDamage(m_player.at(player)->getCharacterType()));
    cocos2d::log("Life %d", m_player.at(player)->getLife());
    float damageEnemyToPlayer = m_enemy.at(enemy)->getDamage(m_player.at(player)->getCharacterType())*m_enemy.at(enemy)->getLife();
    cocos2d::log("Damage %f", damageEnemyToPlayer);
    cocos2d::log("Def %f", (diffEnemy * damageEnemyToPlayer) / 100);
    damageEnemyToPlayer = damageEnemyToPlayer + ((diffEnemy * damageEnemyToPlayer) / 100);
    if(damageEnemyToPlayer > 5) {
        m_player.at(player)->setLifeLabel(
                m_player.at(player)->getLife() - damageEnemyToPlayer + randomPlayer);
        cocos2d::log("Damage %f", damageEnemyToPlayer + randomPlayer);
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
        charactersPos[1][enemy] = Vec2(-1,-1);
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
        charactersPos[0][player] = Vec2(-1,-1);
        cocos2d::log("Size %d", m_player.size());
    }

}

void MapManager::attackEnemy(unsigned int player, unsigned int enemy, Vec2 posP, Vec2 posE){

    int randomEnemy = rand() % 6;
    int randomPlayer = rand() % 6;
    int v1 = rand() % 1;
    int v2 = rand() % 1;
    int defPlayer = m_world->getDefenseAt(posP.x, posP.y);
    int defEnemy = m_world->getDefenseAt(posE.x, posE.y);
    int diffPlayer = (defPlayer-defEnemy)*10;
    int diffEnemy = (defEnemy-defPlayer)*10;

    if(OptionsMenuScene::vibration == 1) {
        Device::vibrate(0.1);
    }

    if(v1 == 1){
        randomEnemy = -randomEnemy;
    }
    if(v2 == 1){
        randomPlayer = -randomPlayer;
    }

    cocos2d::log("Def %d", defPlayer);
    cocos2d::log("Def %d", defEnemy);
    cocos2d::log("Random %d", randomEnemy);
    cocos2d::log("Random %d", randomPlayer);

    cocos2d::log("Life %f", m_enemy.at(enemy)->getDamage(m_player.at(player)->getCharacterType()));
    cocos2d::log("Life %d", m_player.at(player)->getLife());
    float damageEnemyToPlayer = m_enemy.at(enemy)->getDamage(m_player.at(player)->getCharacterType())*m_enemy.at(enemy)->getLife();
    cocos2d::log("Damage %f", damageEnemyToPlayer);
    cocos2d::log("Def %f", (diffEnemy * damageEnemyToPlayer) / 100);
    damageEnemyToPlayer = damageEnemyToPlayer + ((diffEnemy * damageEnemyToPlayer) / 100);
    if(damageEnemyToPlayer > 5) {
        m_player.at(player)->setLifeLabel(
                m_player.at(player)->getLife() - damageEnemyToPlayer + randomPlayer);
        cocos2d::log("Damage %f", damageEnemyToPlayer + randomPlayer);
    }
    else{
        m_player.at(player)->setLifeLabel(
                m_player.at(player)->getLife() - damageEnemyToPlayer);
    }

    cocos2d::log("Life %f", m_player.at(player)->getDamage(m_enemy.at(enemy)->getCharacterType()));
    cocos2d::log("Life %d", m_enemy.at(enemy)->getLife());

    float damagePlayerToEnemy = m_player.at(player)->getDamage(m_enemy.at(enemy)->getCharacterType())*m_player.at(player)->getLife();
    cocos2d::log("Damage %f", damagePlayerToEnemy);
    cocos2d::log("Def %f", (diffPlayer * damagePlayerToEnemy) / 100);
    damagePlayerToEnemy = damagePlayerToEnemy + ((diffPlayer * damagePlayerToEnemy) / 100);
    if(damagePlayerToEnemy > 5) {
        m_enemy.at(enemy)->setLifeLabel(
                m_enemy.at(enemy)->getLife() - damagePlayerToEnemy + randomEnemy);
        cocos2d::log("Damage %f", damagePlayerToEnemy + randomEnemy);
    }
    else{
        m_enemy.at(enemy)->setLifeLabel(
                m_enemy.at(enemy)->getLife() - damagePlayerToEnemy);
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
        charactersPos[1][enemy] = Vec2(-1,-1);
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
        charactersPos[0][player] = Vec2(-1,-1);
        cocos2d::log("Size %d", m_player.size());
    }

}

void MapManager::moveEnemies(){
    cocos2d::log("Enemy Move ");
    for (unsigned int j = 0; j < numEnemies; j++) {
        if(m_enemy.at(j)->getState() == CharacterState::Selectable) {
            int def = m_world->getDefenseAt(m_enemy.at(j)->getMapPos().x, m_enemy.at(j)->getMapPos().y);
            bool pasa = false, pasa1 = false, pasa2 = false, pasa3 = false, pasa4 = false, attacked = false;
            Point newPos;
            int k = 0;
            cocos2d::log("Enemy Move %i", j);
            cocos2d::log("Enemy Move %i", def);
            cocos2d::log("Enemy Move %f", m_enemy.at(j)->getMapPos().x);
            cocos2d::log("Enemy Move %f", m_enemy.at(j)->getMapPos().y);
            int player = playerNear(m_enemy.at(j)->getMapPos());
            if (player != -1) {
                cocos2d::log("Enemy Move Attack %i", player);
                attackEnemy(player, j, m_player.at(player)->getMapPos(), m_enemy.at(j)->getMapPos());
                attacked = true;
            }
            if(!attacked) {
                for (unsigned int r = 0; r < m_enemy.at(j)->getRange(); r++) {
                    k = 0;
                    for (unsigned int i = 0; i < 4; i++) {
                        int random = rand() % 4;
                        cocos2d::log("Enemy Move Random %i", j);
                        cocos2d::log("Enemy Move Random %i", random);
                        cocos2d::log("Enemy Move Random %i", def);
                        cocos2d::log("Enemy Move Random %i", k);
                        cocos2d::log("Enemy Move Random %i",
                                     m_world->getDefenseAt(m_enemy.at(j)->getMapPos().x + 1,
                                                           m_enemy.at(j)->getMapPos().y));
                        if (random == 0 && m_enemy.at(j)->getMapPos().x + 1 > -1 &&
                            m_enemy.at(j)->getMapPos().x + 1 < 8
                            && m_enemy.at(j)->getMapPos().y > -1 &&
                            m_enemy.at(j)->getMapPos().y < 8 &&
                            m_world->getDefenseAt(m_enemy.at(j)->getMapPos().x + 1,
                                                  m_enemy.at(j)->getMapPos().y) > def - k) {
                            cocos2d::log("Enemy Move1 %f", m_enemy.at(j)->getMapPos().x + 1);
                            cocos2d::log("Enemy Move1 %f", m_enemy.at(j)->getMapPos().y);
                            cocos2d::log("Enemy Move1 %i",
                                         m_world->getDefenseAt(m_enemy.at(j)->getMapPos().x + 1,
                                                               m_enemy.at(j)->getMapPos().y));
                            newPos = Point(m_enemy.at(j)->getMapPos().x + 1,
                                           m_enemy.at(j)->getMapPos().y);
                            pasa1 = true;
                        } else if (random == 1 && m_enemy.at(j)->getMapPos().x > -1 &&
                                   m_enemy.at(j)->getMapPos().x < 8
                                   && m_enemy.at(j)->getMapPos().y + 1 > -1 &&
                                   m_enemy.at(j)->getMapPos().y + 1 < 8 &&
                                   m_world->getDefenseAt(m_enemy.at(j)->getMapPos().x,
                                                         m_enemy.at(j)->getMapPos().y + 1) >
                                   def - k) {
                            cocos2d::log("Enemy Move2 %f", m_enemy.at(j)->getMapPos().x);
                            cocos2d::log("Enemy Move2 %f", m_enemy.at(j)->getMapPos().y + 1);
                            cocos2d::log("Enemy Move2 %i",
                                         m_world->getDefenseAt(m_enemy.at(j)->getMapPos().x,
                                                               m_enemy.at(j)->getMapPos().y + 1));
                            newPos = Point(m_enemy.at(j)->getMapPos().x,
                                           m_enemy.at(j)->getMapPos().y + 1);
                            pasa2 = true;
                        } else if (random == 2 && m_enemy.at(j)->getMapPos().x - 1 > -1 &&
                                   m_enemy.at(j)->getMapPos().x - 1 < 8
                                   && m_enemy.at(j)->getMapPos().y > -1 &&
                                   m_enemy.at(j)->getMapPos().y < 8 &&
                                   m_world->getDefenseAt(m_enemy.at(j)->getMapPos().x - 1,
                                                         m_enemy.at(j)->getMapPos().y) > def - k) {
                            cocos2d::log("Enemy Move3 %f", m_enemy.at(j)->getMapPos().x - 1);
                            cocos2d::log("Enemy Move3 %f", m_enemy.at(j)->getMapPos().y);
                            cocos2d::log("Enemy Move1 %i",
                                         m_world->getDefenseAt(m_enemy.at(j)->getMapPos().x - 1,
                                                               m_enemy.at(j)->getMapPos().y));
                            newPos = Point(m_enemy.at(j)->getMapPos().x - 1,
                                           m_enemy.at(j)->getMapPos().y);
                            pasa3 = true;
                        } else if (random == 3 && m_enemy.at(j)->getMapPos().x > -1 &&
                                   m_enemy.at(j)->getMapPos().x < 8
                                   && m_enemy.at(j)->getMapPos().y - 1 > -1 &&
                                   m_enemy.at(j)->getMapPos().y - 1 < 8 &&
                                   m_world->getDefenseAt(m_enemy.at(j)->getMapPos().x,
                                                         m_enemy.at(j)->getMapPos().y - 1) >
                                   def - k) {
                            cocos2d::log("Enemy Move4 %f", m_enemy.at(j)->getMapPos().x);
                            cocos2d::log("Enemy Move4 %f", m_enemy.at(j)->getMapPos().y - 1);
                            cocos2d::log("Enemy Move1 %i",
                                         m_world->getDefenseAt(m_enemy.at(j)->getMapPos().x,
                                                               m_enemy.at(j)->getMapPos().y - 1));
                            newPos = Point(m_enemy.at(j)->getMapPos().x,
                                           m_enemy.at(j)->getMapPos().y - 1);
                            pasa4 = true;
                        }
                        if (pasa1 || pasa2 || pasa3 || pasa4) {
                            pasa = true;
                            i = 4;
                        } else {
                            i = 0;
                            k++;
                        }
                        if (pasa && checkCorrectPos(newPos)) {
                            cocos2d::log("Enemy Move6 %f", newPos.x);
                            cocos2d::log("Enemy Move6 %f", newPos.y);
                            m_enemy.at(j)->setState(CharacterState::Selected);
                            m_enemy.at(j)->setMapPos(newPos);
                            cocos2d::log("Enemy Move6 %f", m_enemy.at(j)->getMapPos().x);
                            cocos2d::log("Enemy Move6 %f", m_enemy.at(j)->getMapPos().y);
                            pasa = false;
                            pasa1 = false;
                            pasa2 = false;
                            pasa3 = false;
                            pasa4 = false;
                        }
                    }
                }
                m_enemy.at(j)->setState(CharacterState::UnSelectable);
                charactersPos[1][j] = m_enemy.at(j)->getMapPos();
            }
        }
    }
    if (checkCharacterPos()) {
        m_gui->setCharacterTexture(characterSelect, lifeCharacterSelect);
    } else {
        m_gui->setVisibleTexture();
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

void MapManager::publicSelect(MapManager* m, int x, int y)
{
    if(!m->m_gui->getFinish() && !m->m_gui->getPause()) {
        int idTile = m->m_world->getTileGID(y - 1, x - 1);
        m->m_gui->setSelectPosition(Point(POSITION_X_MAP + 16 + (32 * (y - 1)), 50 + (32 *
                                                                                      (x - 1))));
        m->m_gui->updateGUI(idTile);

        m->pos = Vec2(y - 1, x - 1);

        if (m->checkCharacterPos()) {
            m->m_gui->setCharacterTexture(m->characterSelect, m->lifeCharacterSelect);
        } else {
            m->m_gui->setVisibleTexture();
        }
    }
}

void MapManager::publicSelectPlayer(MapManager* m, int player)
{

    if(!m->m_gui->getFinish() && !m->m_gui->getPause()) {
        cocos2d::log("Players select %f", static_cast<double>(m->numPlayers));
        cocos2d::log("Players select %f", static_cast<double>(player));
        if (m->m_player.at(player)->getState() == CharacterState::Selectable ||
            m->m_player.at(player)->getState() == CharacterState::UnSelected ||
            m->m_player.at(player)->getState() == CharacterState::Attack) {

            cocos2d::log("Players select %f", static_cast<double>(player));
            m->unselectOthers();
            cocos2d::log("Players select %f", static_cast<double>(player));
            m->m_gui->disableAttackPosition();
            cocos2d::log("Players select %f", static_cast<double>(player));

            m->m_player.at(player)->setState(CharacterState::Selected);
            m->enemyNear(m->m_player.at(player)->getMapPos());
            m->m_world->changeTiles2(m->m_player.at(player)->getMapPos(), m->charactersPos,
                                     m->numPlayers, m->numEnemies,
                                     m->m_player.at(player)->getRange());
        }
        if (!m->isSelected()) {
            m->m_world->initialTiles();
        }
    }
}

void MapManager::publicMove(MapManager* m, int player, int x, int y)
{
    if(!m->m_gui->getFinish() && !m->m_gui->getPause()) {
        m->pos = Point(y - 1, x - 1);

        cocos2d::log("Players move  %f", static_cast<double>(m->numPlayers));
        cocos2d::log("Players move %f", static_cast<double>(player));
        if (m->m_player.at(player)->getState() == CharacterState::Selected) {
            if (m->checkCorrectPos(m->pos) && m->checkCorrectRange(m->pos)) {
                cocos2d::log("Players move %f", static_cast<double>(player));
                m->m_player.at(player)->setMapPos(m->pos);
                m->m_world->initialTiles();
                m->m_player.at(player)->setState(CharacterState::Attack);
                m->enemyNear(m->m_player.at(player)->getMapPos());
                m->m_gui->setCharacterTexture(m->characterSelect, m->lifeCharacterSelect);
                m->charactersPos[0][player] = m->m_player.at(player)->getMapPos();
            } else {
                m->m_player.at(player)->setState(CharacterState::Attack);
                m->publicAttack(player, x, y);
            }
        } else {
            m->publicAttack(player, x, y);
        }
    }
}

void MapManager::publicAttack(int player, int x, int y)
{
    if(!m_gui->getFinish() && !m_gui->getPause()) {
        pos = Point(y - 1, x - 1);

        cocos2d::log("Players attack  %f", static_cast<double>(numPlayers));
        cocos2d::log("Players attack %f", static_cast<double>(player));
        if (m_player.at(player)->getState() == CharacterState::Attack) {
            bool attacked = false;
            for (unsigned int j = 0; j < numEnemies; j++) {
                if (pos == m_enemy.at(j)->getMapPos() &&
                    enemyNear(m_player.at(player)->getMapPos()) && enemyNearAttack(m_player.at(player)->getMapPos(),
                                                                                   m_enemy.at(j)->getMapPos())) {
                    attackPlayer(player, j, m_player.at(player)->getMapPos(),
                                 m_enemy.at(j)->getMapPos());
                    m_world->initialTiles();
                    attacked = true;
                }
            }
            if (!attacked) {
                m_gui->disableAttackPosition();
                m_player.at(player)->setState(CharacterState::UnSelected);
            }
        }
    }
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

void MapManager::getMP(MapManager *m){
    cocos2d::log("getClass");
    mp = m;
}