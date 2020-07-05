//
// Created by agpal on 30/01/2020.
//

#include "World.h"
#include "Definitions.h"
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
    m_tiledMapHelper->loadTileMap("map2.tmx", "def 1", 0);

}

Node* World::getNode(){

    Node *node = Node::create();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    cocos2d::log("SIZEEEEEEEE %f", visibleSize.height);
    cocos2d::log("SIZEEEEEEEE %f", visibleSize.width);

    auto fondo = LayerGradient::create(Color4B(139,69,19,255),Color4B(101,50,14,255));
    fondo->setContentSize(Size(3392+500, visibleSize.height/2+200));
    fondo->setPosition(-500,visibleSize.height/2-170);

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto backgroundSprite = Sprite::create( "gameplayBackground.png" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );

    node->addChild( backgroundSprite );

    m_tiledMapHelper->getTiledMap()->setPositionX(POSITION_X_MAP);
    m_tiledMapHelper->getTiledMap()->setPositionY(visibleSize.height-POSITION_Y_MAP-256);
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

void World::changeTiles(const Vec2 &posPlayer, const Vec2 charactersPos[2][5], const int &type, const int &range) {
    auto suelo = m_tiledMapHelper->getTiledMap()->getLayer("suelo");
    int x = posPlayer.x+2, y = posPlayer.y, maxY = 2;
    bool pasa = true;
    if (m_tiledMapHelper->isTileCoordInMap(posPlayer)) {
        cocos2d::log("Pos2 s %d", x);
        cocos2d::log("Pos3 s %d", y);
            for (int c2=0; c2 < 8;c2++){
                pasa = true;
                cocos2d::log("Pos s %d", c2);
                cocos2d::log("Pos s %f", posPlayer.x);
                cocos2d::log("Pos s %d", x);
                cocos2d::log("Pos s %d", y);
                //if (tablero[f2][c2]!=9){ //Si no es bomba
                if (y>=0 && x>=0) {
                    for (int i=0; i < 2;i++){
                        for (int j=0; j < 5;j++) {
                            if (charactersPos[i][j] == Vec2(x,y)) {
                                pasa = false;
                            }
                        }
                    }
                    if (pasa == true && x < 8 && x > -1 && y < 8 && y > -1) {
                        suelo->setTileGID(m_tiledMapHelper->getTileGIDAt(Vec2(x, 7 - y)) + 48,
                                          Vec2(x, 7 - y));
                    }
                }
                if (x-posPlayer.x>0) {
                    y += 1;
                    x -= 1;
                    cocos2d::log("1111111");
                }
                else if (x-posPlayer.x>-1){
                    y -= 1;
                    x -= 1;
                    cocos2d::log("22222222");
                }
                else{
                    y -= 1;
                    x += 1;
                    cocos2d::log("33333333");
                }
            }

        //for (unsigned int i = 1; i < range + 1; i++) {
        //    if (m_tiledMapHelper->isTileCoordInMap(Vec2(posPlayer.x + i, posPlayer.y + i))) {
        //        int gidSuelo = suelo->getTileGIDAt(posPlayer);
        //        if (gidSuelo != 0) {
        //if (m_tiledMapHelper->isTileCoordInMap(Vec2(posPlayer.x, 7 - (posPlayer.y + 1)))) {
          //  suelo->setTileGID(m_tiledMapHelper->getTileGIDAt(Vec2(posPlayer.x, 7 - (posPlayer.y + 1)))+32, Vec2(posPlayer.x, 7 - (posPlayer.y + 1)));
        //}
        //        }
        //    }
        //}
    }
}

void World::initialTiles() {

    auto suelo = m_tiledMapHelper->getTiledMap()->getLayer("suelo");

    for (unsigned int i = 0; i < 8; i++) {
        for (unsigned int j = 0; j < 8; j++) {
            Vec2 vec = Vec2(i, j);
            if(m_tiledMapHelper->getTileGIDAt(vec) > 48){
                suelo->setTileGID(m_tiledMapHelper->getTileGIDAt(vec)-48, vec);
            }
        }
    }
}