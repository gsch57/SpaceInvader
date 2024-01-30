#ifndef __ENTITYFACTORY_H__
#define __ENTITYFACTORY_H__

#include "Entity.hpp"
#include "Player.hpp"
#include "Missile.hpp"
#include "Enemy.hpp"

class EntityFactory
{
public:
    static Entity *createPlayer(int life, int positionX, int positionY);
    static Entity *createEnemy(int life, int positionX, int positionY);
    static Entity *createPlayerMissile(int life, int positionX, int positionY);
    static Entity *createEnemyMissile(int life, int positionX, int positionY);
};

#endif // __ENTITYFACTORY_H__