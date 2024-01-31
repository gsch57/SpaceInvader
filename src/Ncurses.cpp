#include "../includes/Ncurses.hpp"
#include <stdlib.h>
#include <queue>
#include <iostream>

Ncurses::Ncurses(int const &window_height, int const &window_width) : m_windowHeight(window_height),
                                                                      m_windowWidth(window_width)
{
    initscr();
    nodelay(stdscr, TRUE);
    keypad(stdscr, true); // initialise the keyboard: we can use arrows for directions
    noecho();             // user input is not displayed on the screen
    curs_set(0);          // cursor symbol is not not displayed on the screen (Linux)
    m_maxGameWindowWidth = static_cast<int>(window_width * 0.8);
    m_maxGameWindowHeight = m_windowHeight - 1;

    m_window = newwin(m_windowHeight, m_windowWidth, 0, 0);
    m_gameWindow = subwin(m_window, m_maxGameWindowHeight, m_maxGameWindowWidth, 0, 0);
    m_scoreWindow = subwin(m_window, m_maxGameWindowHeight, m_windowWidth - m_maxGameWindowWidth, 0, m_maxGameWindowWidth);

    // // making box border with default border styles
    box(m_gameWindow, 0, 0);
    box(m_scoreWindow, 0, 0);
    refresh();
    // // move and print in window
    wrefresh(m_gameWindow);
    wrefresh(m_scoreWindow);
}

void Ncurses::getUserInput(std::queue<int> &keyPresseds) const
{
    int c;
    while ((c = getch()) != ERR)
        keyPresseds.push(c);
}

void Ncurses::inGameDraw(const int &x, const int &y, const char *content) const
{
    mvwaddch(m_gameWindow, x, y, content[0]);
}

void Ncurses::clearGameWindow() const
{
    wclear(m_gameWindow);
}

void Ncurses::refreshGameWindow() const
{
    box(m_gameWindow, 0, 0);
    refresh();
    wrefresh(m_gameWindow);
}

void Ncurses::drawScore(const int &x, const int &y, const char *content) const
{
    mvwprintw(m_scoreWindow, x, y, content);
    wrefresh(m_scoreWindow);
}

int Ncurses::getMaxGameWindowWidth() const
{
    return m_maxGameWindowWidth;
}

int Ncurses::getMaxGameWindowHeight() const
{
    return m_maxGameWindowHeight;
}

Ncurses::~Ncurses()
{
    delwin(m_window);
    delwin(m_gameWindow);
    delwin(m_scoreWindow);
    endwin();
}
