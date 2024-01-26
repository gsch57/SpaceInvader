#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <vector>

enum EntityType
{
    MISSILE,
    PLAYER,
    ENEMY
};

class Entity
{
private:
    int m_life;
    std::pair<int, int> m_position;

public:
    Entity(int life, int positionX, int positionY);
    virtual ~Entity(){};

    virtual char *renderer() const = 0;
    virtual void move() const = 0;

    std::pair<int, int> getPosition() const;
    void setPosition(int positionX, int positionY);
    int getLife() const;
    virtual EntityType getType() const = 0;
};

struct EntityComparator
{
    bool operator()(const Entity &a, const Entity &b) const
    {
        // Utilise l'ordre intrinsèque des énumérations pour le tri
        return a.getType() < b.getType() ||
               (a.getType() == b.getType() && a.getPosition() < b.getPosition()) ||
               (a.getType() == b.getType() && a.getPosition() == b.getPosition() && a.getLife() < b.getLife());
    }
};

#endif // __ENTITY_H__