//
// Created by agpal on 29/01/2020.
//

#pragma once

#include "cocos2d.h"
USING_NS_CC;


class TiledMapHelper: public Ref {

public:

    bool init();

    void loadTileMap(const char *url, const char *withCollisionLayer, int numMap);

    Point tileCoordForPosition(const Vec2& position);
    Rect rectForTileAt(const Point &tileCoords);
    int getTileGIDAt(const Point &tileCoords);
    int getTileGIDAtPosition(const Vec2& position);
    void deleteTileAt(const Point &tileCoords);

    TMXTiledMap *getTiledMap();
    TMXLayer *getMainLayer();

    CREATE_FUNC(TiledMapHelper);


private:

    TMXTiledMap *m_tiledmap;
    TMXLayer *m_layer;
    TMXLayer *m_forest;
    TMXLayer *m_mountain;
    TMXLayer *m_plain;
    TMXLayer *m_road;
    TMXLayer *m_house;
    TMXLayer *m_bridge;
    TMXLayer *m_sea;


};

