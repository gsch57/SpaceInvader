#ifndef __ENTITYFACTORY_H__
#define __ENTITYFACTORY_H__

#include "Entity.hpp"
#include "Player.hpp"
#include "Missile.hpp"

class EntityFactory
{
public:
    static Entity *createPlayer(int life, int positionX, int positionY);
    // static Entity createEnemy(int life, int position);
    static Entity *createMissile(int life, int positionX, int positionY);
};

#endif // __ENTITYFACTORY_H__