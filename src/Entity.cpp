#include "../includes/Entity.hpp"

Entity::Entity(int life, int positionX, int positionY)
{
    m_life = life;
    m_position = std::pair<int, int>(positionX, positionY);
    m_lastUpdateTime = 0.0;
}

std::pair<int, int> Entity::getPosition() const
{
    return m_position;
}

void Entity::setPosition(int positionX, int positionY)
{
    m_position = std::pair<int, int>(positionX, positionY);
}

int Entity::getLife() const
{
    return m_life;
}

char *Entity::renderer() const
{
    return new char();
}