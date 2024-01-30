#include "../includes/Player.hpp"
#include <iostream>

Player::Player(int life, int positionX, int positionY)
    : Entity(life, positionX, positionY)
{
}

Player::~Player()
{
}

char *Player::renderer() const
{
    return "^";
}

std::pair<int, int> Player::move(int max_width, int max_weigth)
{
    return m_position;
}

EntityType Player::getType() const
{
    return PLAYER;
}