//
// Created by agpal on 30/01/2020.
//

#pragma once

#include "cocos2d.h"
USING_NS_CC;

class GameEntity: public Ref {

public:

    bool init(){return true;};

    virtual void preloadResources(){};
    virtual Node* getNode(){return NULL;};
    virtual void update(float delta){};

protected:
    Node *m_node=NULL;


};


