#include "../includes/Entity.hpp"

Entity::Entity(int life, int positionX, int positionY)
{
    m_life = life;
    m_position = std::pair<int, int>(positionX, positionY);
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
    return "";
}

EntityType Entity::getType() const
{
    return m_type;
}