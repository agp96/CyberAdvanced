//
// Created by agpal on 30/01/2020.
//

#pragma once

#include "Engine2D/GameEntity.h"
#include "Engine2D/TiledMapHelper.h"

class World: public GameEntity{

public:
    CREATE_FUNC(World);
    bool init();
    ~World();

    virtual void preloadResources();
    virtual Node* getNode();
    void update(float delta);

    int getTileGIDAtPosition(const Point &tileCoords);
    Point tileCoordForPosition(const Vec2& position);
    Rect tileRectForPosition(const Vec2& position);
    void deleteTileAt(const Point &tileCoords);
    Texture2D* getTileAt(const Point &tileCoords);
    Size getTileSize();


private:
    TiledMapHelper *m_tiledMapHelper;


};

