//
// Created by agpal on 29/01/2020.
//

#include "TiledMapHelper.h"

bool TiledMapHelper::init(){

    return true;

}


void TiledMapHelper::loadTileMap(const char *url, const char *withCollisionLayer, int numMap){
    Size visibleSize = Director::getInstance()->getVisibleSize();

    m_tiledmap = TMXTiledMap::create(url);
    m_tiledmap->setPositionY(visibleSize.height/2);
    m_layer = m_tiledmap->getLayer(withCollisionLayer);

}

Point TiledMapHelper::tileCoordForPosition(const Point& position)
{
    Size tileSize = m_tiledmap->getTileSize();
    auto tpos = m_tiledmap->getPosition();

    float totalHeight = m_tiledmap->getMapSize().height * tileSize.height;
    float x = floor((position.x-tpos.x) / tileSize.width);
    float y = floor((totalHeight - (position.y-tpos.y)) / tileSize.height);
    return Point(x, y);
}

Rect TiledMapHelper::rectForTileAt(const Point &tileCoords) {
    Size tileSize = m_tiledmap->getTileSize();
    auto tpos = m_tiledmap->getPosition();

    float totalHeight = m_tiledmap->getMapSize().height * tileSize.height;
    Point origin = Point((tileCoords.x-tpos.x) * tileSize.width, totalHeight -
                                                                 (((tileCoords.y-tpos.y) + 1) * tileSize.height));
    return Rect(origin.x, origin.y,
                tileSize.width, tileSize.height);
}

int TiledMapHelper::getTileGIDAt(const Point &tileCoords) {
    Size s = m_layer->getLayerSize();

    if (tileCoords.x >= 0 && tileCoords.x < s.width && tileCoords.y >= 0 && tileCoords.y < s.height)
        return m_layer->getTileGIDAt(tileCoords);
    else {
        CCLOG("Warning: Accesing pos %f,%f in tilemap (out of range)", tileCoords.x, tileCoords.y);
        return 0;
    }
}

void TiledMapHelper::deleteTileAt(const Point &tileCoords){
    m_layer->setTileGID(0, tileCoords);
}


int TiledMapHelper::getTileGIDAtPosition(const Point &pos){
    return getTileGIDAt(tileCoordForPosition(pos));
}

TMXTiledMap *TiledMapHelper::getTiledMap(){
    return m_tiledmap;
}

TMXLayer *TiledMapHelper::getMainLayer(){
    return m_layer;
}

bool TiledMapHelper::isTileCoordInMap(Point tileCoord) {
    Size mapSize = m_tiledmap->getMapSize();
    return tileCoord.x >=0 &&
           tileCoord.y >= 0 &&
           tileCoord.x < mapSize.width &&
           tileCoord.y < mapSize.height;
}