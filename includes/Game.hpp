#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <map>
#include "Ncurses.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include <queue>

class Game
{
private:
    int m_score;
    int m_level;
    int m_max_missile;
    int m_enemyCounter;
    Ncurses *m_ncurses;
    Entity *m_player;
    std::map<std::pair<int, int>, Entity *> m_entityMap;
    std::vector<Entity *> m_entityVector;
    std::map<std::pair<int, int>, Entity *> m_entityToClean;
    std::queue<int> m_keyPresseds;

public:
    Game();
    ~Game();
    void start();
    void loadLevel();
    void retrieveUserInput();
    void addMissile(EntityType missileType, Entity *entity = nullptr);
    void updateEntity(int frame);
    void move(Entity *entity);
    void cleanEntity();
    double getCurrentTime();
};

#endif // __GAME_H__
