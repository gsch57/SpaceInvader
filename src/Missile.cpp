#include "../includes/Missile.hpp"
#include "../includes/Entity.hpp"

Missile::Missile(int life, int positionX, int positionY)
    : Entity(life, positionX, positionY)
{
}

char *Missile::renderer() const
{
    return "|";
}

void Missile::move() const
{
}

EntityType Missile::getType() const
{
    return MISSILE;
}