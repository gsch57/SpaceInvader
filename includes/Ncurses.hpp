#ifndef __NCURSES_H__
#define __NCURSES_H__

#include <ncurses.h>

class Ncurses
{
private:
    int m_windowHeight;
    int m_windowWidth;
    int m_maxGameWindowWidth;
    int m_maxGameWindowHeight;

    WINDOW *m_window;
    WINDOW *m_gameWindow;
    WINDOW *m_scoreWindow;

public:
    Ncurses(int const &window_height = 50, int const &window_width = 80);
    ~Ncurses();
    int getUserInput() const;

    void inGameDraw(const int &x, const int &y, const char *content) const;
    void drawScore(const int &x, const int &y, const char *content) const;
    void refreshGameWindow() const;
    void clearGameWindow() const;

    int getMaxGameWindowWidth() const;
    int getMaxGameWindowHeight() const;
};

#endif // __NCURSES_H__