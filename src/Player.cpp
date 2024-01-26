#include "../includes/Player.hpp"
#include "../includes/Entity.hpp"

Player::Player(int life, int positionX, int positionY)
    : Entity(life, positionX, positionY)
{
}

char *Player::renderer() const
{
    return "^";
}

void Player::move() const
{
}

EntityType Player::getType() const
{
    return PLAYER;
}