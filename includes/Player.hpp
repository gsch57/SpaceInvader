#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.hpp"

class Player : public Entity
{
private:
public:
    Player(int life, int positionX, int positionY);
    virtual ~Player();
    virtual char *renderer() const;
    virtual std::pair<int, int> move(int max_width, int max_weigth);
    EntityType getType() const;
};

#endif // __PLAYER_H__