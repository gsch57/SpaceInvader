#include "../includes/EntityFactory.hpp"
#include <memory>

Entity *EntityFactory::createPlayer(int life, int positionX, int positionY)
{
    return new Player(life, positionX, positionY);
}

Entity *EntityFactory::createPlayerMissile(int life, int positionX, int positionY)
{
    return new Missile(life, positionX, positionY, PLAYER_MISSILE);
}

Entity *EntityFactory::createEnemyMissile(int life, int positionX, int positionY)
{
    return new Missile(life, positionX, positionY, ENEMY_MISSILE);
}

Entity *EntityFactory::createEnemy(int life, int positionX, int positionY)
{
    return new Enemy(life, positionX, positionY);
}