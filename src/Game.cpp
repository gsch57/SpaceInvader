#include "../includes/Game.hpp"
#include "../includes/EntityFactory.hpp"
#include <unistd.h>
#include <iostream>

Game::Game()
{
    m_ncurses = new Ncurses(35, 50);
    m_max_missile = 2;
    m_score = 0;
    m_level = 0;
    m_player = nullptr;
}

Game::~Game()
{
    if (m_ncurses)
        delete m_ncurses;
    for (auto &entity : m_entityVector)
    {
        if (entity)
            delete entity;
    }

    m_entityVector.clear();
    m_entityMap.clear();
}

void Game::loadLevel()
{
    // Go read config for level number
    if (m_level == 0)
    {
        int maxHeight = m_ncurses->getMaxGameWindowHeight();
        int maxWidth = m_ncurses->getMaxGameWindowWidth();

        int playerX = maxHeight - 2;
        int playerY = maxWidth / 2;
        m_player = EntityFactory::createPlayer(100, playerX, playerY);
        std::pair<int, int> position = std::pair<int, int>(playerX, playerY);
        if (m_player)
        {
            m_entityMap[position] = m_player;
            m_entityVector.push_back(m_player);
        }
        for (int i = 1; i < 20; i += 3)
        {
            for (int j = 5; j < maxHeight; j += 4)
            {
                Entity *enemy = EntityFactory::createEnemy(10, i, j);
                if (enemy)
                {
                    m_entityMap[std::pair<int, int>(i, j)] = enemy;
                    m_entityVector.insert(m_entityVector.begin(), enemy);
                }
            }
        }
    }
}

void Game::move(Entity *entity, int index)
{
    std::pair<int, int> position = entity->getPosition();
    int max_width = m_ncurses->getMaxGameWindowWidth();
    int max_heigth = m_ncurses->getMaxGameWindowHeight();
    if (m_entityMap[position])
        m_entityMap.erase(position);

    position = entity->move(max_width, max_heigth);
    if (position.first >= max_heigth - 2 && entity->getType() != PLAYER)
    {
        m_level = -1;
    }
    else if (position.first < 0)
    {
        if (m_entityToClean.count(entity->getPosition()) == 0)
            m_entityToClean[entity->getPosition()] = entity;
    }
    else if (m_entityMap[position] != NULL)
    {
        Entity *otherEntity = m_entityMap[position];
        if (m_entityToClean.count(entity->getPosition()) == 0)
            m_entityToClean[entity->getPosition()] = entity;
        if (m_entityToClean.count(otherEntity->getPosition()) == 0)
            m_entityToClean[otherEntity->getPosition()] = otherEntity;
    }
    else
    {
        entity->setPosition(position.first, position.second);
        m_entityMap[position] = entity;
    }
}

void Game::updateEntity(int frame)
{
    int index = 0;
    while (index < m_entityVector.size())
    {
        Entity *entity = m_entityVector[index];

        if (entity)
        {
            EntityType type = entity->getType();
            switch (type)
            {
            case MISSILE:
                if (frame % 8 == 0)
                    move(entity, index);
                break;
            // case ENEMY:
            //     if (frame % 4 == 0)
            //         move(entity, index);
            //     break;
            case PLAYER:
                move(entity, index);
                break;
            }
        }
        index++;
    }
    std::map<std::pair<int, int>, Entity *>::iterator it;
    for (it = m_entityToClean.begin(); it != m_entityToClean.end(); it++)
    {
        Entity *entity = it->second;

        if (entity->getType() == MISSILE)
            m_max_missile++;
        m_entityMap.erase(entity->getPosition());
        m_entityVector.erase(std::remove(m_entityVector.begin(), m_entityVector.end(), entity), m_entityVector.end());
        delete entity;
    }
    m_entityToClean.clear();
}

void Game::addMissile()
{
    if (m_max_missile >= 0)
    {
        std::pair<int, int> position = m_player->getPosition();
        position.first -= 1;
        if (m_entityMap.count(position) == 0)
        {
            Entity *missile = EntityFactory::createMissile(100, position.first, position.second);
            m_entityMap[missile->getPosition()] = missile;
            m_entityVector.push_back(missile);
            m_max_missile -= 1;
        }
    }
}

void Game::retrieveUserInput()
{
    int keyPressed = m_ncurses->getUserInput();
    std::pair<int, int> position;
    if (m_player)
        position = m_player->getPosition();

    switch (keyPressed)
    {
    case KEY_LEFT:
        if (m_player)
        {
            m_player->setPosition(position.first, position.second - 1);
        }
        break;
    case KEY_RIGHT:
        if (m_player)
        {
            m_player->setPosition(position.first, position.second + 1);
        }
        break;
    case 'c':
        m_level = -1;
        break;
    case ' ':
        if (m_player)
        {
            addMissile();
        }
        break;
    }
}

void Game::start()
{
    // Main loop;
    while (m_level >= 0)
    {
        // Init the level;
        loadLevel();
        int index = 0;
        while (m_level >= 0)
        {
            if (index > 12)
                index = 0;
            m_ncurses->clearGameWindow();
            updateEntity(index);
            retrieveUserInput();
            for (auto &entity : m_entityVector)
            {
                if (entity)
                    m_ncurses->inGameDraw(entity->getPosition().first, entity->getPosition().second, entity->renderer());
            }
            m_ncurses->refreshGameWindow();
            usleep(10000);
            index++;
        }
    }
}
