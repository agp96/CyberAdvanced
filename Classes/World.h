//
// Created by agpal on 30/01/2020.
//

#pragma once

#include "Engine2D/GameEntity.h"
#include "Engine2D/TiledMapHelper.h"

class World: public GameEntity{

public:
    bool init();

    virtual void preloadResources();
    virtual Node* getNode();

    void update(float delta);
    void setLevel(int lvl);
    void loadLevel(int lvl);

    int getTileGIDAtPosition(const Point &tileCoords);
    Point tileCoordForPosition(const Vec2& position);
    Rect tileRectForPosition(const Vec2& position);
    void deleteTileAt(const Point &tileCoords);
    Texture2D* getTileAt(const Point &tileCoords);
    Size getTileSize();

    void changeTiles(const Vec2 &posPlayer, const Vec2 charactersPos[2][5], const int &type, const int &range);
    void changeTiles2(const Vec2 &posPlayer, const Vec2 charactersPos[2][5], const int &numPlayers, const int &numEnemies, const int &range);
    void initialTiles();

    int getDefenseAt(int x, int y);
    int getTileGID(int x, int y);

    std::vector<Vec2*> getMoveMap();

    CREATE_FUNC(World);

private:
    TiledMapHelper *m_tiledMapHelper;
    int *map;
    int lvl;
    int tiles_map[8][8];
    int defense_map[8][8];
    int weight_map[8][8];
    std::vector<Vec2*> move_map;

};

