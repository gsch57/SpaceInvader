#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "IObject.hpp"

class Entity : public IObject
{
private:
    int m_life;
    int m_position;

public:
    Entity(int life, int position);
    // virtual void fire() = 0;
    // virtual void move() = 0;
    char renderer();
    int getPosition();
    void setPosition(int position);
    int getLife();
};

#endif // __ENTITY_H__