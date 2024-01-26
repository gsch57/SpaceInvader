#include "../includes/EntityFactory.hpp"
#include <memory>

Entity *EntityFactory::createPlayer(int life, int positionX, int positionY)
{
    return new Player(life, positionX, positionY);
}