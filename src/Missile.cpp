#include "../includes/Missile.hpp"
#include <iostream>

Missile::Missile(int life, int positionX, int positionY)
    : Entity(life, positionX, positionY)
{
}

Missile::~Missile()
{
}

char *Missile::renderer() const
{
    return "|";
}

std::pair<int, int> Missile::move(int max_width, int max_weigth)
{
    std::pair<int, int> position = m_position;
    position.first -= 1;
    return position;
}

EntityType Missile::getType() const
{
    return MISSILE;
}