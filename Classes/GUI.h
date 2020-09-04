//
// Created by agpal on 05/02/2020.
//

#pragma once

#include "Engine2D/GameEntity.h"

class GUI: public GameEntity{

public:

    bool init();

    void preloadResources();
    Node* getNode();

    void setSelectPosition(const Point& newPos);
    void setAttackPosition(const Point& newPos);
    void disableAttackPosition();

    void setVidas(int numvidas);
    void updateGUI(const int &tile);
    void showInfo();

    bool getTurn();
    void setTurn(bool newTurn);

    bool getPause();
    bool getFinish();

    int getNextLevel();

    void setCharacterTexture(Texture2D * newTexture, int lifeCharacterSelect);
    void setVisibleTexture();

    static void getGUI(GUI *g);

    void showFinishMenu(bool completed);

    static void publicGoToMainMenuScene();
    static void publicFinishTurn();
    static void publicGoToInfo();
    static void publicContinue();
    static void publicRepeat();
    static void publicNext();

    CREATE_FUNC(GUI);

    static GUI *gui;

private:
    void GoToInfo( cocos2d::Ref *sender );
    void Continue( cocos2d::Ref *sender );
    void GoToMainMenuScene( cocos2d::Ref *sender );
    void FinishTurn( cocos2d::Ref *sender );
    void menuNextLevelCallback(cocos2d::Ref* pSender);
    void menuTryAgainCallback(cocos2d::Ref* pSender);

    Label *m_labelVidas;
    Label *labelLife;
    Sprite *selectSprite;
    std::vector<Sprite*> attackSprite;
    std::vector<Sprite*> moveSprite;
    Sprite *tileSprite;
    Sprite *characterSprite;
    Label *labelSprite, *labelInfo;
    Menu *finishTurn, *menu, *info, *cont;
    LayerGradient *fondoInfo;
    int idTile;
    static bool turn;
    bool finish, pause;
    int nextLevel = -1;

};
