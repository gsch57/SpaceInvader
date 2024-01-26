#include "../includes/Game.hpp"
#include "../includes/EntityFactory.hpp"
#include <unistd.h>
#include <iostream>

Game::Game()
{
    m_ncurses = new Ncurses(35, 80);
    m_score = 0;
    m_level = 0;
    m_player = nullptr;
}

Game::~Game()
{
    delete m_ncurses;
    if (m_player)
        delete m_player;

    for (auto &entity : m_entityVector)
    {
        delete entity;
    }
    m_entityVector.clear();
}

void Game::loadLevel()
{
    // Go read config for level number
    if (m_level == 0)
    {
        int playerX = m_ncurses->getMaxGameWindowWidth() / 2;
        int playerY = m_ncurses->getMaxGameWindowHeight() - 1;

        m_player = EntityFactory::createPlayer(100, playerX, playerY);
        std::pair<int, int> position = std::pair<int, int>(playerX, playerY);
        if (m_player)
        {
            m_entityMap[position] = m_player;
            m_entityVector.push_back(m_player);
        }
    }
}

void Game::updateEntity()
{
    for (auto &entity : m_entityVector)
    {
        // EntityType type = entity->getType();
        // switch (expression)
        // {
        // case /* constant-expression */:
        //     /* code */
        //     break;

        // default:
        //     break;
        // }
    }
}

void Game::addMissile()
{
    std::pair<int, int> position = m_player->getPosition();
    Entity *missile = EntityFactory::createMissile(100, position.first - 1, position.second);
    m_entityMap[missile->getPosition()] = missile;
    m_entityVector.push_back(missile);
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
        while (m_level >= 0)
        {
            retrieveUserInput();
            m_ncurses->clearGameWindow();
            for (auto &entity : m_entityVector)
            {
                m_ncurses->inGameDraw(entity->getPosition().first, entity->getPosition().second, entity->renderer());
            }
            m_ncurses->refreshGameWindow();
        }
        usleep(100);
    }
}
