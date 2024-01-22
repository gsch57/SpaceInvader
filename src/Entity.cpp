#include "../includes/Entity.hpp"

Entity::Entity(int life, int position)
{
    m_life = life;
    m_position = position;
}

int Entity::getPosition()
{
    return m_position;
}

void Entity::setPosition(int position)
{
    m_position = position;
}

int Entity::getLife()
{
    return m_life;
}

char Entity::renderer()
{
    return char(' ');
}