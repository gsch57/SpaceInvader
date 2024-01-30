#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "Entity.hpp"

class Missile : public Entity
{
private:
    EntityType m_type;
    char m_reprentation;

public:
    Missile(int life, int positionX, int positionY, EntityType type);
    virtual ~Missile();

    virtual char *renderer() const;
    virtual std::pair<int, int> move(int max_width, int max_weigth);
    virtual EntityType getType() const;
};
#endif // __MISSILE_H__