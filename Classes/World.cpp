//
// Created by agpal on 30/01/2020.
//

#include "World.h"
#include "Definitions.h"
#include "iostream"


bool World::init(){
    cocos2d::log("World2");
    GameEntity::init();

    m_tiledMapHelper = TiledMapHelper::create();
    m_tiledMapHelper->retain();
    return true;
}

void World::preloadResources(){

    cocos2d::log("World %d", lvl);
    if(lvl == 0) {
        cocos2d::log("World %d", lvl);
        m_tiledMapHelper->loadTileMap("map2.tmx", "suelo", 0);
        cocos2d::log("World %d", lvl);
    }
    else if(lvl == 1) {
        cocos2d::log("World %d", lvl);
        m_tiledMapHelper->loadTileMap("map3.tmx", "suelo", 0);
    }
    cocos2d::log("World3");
}

void World::setLevel(int l){

    lvl = l;
    cocos2d::log("WorldSET");
    if(lvl == 0) {
        cocos2d::log("World %d", lvl);
        m_tiledMapHelper->loadTileMap("map2.tmx", "suelo", 0);
        cocos2d::log("World %d", lvl);
    }
    else if(lvl == 1) {
        cocos2d::log("World %d", lvl);
        m_tiledMapHelper->loadTileMap("map3.tmx", "suelo", 0);
    }
}

void World::loadLevel(int l){

    cocos2d::log("completed8 %d", l);
    if(l == 0) {
        m_tiledMapHelper->loadTileMap("map2.tmx", "suelo", 0);
        lvl = l;
    }
    else if(l == 1) {
        lvl = l;
        cocos2d::log("completed82 %d", l);
        m_tiledMapHelper->loadTileMap("map3.tmx", "suelo", 0);
        //Añado el tiledmap
        //m_node = NULL;
        //getNode();
    }
}

Node* World::getNode(){

    cocos2d::log("World4");
    if(m_node==NULL) {
        m_node = Node::create();
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        cocos2d::log("SIZEEEEEEEE %f", visibleSize.height);
        cocos2d::log("SIZEEEEEEEE %f", visibleSize.width);

        int k = 0;
        map = reinterpret_cast<int *>(m_tiledMapHelper->getMainLayer()->getTiles());
        cocos2d::log("World45");
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                tiles_map[i][j] = map[k];
                if (map[k] < 4) {
                    defense_map[i][j] = map[k];
                } else if (map[k] == 4 || map[k] == 5) {
                    defense_map[i][j] = 4;
                }
                else{
                    defense_map[i][j] = 0;
                }
                if (defense_map[i][j] == 1) {
                    weight_map[i][j] = 0;
                } else if (defense_map[i][j] == 2) {
                    weight_map[i][j] = 2;
                } else if (defense_map[i][j] == 3) {
                    weight_map[i][j] = 3;
                } else if (defense_map[i][j] == 4) {
                    weight_map[i][j] = 1;
                } else {
                    weight_map[i][j] = 0;
                }
                k++;
            }
        }

        cocos2d::log("World5");
        auto fondo = LayerGradient::create(Color4B(110, 62, 167, 255), Color4B(73, 10, 206, 255));
        fondo->setContentSize(Size(3392 + 500, visibleSize.height / 2 + 200));
        fondo->setPosition(-500, visibleSize.height / 2 - 170);

        m_node->addChild(fondo);

        auto rectNode = DrawNode::create();
        Vec2 rectangle[4], rectangle2[4];
        rectangle[0] = Vec2(-50, -50);
        rectangle[1] = Vec2(310, -50);
        rectangle[2] = Vec2(310, 320);
        rectangle[3] = Vec2(-50, 320);

        Color4F color(9, 4, 0, 16);
        rectNode->drawPolygon(rectangle, 4, Color4F::GRAY, 1, Color4F::GRAY);

        rectangle2[0] = Vec2(visibleSize.width - visibleSize.width / 4 + origin.x -
                             (visibleSize.width - visibleSize.width / 4 + origin.x) / 5,
                             visibleSize.height / 2 - 70);
        rectangle2[1] = Vec2(visibleSize.width - visibleSize.width / 4 + origin.x +
                             (visibleSize.width - visibleSize.width / 4 + origin.x) / 5,
                             visibleSize.height / 2 - 70);
        rectangle2[2] = Vec2(visibleSize.width - visibleSize.width / 4 + origin.x +
                             (visibleSize.width - visibleSize.width / 4 + origin.x) / 5,
                             visibleSize.height - 110);
        rectangle2[3] = Vec2(visibleSize.width - visibleSize.width / 4 + origin.x -
                             (visibleSize.width - visibleSize.width / 4 + origin.x) / 5,
                             visibleSize.height - 110);

        Color4F color2(9, 4, 0, 16);
        rectNode->drawPolygon(rectangle2, 4, Color4F::BLUE, 1, Color4F::BLUE);
        m_node->addChild(rectNode);

        auto labelsquare = Label::createWithBMFont("fonts/Retro Gaming2.fnt",
                                                   "1    2    3    4    5    6    7    8");
        labelsquare->setPosition(Point(POSITION_X_MAP * 4 + 8,
                                       visibleSize.height - visibleSize.height / 16 + origin.y));
        labelsquare->setScale(0.45f);
        labelsquare->setVisible(true);
        labelsquare->setColor(Color3B::BLACK);

        m_node->addChild(labelsquare, 1);

        auto labelsquare2 = Label::createWithBMFont("fonts/Retro Gaming2.fnt", "8");
        labelsquare2->setPosition(Point(POSITION_X_MAP - 15,
                                        visibleSize.height - visibleSize.height / 7 + origin.y -
                                        1));
        labelsquare2->setScale(0.45f);
        labelsquare2->setVisible(true);
        labelsquare2->setColor(Color3B::BLACK);

        m_node->addChild(labelsquare2, 1);

        auto labelsquare3 = Label::createWithBMFont("fonts/Retro Gaming2.fnt", "7");
        labelsquare3->setPosition(Point(POSITION_X_MAP - 15, labelsquare2->getPositionY() - 32));
        labelsquare3->setScale(0.45f);
        labelsquare3->setVisible(true);
        labelsquare3->setColor(Color3B::BLACK);
        m_node->addChild(labelsquare3, 1);

        auto labelsquare4 = Label::createWithBMFont("fonts/Retro Gaming2.fnt", "6");
        labelsquare4->setPosition(Point(POSITION_X_MAP - 15, labelsquare3->getPositionY() - 32));
        labelsquare4->setScale(0.45f);
        labelsquare4->setVisible(true);
        labelsquare4->setColor(Color3B::BLACK);
        m_node->addChild(labelsquare4, 1);

        auto labelsquare5 = Label::createWithBMFont("fonts/Retro Gaming2.fnt", "5");
        labelsquare5->setPosition(Point(POSITION_X_MAP - 15, labelsquare4->getPositionY() - 32));
        labelsquare5->setScale(0.45f);
        labelsquare5->setVisible(true);
        labelsquare5->setColor(Color3B::BLACK);
        m_node->addChild(labelsquare5, 1);

        auto labelsquare6 = Label::createWithBMFont("fonts/Retro Gaming2.fnt", "4");
        labelsquare6->setPosition(Point(POSITION_X_MAP - 15, labelsquare5->getPositionY() - 32));
        labelsquare6->setScale(0.45f);
        labelsquare6->setVisible(true);
        labelsquare6->setColor(Color3B::BLACK);
        m_node->addChild(labelsquare6, 1);

        auto labelsquare7 = Label::createWithBMFont("fonts/Retro Gaming2.fnt", "3");
        labelsquare7->setPosition(Point(POSITION_X_MAP - 15, labelsquare6->getPositionY() - 32));
        labelsquare7->setScale(0.45f);
        labelsquare7->setVisible(true);
        labelsquare7->setColor(Color3B::BLACK);
        m_node->addChild(labelsquare7, 1);

        auto labelsquare8 = Label::createWithBMFont("fonts/Retro Gaming2.fnt", "2");
        labelsquare8->setPosition(Point(POSITION_X_MAP - 15, labelsquare7->getPositionY() - 32));
        labelsquare8->setScale(0.45f);
        labelsquare8->setVisible(true);
        labelsquare8->setColor(Color3B::BLACK);
        m_node->addChild(labelsquare8, 1);

        auto labelsquare9 = Label::createWithBMFont("fonts/Retro Gaming2.fnt", "1");
        labelsquare9->setPosition(Point(POSITION_X_MAP - 15, labelsquare8->getPositionY() - 32));
        labelsquare9->setScale(0.45f);
        labelsquare9->setVisible(true);
        labelsquare9->setColor(Color3B::BLACK);
        m_node->addChild(labelsquare9, 1);


        cocos2d::log("World6");
        m_tiledMapHelper->getTiledMap()->setPositionX(POSITION_X_MAP);
        m_tiledMapHelper->getTiledMap()->setPositionY(visibleSize.height - POSITION_Y_MAP - 256);
        m_tiledMapHelper->getTiledMap()->setScale(CC_CONTENT_SCALE_FACTOR());
        //m_tiledMapHelper->getTiledMap()->setTileSize(m_tiledMapHelper->getTiledMap()->getTileSize()*2);

        //Añado el tiledmap
        m_node->addChild(m_tiledMapHelper->getTiledMap());

        cocos2d::log("World");
    }

    return m_node;

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

void World::changeTiles2(const Vec2 &posPlayer, const Vec2 charactersPos[2][5], const int &numPlayers, const int &numEnemies, const int &range) {
    auto suelo = m_tiledMapHelper->getTiledMap()->getLayer("suelo");
    int x = posPlayer.x+1, y = 8-posPlayer.y, maxY = 2;
    if (m_tiledMapHelper->isTileCoordInMap(posPlayer)) {
        for (int c2=0; c2 < 9;c2++){
            if(c2 < y) {
                if (c2 == y - range) {
                    cocos2d::log("Pos41 s %d", x-1);
                    cocos2d::log("Pos41 s %d", y - 1 - range);
                    if (x - 1 > -1 && x - 1 < 8 && y - 1 - range > -1 &&
                        y - 1 - range < 8 && weight_map[y - 1 - range][x - 1] < 2) {
                        bool pasa = false;
                        int max = numPlayers;
                        for(int j=0; j < 2; j++){
                            for(int k=0; k < max; k++) {
                                int f1 = (64 -
                                          ((charactersPos[j][k].y+1) * 8))+charactersPos[j][k].x;
                                if (div (f1,8).quot == y - 1 - range && div (f1,8).rem == x - 1 ) {
                                    pasa = true;
                                }
                                if (div (f1,8).quot == y - 1 - range + 1 && div (f1,8).rem == x - 1 ) {
                                    pasa = true;
                                }
                            }
                            max = numEnemies;
                        }
                        if(pasa == false) {
                            suelo->setTileGID(
                                    m_tiledMapHelper->getTileGIDAt(Vec2(x - 1, y - 1 - range)) + 48,
                                    Vec2(x - 1, y - 1 - range));
                            move_map.push_back(new Vec2(x - 1, y - 1 - range));
                        }
                    }
                }
                if (c2 == y - range + 1) {
                    cocos2d::log("Pos42 s %d", x);
                    cocos2d::log("Pos42 s %d", y);
                    int i = -2;
                    for (int c3 = 0; c3 < 3; c3++) {
                        i++;
                        if (x - 1 + i > -1 && x - 1 + i < 8 && y - 1 - range + 1 > -1 &&
                            y - 1 - range + 1 < 8 && weight_map[y - 1 - range + 1][x - 1 + i]-1 < 3) {
                            bool pasa = false;
                            int max = numPlayers;
                            for(int j=0; j < 2; j++){
                                for(int k=0; k < max; k++) {
                                    int f1 = (64 -
                                              ((charactersPos[j][k].y+1) * 8))+charactersPos[j][k].x;
                                    if (div (f1,8).quot == y - 1 - range + 1 && div (f1,8).rem == x - 1 + i ) {
                                        pasa = true;
                                    }
                                }
                                max = numEnemies;
                            }
                            if(pasa == false) {
                                suelo->setTileGID(
                                        m_tiledMapHelper->getTileGIDAt(
                                                Vec2(x - 1 + i, y - 1 - range + 1)) +
                                        48,
                                        Vec2(x - 1 + i, y - 1 - range + 1));
                                move_map.push_back(new Vec2(x - 1 + i, y - 1 - range + 1));
                            }
                        }
                    }
                }
                if (c2 == y - range + 2) {
                    cocos2d::log("Pos43 s %d", x - range + 2);
                    cocos2d::log("Pos43 s %d", x);
                    cocos2d::log("Pos43 s %d", y);
                    int i = -3;
                    for (int c3 = 0; c3 < 5; c3++) {
                        i++;
                        if (x - 1 + i > -1 && x - 1 + i < 8 && y - 1 - range + 2 > -1 &&
                            y - 1 - range + 2 < 8 && weight_map[y - 1 - range + 2][x - 1 + i]-1 < 4) {
                            bool pasa = false;
                            int max = numPlayers;
                            for(int j=0; j < 2; j++){
                                for(int k=0; k < max; k++) {
                                    int f1 = (64 -
                                              ((charactersPos[j][k].y+1) * 8))+charactersPos[j][k].x;
                                    if (div (f1,8).quot == y - 1 - range + 2 && div (f1,8).rem == x - 1 + i ) {
                                        pasa = true;
                                    }
                                }
                                max = numEnemies;
                            }
                            if(pasa == false) {
                                suelo->setTileGID(
                                        m_tiledMapHelper->getTileGIDAt(
                                                Vec2(x - 1 + i, y - 1 - range + 2)) +
                                        48,
                                        Vec2(x - 1 + i, y - 1 - range + 2));
                                move_map.push_back(new Vec2(x - 1 + i, y - 1 - range + 2));
                            }
                        }
                    }
                }
                if (c2 == y - range + 3) {
                    cocos2d::log("Pos58 s %d", x);
                    cocos2d::log("Pos58 s %d", y);
                    int i = -4;
                    for (int c3 = 0; c3 < 7; c3++) {
                        i++;
                        if (x - 1 + i > -1 && x - 1 + i < 8 && y - 1 - range + 3 > -1 &&
                            y - 1 - range + 3 < 8 && weight_map[y - 1 - range + 3][x - 1 + i]-1 < 4) {
                            bool pasa = false;
                            int max = numPlayers;
                            for(int j=0; j < 2; j++){
                                for(int k=0; k < max; k++) {
                                    int f1 = (64 -
                                             ((charactersPos[j][k].y+1) * 8))+charactersPos[j][k].x;
                                    if (div (f1,8).quot == y - 1 - range + 3 && div (f1,8).rem == x - 1 + i ) {
                                        pasa = true;
                                    }
                                }
                                max = numEnemies;
                            }
                            if(pasa == false) {
                                suelo->setTileGID(
                                        m_tiledMapHelper->getTileGIDAt(
                                                Vec2(x - 1 + i, y - 1 - range + 3)) +
                                        48,
                                        Vec2(x - 1 + i, y - 1 - range + 3));
                                move_map.push_back(new Vec2(x - 1 + i, y - 1 - range + 3));
                            }
                        }
                    }
                }
            }
            if(c2 == y){
                cocos2d::log("Pos6 s %d", x);
                cocos2d::log("Pos6 s %d", y);
                int i = -range-1;
                for (int c3=0; c3 < range*2;c3++) {
                    i++;
                    if(x - 1 + i == x-1){
                        i++;
                    }
                    if(x - 1 + i > - 1 && x - 1 + i < 8 && y - 1 > -1 && y - 1 < 8 && weight_map[y - 1][x - 1 + i]-1 < range) {
                        bool pasa = false;
                        int max = numPlayers;
                        for(int j=0; j < 2; j++){
                            for(int k=0; k < max; k++) {
                                int f1 = (64 -
                                          ((charactersPos[j][k].y+1) * 8))+charactersPos[j][k].x;
                                if (div (f1,8).quot == y - 1 && div (f1,8).rem == x - 1 + i) {
                                    pasa = true;
                                }
                                if (c3 == 0 && div (f1,8).quot == y - 1 && div (f1,8).rem == x + i) {
                                    pasa = true;
                                }
                                if (c3 == (range*2) - 1 && div (f1,8).quot == y - 1 && div (f1,8).rem == x - 1 + i -1) {
                                    pasa = true;
                                }
                            }
                            max = numEnemies;
                        }
                        if(pasa == false) {
                            suelo->setTileGID(
                                    m_tiledMapHelper->getTileGIDAt(Vec2(x - 1 + i, y - 1)) +
                                    48,
                                    Vec2(x - 1 + i, y - 1));
                            move_map.push_back(new Vec2(x - 1 + i, y - 1));
                        }
                    }
                }
            }
            if(c2 > y){
                if (c2 == y + range) {
                    cocos2d::log("Pos71 s %d", x);
                    cocos2d::log("Pos71 s %d", y);
                    if (x - 1 > -1 && x - 1 < 8 && y - 1 + range > -1 &&
                        y - 1 + range < 8 && weight_map[y - 1 + range][x - 1]-1 < 1) {
                        bool pasa = false;
                        int max = numPlayers;
                        for(int j=0; j < 2; j++){
                            for(int k=0; k < max; k++) {
                                int f1 = (64 -
                                          ((charactersPos[j][k].y+1) * 8))+charactersPos[j][k].x;
                                if (div (f1,8).quot == y - 1 + range && div (f1,8).rem == x - 1) {
                                    pasa = true;
                                }
                                if (div (f1,8).quot == y - 1 + range - 1 && div (f1,8).rem == x - 1) {
                                    pasa = true;
                                }
                            }
                            max = numEnemies;
                        }
                        if(pasa == false) {
                            suelo->setTileGID(
                                    m_tiledMapHelper->getTileGIDAt(Vec2(x - 1, y - 1 + range)) + 48,
                                    Vec2(x - 1, y - 1 + range));
                            move_map.push_back(new Vec2(x - 1, y - 1 + range));
                        }
                    }
                }
                if (c2 == y + range - 1) {
                    cocos2d::log("Pos72 s %d", x);
                    cocos2d::log("Pos72 s %d", y);
                    int i = -2;
                    for (int c3 = 0; c3 < 3; c3++) {
                        i++;
                        if (x - 1 + i > -1 && x - 1 + i < 8 && y - 1 + range - 1 > -1 &&
                            y - 1 + range - 1 < 8 && weight_map[y - 1 + range - 1][x - 1 + i]-1 < 2) {
                            bool pasa = false;
                            int max = numPlayers;
                            for(int j=0; j < 2; j++){
                                for(int k=0; k < max; k++) {
                                    int f1 = (64 -
                                              ((charactersPos[j][k].y+1) * 8))+charactersPos[j][k].x;
                                    if (div (f1,8).quot == y - 1 + range - 1 && div (f1,8).rem == x - 1 + i) {
                                        pasa = true;
                                    }
                                }
                                max = numEnemies;
                            }
                            if(pasa == false) {
                                suelo->setTileGID(
                                        m_tiledMapHelper->getTileGIDAt(
                                                Vec2(x - 1 + i, y - 1 + range - 1)) +
                                        48,
                                        Vec2(x - 1 + i, y - 1 + range - 1));
                                move_map.push_back(new Vec2(x - 1 + i, y - 1 + range - 1));
                            }
                        }
                    }
                }
                if (c2 == y + range - 2) {
                    cocos2d::log("Pos73 s %d", x - range + 2);
                    cocos2d::log("Pos73 s %d", x);
                    cocos2d::log("Pos73 s %d", y);
                    int i = -3;
                    for (int c3 = 0; c3 < 5; c3++) {
                        i++;
                        if (x - 1 + i > -1 && x - 1 + i < 8 && y - 1 + range - 2 > -1 &&
                            y - 1 + range - 2 < 8 && weight_map[y - 1 + range - 2][x - 1 + i]-1 < 3) {
                            bool pasa = false;
                            int max = numPlayers;
                            for(int j=0; j < 2; j++){
                                for(int k=0; k < max; k++) {
                                    int f1 = (64 -
                                              ((charactersPos[j][k].y+1) * 8))+charactersPos[j][k].x;
                                    if (div (f1,8).quot == y - 1 + range - 2 && div (f1,8).rem == x - 1 + i) {
                                        pasa = true;
                                    }
                                }
                                max = numEnemies;
                            }
                            if(pasa == false) {
                                suelo->setTileGID(
                                        m_tiledMapHelper->getTileGIDAt(
                                                Vec2(x - 1 + i, y - 1 + range - 2)) +
                                        48,
                                        Vec2(x - 1 + i, y - 1 + range - 2));
                                move_map.push_back(new Vec2(x - 1 + i, y - 1 + range - 2));
                            }
                        }
                    }
                }
                if (c2 == y + range - 3) {
                    cocos2d::log("Pos74 s %d", x);
                    cocos2d::log("Pos74 s %d", y);
                    int i = -4;
                    for (int c3 = 0; c3 < 7; c3++) {
                        i++;
                        if (x - 1 + i > -1 && x - 1 + i < 8 && y - 1 + range - 3 > -1 &&
                            y - 1 + range - 3 < 8 && weight_map[y - 1 + range - 3][x - 1 + i]-1 < 4) {
                            bool pasa = false;
                            int max = numPlayers;
                            for(int j=0; j < 2; j++){
                                for(int k=0; k < max; k++) {
                                    int f1 = (64 -
                                              ((charactersPos[j][k].y+1) * 8))+charactersPos[j][k].x;
                                    if (div (f1,8).quot == y - 1 + range - 3 && div (f1,8).rem == x - 1 + i) {
                                        pasa = true;
                                    }
                                }
                                max = numEnemies;
                            }
                            if(pasa == false) {
                                suelo->setTileGID(
                                        m_tiledMapHelper->getTileGIDAt(
                                                Vec2(x - 1 + i, y - 1 + range - 3)) +
                                        48,
                                        Vec2(x - 1 + i, y - 1 + range - 3));
                                move_map.push_back(new Vec2(x - 1 + i, y - 1 + range - 3));
                            }
                        }
                    }
                }
            }
        }
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

    for (unsigned int i = 0; i < move_map.size(); i++) {
        move_map.at(i)->setZero();
        delete(move_map.at(i));
        move_map.erase(move_map.begin()+i);
    }
}

int World::getDefenseAt(int x, int y){
    int f1 = (64 -
              ((y+1) * 8))+x;
    return defense_map[div (f1,8).quot][div (f1,8).rem];
}

int World::getTileGID(int x, int y){
    int f1 = (64 -
              ((y+1) * 8))+x;
    return tiles_map[div (f1,8).quot][div (f1,8).rem];
}

std::vector<Vec2*> World::getMoveMap(){
    return move_map;
}