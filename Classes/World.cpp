//
// Created by agpal on 30/01/2020.
//

#include "World.h"
#include "iostream"


bool World::init(){
    GameEntity::init();

    m_tiledMapHelper = TiledMapHelper::create();
    m_tiledMapHelper->retain();

    return true;
}


World::~World(){
    m_tiledMapHelper->release();
}

void World::preloadResources(){
    m_tiledMapHelper->loadTileMap("map2.tmx", "Map", 0);

}

Node* World::getNode(){

    Node *node = Node::create();
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto fondo = LayerGradient::create(Color4B(139,69,19,255),Color4B(101,50,14,255));
    fondo->setContentSize(Size(3392+500, visibleSize.height/2+200));
    fondo->setPosition(-500,visibleSize.height/2-110);

    node->addChild( fondo );

    m_tiledMapHelper->getTiledMap()->setPositionY(visibleSize.height/2-110);
    m_tiledMapHelper->getTiledMap()->setScale(CC_CONTENT_SCALE_FACTOR());
    //m_tiledMapHelper->getTiledMap()->setTileSize(m_tiledMapHelper->getTiledMap()->getTileSize()*2);

    //Añado el tiledmap
    node->addChild(m_tiledMapHelper->getTiledMap());

    return node;

}

int World::getTileGIDAtPosition(const Point &tileCoords){
    return m_tiledMapHelper->getTileGIDAtPosition(tileCoords);
}

Point World::tileCoordForPosition(const Vec2& position){
    return m_tiledMapHelper->tileCoordForPosition(position);
}

Rect World::tileRectForPosition(const cocos2d::Vec2 &position) {
    Point tileCoords = m_tiledMapHelper->tileCoordForPosition(position);
    return m_tiledMapHelper->rectForTileAt(tileCoords);
}

Texture2D* World::getTileAt(const Point &tileCoords){

    m_tiledMapHelper->getTiledMap()->getPropertiesForGID(m_tiledMapHelper->getMainLayer()->getTileGIDAt(tileCoords));
    auto sprite = m_tiledMapHelper->getMainLayer()->getTileAt(tileCoords)->getTexture();
    m_tiledMapHelper->getMainLayer()->getTileAt(tileCoords)->getTextureAtlas();
    return sprite;
}

void World::deleteTileAt(const Point &tileCoords){
    auto sprite = m_tiledMapHelper->getMainLayer()->getTileAt(tileCoords);

    //Lambda para borrar el tile cuando termine la animación
    //& copia por referencia
    //= copia por valor
    //Cuidado, pq tileCoords estara liberado cuando se ejecute lambda
    //Por defecto [=]
    auto actionDelete = CallFunc::create([&,tileCoords](){m_tiledMapHelper->deleteTileAt(tileCoords);});

    auto actionAnim = Spawn::create(MoveBy::create(.1, Vec2(0,5)),FadeOut::create(1),RotateBy::create(1,90),NULL);
    auto action = Sequence::create(actionAnim,actionDelete,NULL);

    sprite->runAction(action);

}

Size World::getTileSize(){
    return m_tiledMapHelper->getTiledMap()->getTileSize();
}

void World::update(float delta){
}
