#include "../includes/Game.hpp"
#include "../includes/EntityFactory.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

Game::Game()
{
    m_ncurses = new Ncurses(35, 50);
    m_max_missile = 2;
    m_score = 0;
    m_level = 0;
    m_player = nullptr;
    m_enemyCounter = 0;
    srand(time(NULL));
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
    int maxHeight = m_ncurses->getMaxGameWindowHeight();
    int maxWidth = m_ncurses->getMaxGameWindowWidth();
    if (m_level == 0)
    {

        int playerX = maxHeight - 2;
        int playerY = maxWidth / 2;
        m_player = EntityFactory::createPlayer(100, playerX, playerY);
        std::pair<int, int> position = std::pair<int, int>(playerX, playerY);
        if (m_player)
        {
            m_entityMap[position] = m_player;
            m_entityVector.push_back(m_player);
        }
    }
    for (int i = 1; i < m_level + 2; i += 1)
    {
        for (int j = 4; j < m_level * 2 + 4 && j < maxHeight; j += 2)
        {
            Entity *enemy = EntityFactory::createEnemy(10, i, j);
            if (enemy)
            {
                m_entityMap[std::pair<int, int>(i, j)] = enemy;
                m_entityVector.insert(m_entityVector.begin(), enemy);
                m_enemyCounter++;
            }
        }
    }
}

void Game::move(Entity *entity)
{
    std::pair<int, int> position = entity->getPosition();
    int max_width = m_ncurses->getMaxGameWindowWidth();
    int max_heigth = m_ncurses->getMaxGameWindowHeight();
    if (m_entityMap.count(position) > 0)
        m_entityMap.erase(position);

    position = entity->move(max_width, max_heigth);
    if (position.first >= max_heigth && entity->getType() != PLAYER && entity->getType() != ENEMY_MISSILE)
    {
        m_level = -2;
    }
    // Delete Player missile
    else if (position.first < 0)
    {
        if (m_entityToClean.count(entity->getPosition()) == 0)
            m_entityToClean[entity->getPosition()] = entity;
    }
    // Delete Enemy missile
    else if (position.first > max_heigth)
    {
        if (m_entityToClean.count(entity->getPosition()) == 0)
            m_entityToClean[entity->getPosition()] = entity;
    }
    else if (m_entityMap.count(position) > 0 &&
             !((entity->getType() == ENEMY_MISSILE && m_entityMap[position]->getType() == ENEMY) ||
               (entity->getType() == ENEMY && m_entityMap[position]->getType() == ENEMY_MISSILE)))
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
        if (m_entityMap.count(position) > 0 || (m_entityMap.count(position) == 0 && entity->getType() != ENEMY_MISSILE))
            m_entityMap[position] = entity;
    }
}

void Game::cleanEntity()
{
    std::map<std::pair<int, int>, Entity *>::iterator it;
    for (it = m_entityToClean.begin(); it != m_entityToClean.end(); it++)
    {
        Entity *entity = it->second;
        EntityType type = entity->getType();
        switch (type)
        {
        case PLAYER_MISSILE:
            m_max_missile++;
            break;
        case ENEMY:
            m_enemyCounter--;
            break;
        default:
            break;
        }
        m_entityMap.erase(entity->getPosition());
        m_entityVector.erase(std::remove(m_entityVector.begin(), m_entityVector.end(), entity), m_entityVector.end());
        delete entity;
    }
    m_entityToClean.clear();
    if (m_enemyCounter == 0)
        m_level++;
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
            case PLAYER_MISSILE:
                if (frame % 8 == 0)
                    move(entity);
                break;
            case ENEMY_MISSILE:
                if (frame % 8 == 0)
                    move(entity);
                break;
            case ENEMY:
                if (frame % 4 == 0)
                {
                    move(entity);
                    if ((rand() % (50 + m_level * 100) + 1) == 20)
                        addMissile(ENEMY_MISSILE, entity);
                }
                break;
            case PLAYER:
                move(entity);
                break;
            default:
                break;
            }
        }
        index++;
    }
    cleanEntity();
}

void Game::addMissile(EntityType missileType, Entity *entity)
{
    std::pair<int, int> position;
    Entity *missile = nullptr;
    if (missileType == PLAYER_MISSILE && m_max_missile >= 0)
    {
        position = m_player->getPosition();
        position.first--;
        if (m_entityMap.count(position) == 0)
        {
            missile = EntityFactory::createPlayerMissile(100, position.first, position.second);
            m_entityMap[missile->getPosition()] = missile;
            m_entityVector.push_back(missile);
            m_max_missile--;
        }
    }
    else if (missileType == ENEMY_MISSILE && entity != nullptr)
    {

        position = entity->getPosition();
        position.first++;
        missile = EntityFactory::createEnemyMissile(100, position.first, position.second);
        if (m_entityMap.count(position) == 0)
        {
            m_entityMap[missile->getPosition()] = missile;
            m_entityVector.push_back(missile);
        }
    }
}

void Game::retrieveUserInput()
{
    m_ncurses->getUserInput(m_keyPresseds);
    std::pair<int, int> position;
    if (m_player != nullptr)
    {
        position = m_player->getPosition();

        while (!m_keyPresseds.empty())
        {
            int keyPressed = m_keyPresseds.front();
            m_keyPresseds.pop();
            switch (keyPressed)
            {
            case KEY_LEFT:
            case KEY_RIGHT:
                if (m_entityMap.count(position) > 0)
                    m_entityMap.erase(position);
                m_player->setPosition(position.first, position.second + 1 * (keyPressed == KEY_LEFT ? -1 : 1));
                break;
            case 'c':
                m_level = -2;
                break;
            case ' ':
                addMissile(PLAYER_MISSILE);
                break;
            }
        }
    }
}

double Game::getCurrentTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = currentTime.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}

void Game::start()
{
    const double targetFrameTime = 0.016; // Temps cible par frame (en secondes, par exemple 1/60)

    // Créer un thread pour récupérer les entrées utilisateur
    std::thread inputThread([this]()
                            {
        while (m_level >= 0) {
            retrieveUserInput();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        } });

    while (m_level >= 0)
    {
        // Initialiser le niveau;
        loadLevel();
        int frame = 0;
        double startTime, endTime, deltaTime;

        while (m_enemyCounter > 0 && m_level >= 0)
        {
            if (frame > 12)
                frame = 0;
            m_ncurses->clearGameWindow();
            updateEntity(frame);
            for (auto &entity : m_entityVector)
            {
                if (entity)
                    m_ncurses->inGameDraw(entity->getPosition().first, entity->getPosition().second, entity->renderer());
            }
            m_ncurses->refreshGameWindow();

            // Mesurer le temps écoulé
            startTime = getCurrentTime();

            // Calculer la durée de cette frame
            endTime = getCurrentTime();
            deltaTime = endTime - startTime;

            // Attendre jusqu'à ce que le temps de la frame soit atteint
            double sleepTime = targetFrameTime - deltaTime;
            if (sleepTime > 0)
            {
                usleep(sleepTime * 1000000); // Convertir le temps de sommeil en microsecondes
            }

            frame++;
        }
        m_level++;
    }

    inputThread.join();
}
