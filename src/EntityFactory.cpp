#include "../includes/EntityFactory.hpp"
#include <memory>

Entity *EntityFactory::createPlayer(int life, int positionX, int positionY)
{
    return new Player(life, positionX, positionY);
}

Entity *EntityFactory::createMissile(int life, int positionX, int positionY)
{
    return new Missile(life, positionX, positionY);
}

Entity *EntityFactory::createEnemy(int life, int positionX, int positionY)
{
    return new Enemy(life, positionX, positionY);
}