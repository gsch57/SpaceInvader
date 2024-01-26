#ifndef __ENTITYFACTORY_H__
#define __ENTITYFACTORY_H__

#include "Entity.hpp"
#include "Player.hpp"

class EntityFactory
{
public:
    static Entity *createPlayer(int life, int positionX, int positionY);
    // static Entity createEnemy(int life, int position);
    // static Entity createMissile(int life, int position);
};

#endif // __ENTITYFACTORY_H__