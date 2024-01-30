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
        Entity *enemy = EntityFactory::createEnemy(10, 10, 10);
        if (enemy)
        {
            m_entityMap[std::pair<int, int>(10, 10)] = enemy;
            m_entityVector.push_back(enemy);
        }
    }
}

void Game::moveMissile(Entity *missile, int index)
{
    std::pair<int, int> position = missile->getPosition();
    position.first--; // Déplacement vers la gauche

    // Vérifier s'il y a une collision avec un ennemi
    if (m_entityMap.count(position) && m_entityMap[position]->getType() == ENEMY)
    {
        // Supprimer l'ennemi de m_entityMap et m_entityVector
        Entity *enemy = m_entityMap[position];
        m_entityMap.erase(position);
        m_entityVector.erase(std::remove(m_entityVector.begin(), m_entityVector.end(), enemy), m_entityVector.end());

        // Supprimer le missile de m_entityMap et m_entityVector
        m_entityMap.erase(missile->getPosition());
        m_entityVector.erase(m_entityVector.begin() + index);

        // Supprimer les objets de la mémoire
        delete enemy;
        delete missile;
    }
    else
    {
        // Déplacer le missile
        if (position.first >= 0)
        {
            // Mettre à jour la position du missile dans m_entityMap
            m_entityMap.erase(missile->getPosition());
            missile->setPosition(position.first, position.second);
            m_entityMap[position] = missile;
        }
        else
        {
            // Supprimer le missile s'il sort de l'écran
            m_entityMap.erase(missile->getPosition());
            m_entityVector.erase(m_entityVector.begin() + index);
            delete missile;
        }
    }
}

void Game::updateEntity()
{
    int index = 0;
    for (auto &entity : m_entityVector)
    {
        if (entity)
        {
            EntityType type = entity->getType();
            switch (type)
            {
            case MISSILE:
                moveMissile(entity, index);
                break;
            }
        }
        index++;
    }
}

void Game::addMissile()
{
    std::pair<int, int> position = m_player->getPosition();
    position.first -= 1;
    if (m_entityMap[position] == NULL)
    {
        Entity *missile = EntityFactory::createMissile(100, position.first, position.second);
        m_entityMap[missile->getPosition()] = missile;
        m_entityVector.push_back(missile);
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
        while (m_level >= 0)
        {
            retrieveUserInput();
            m_ncurses->clearGameWindow();
            updateEntity();
            for (auto &entity : m_entityVector)
            {
                if (entity)
                    m_ncurses->inGameDraw(entity->getPosition().first, entity->getPosition().second, entity->renderer());
            }
            m_ncurses->refreshGameWindow();
            usleep(100000);
        }
    }
}
