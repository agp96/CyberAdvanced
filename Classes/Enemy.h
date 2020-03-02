//
// Created by agpal on 05/02/2020.
//

#include "Engine2D/Character.h"

class Enemy: public Character{
public:

    Enemy( const std::string& file, const std::string& type, const Vec2& initPos);

    bool init();

    void preloadResources();
    Node* getNode();

    void setLifeLabel(const int& newLife);

    int getCharacterType();

    void move();
    void walk(bool right);
    void stop();
    void attack();
    void die();


private:
    std::string fileSprite;
    int typeCharacter;

};

