#include "../includes/Enemy.hpp"
#include <iostream>

Enemy::Enemy(int life, int positionX, int positionY)
    : Entity(life, positionX, positionY)
{
    m_direction = positionX % 2 == 0;
}

Enemy::~Enemy()
{
}

char *Enemy::renderer() const
{
    return new char('W');
}

std::pair<int, int> Enemy::move(int max_width, int max_weigth)
{
    std::pair<int, int> position = m_position;
    if (m_direction && position.second - 1 >= 0)
    {
        position.second -= 1;
    }
    else if (m_direction && position.second - 1 < 0)
    {
        position.first += 1;
        position.second += 1;
        m_direction = !m_direction;
    }
    else if (!m_direction && position.second + 1 < max_width - 1)
    {
        position.second += 1;
    }
    else if (!m_direction && position.second + 1 >= max_width - 1)
    {
        position.second -= 1;
        position.first += 1;
        m_direction = !m_direction;
    }
    return position;
}

EntityType Enemy::getType() const
{
    return ENEMY;
}