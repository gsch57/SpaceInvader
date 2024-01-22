#ifndef __NCURSES_H__
#define __NCURSES_H__

#include <ncurses.h>

class Ncurses
{
private:
    int m_window_height;
    int m_window_width;

    WINDOW *m_window;
    WINDOW *m_gameWindow;

public:
    Ncurses(int const &window_height = 50, int const &window_width = 80);
    ~Ncurses();
};

#endif // __NCURSES_H__