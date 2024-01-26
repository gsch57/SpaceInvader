#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "Entity.hpp"

class Missile : public Entity
{
private:
public:
    Missile(int life, int positionX, int positionY);

    virtual char *renderer() const;
    virtual void move() const;
    virtual EntityType getType() const;
};
#endif // __MISSILE_H__