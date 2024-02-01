#include "../includes/Missile.hpp"
#include <string>

Missile::Missile(int life, int positionX, int positionY, EntityType type)
    : Entity(life, positionX, positionY)
{
    m_type = type;
    m_reprentation = m_type == PLAYER_MISSILE ? 'i' : '*';
    m_speed = m_type == PLAYER_MISSILE ? 50 : 25;
}

Missile::~Missile()
{
}

char *Missile::renderer() const
{
    return new char(m_reprentation);
}

std::pair<int, int> Missile::move(int max_width, int max_weigth)
{
    std::pair<int, int> position = m_position;
    position.first += 1 * (m_type == PLAYER_MISSILE ? -1 : 1);
    return position;
}

EntityType Missile::getType() const
{
    return m_type;
}