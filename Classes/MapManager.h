//
// Created by agpal on 06/02/2020.
//

#include "Engine2D/GameManager.h"
#include "GUI.h"
#include "World.h"
#include "Player.h"
#include "Enemy.h"
#include "cocos2d.h"

class MapManager : public GameManager
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    ~MapManager();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    void preloadResources();
    void start();
    void updateEachFrame(float delta);

    bool onTouchBegan(Touch *touch, cocos2d::Event *event);
    void onTouchMoved(Touch *touch, cocos2d::Event *event);
    void onTouchEnded(Touch *touch, cocos2d::Event *event);

    void update();

    bool checkCorrectPos();
    bool checkCharacterPos();
    bool checkNextTurn();

    void attackPlayer(int player, int enemy);

    void enemyNear(const Vec2& posPlayer);
    void moveEnemies();

    void turnPlayer();
    void turnEnemy();

    // implement the "static create()" method manually
    CREATE_FUNC(MapManager);

private:
    void GoToMainMenuScene();

    GUI *m_gui;
    World *m_world;
    std::vector<Player*> m_player;
    std::vector<Enemy*> m_enemy;
    Texture2D* characterSelect;
    Vec2 pos;
    int turn = 0;
    int numPlayers, numEnemies;
};

