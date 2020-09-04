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

    void initLevel(int lvl, int mod);

    void preloadResources();
    void start();
    void updateEachFrame(float delta);

    bool onTouchBegan(Touch *touch, cocos2d::Event *event);
    void onTouchMoved(Touch *touch, cocos2d::Event *event);
    void onTouchEnded(Touch *touch, cocos2d::Event *event);

    void update();

    bool checkCorrectPos(const Vec2& pos);
    bool checkCorrectRange(const Vec2& pos);
    bool checkCharacterPos();
    bool checkNextTurn();

    void attackPlayer(unsigned int player, unsigned int enemy, Vec2 posP, Vec2 posE);
    void attackEnemy(unsigned int player, unsigned int enemy, Vec2 posP, Vec2 posE);

    bool enemyNear(const Vec2& posPlayer);
    bool enemyNearAttack(const Vec2& posPlayer, const Vec2& posEnemy);
    int playerNear(const Vec2& posEnemy);
    bool playerNearAttack(const Vec2& posEnemy, const Vec2& posPlayer);
    void moveEnemies();

    void turnPlayer();
    void turnEnemy();

    bool isSelected();
    void unselectOthers();

    static void getMP(MapManager *m);

    static void publicSelect(MapManager* m, int x, int y);
    static void publicSelectPlayer(MapManager* m, int player);
    static void publicMove(MapManager* m, int player, int x, int y);
    void publicAttack(int player, int x, int y);

    // implement the "static create()" method manually
    CREATE_FUNC(MapManager);

    static MapManager *mp;

private:

    GUI *m_gui;
    World *m_world;
    std::vector<Player*> m_player;
    std::vector<Enemy*> m_enemy;
    Texture2D* characterSelect;
    int lifeCharacterSelect;
    Vec2 pos;
    int numPlayers, numEnemies;
    int turn = 0;
    int level = 0;
    int mode = 0;
    Vec2 charactersPos[2][5];

};

