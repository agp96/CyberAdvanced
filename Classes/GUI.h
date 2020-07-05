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

    bool getTurn();
    void setTurn(bool newTurn);

    int getNextLevel();

    void setCharacterTexture(Texture2D * newTexture, int lifeCharacterSelect);
    void setVisibleTexture();

    void showFinishMenu(bool completed);

    CREATE_FUNC(GUI);

private:
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
    Label *labelSprite;
    int idTile;
    bool turn = false;
    int nextLevel = -1;

};
