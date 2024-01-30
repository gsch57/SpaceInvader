#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <map>
#include "Ncurses.hpp"
#include "Entity.hpp"
#include "Player.hpp"

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

public:
    Game();
    ~Game();
    void start();
    void loadLevel();
    void retrieveUserInput();
    void addMissile();
    void updateEntity(int frame);
    void move(Entity *entity);
    void cleanEntity();
};

#endif // __GAME_H__
