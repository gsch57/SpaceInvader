#include "../includes/Player.hpp"
#include <iostream>

Player::Player(int life, int positionX, int positionY)
    : Entity(life, positionX, positionY)
{
    m_speed = 100;
}

Player::~Player()
{
}

char *Player::renderer() const
{
    return new char('^');
}

std::pair<int, int> Player::move(int max_width, int max_weigth)
{
    return m_position;
}

EntityType Player::getType() const
{
    return PLAYER;
}