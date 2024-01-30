#ifndef __ENNEMY_H__
#define __ENNEMY_H__

#include "Entity.hpp"

class Enemy : public Entity
{
private:
    bool m_direction;

public:
    Enemy(int life, int positionX, int positionY);
    virtual ~Enemy();
    virtual char *renderer() const;
    virtual std::pair<int, int> move(int max_width, int max_weigth);
    virtual EntityType getType() const;
};

#endif // __ENNEMY_H__