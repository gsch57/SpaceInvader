#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.hpp"

class Player : public Entity
{
private:
public:
    Player(int life, int positionX, int positionY);

    virtual char *renderer() const;
    virtual void move() const;
};

#endif // __PLAYER_H__