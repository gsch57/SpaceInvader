#include "../includes/Ncurses.hpp"

Ncurses::Ncurses(int const &window_height, int const &window_width)
{
    initscr();
    // nodelay(stdscr, TRUE);
    // keypad(stdscr, true); // initialise the keyboard: we can use arrows for directions
    // noecho();             // user input is not displayed on the screen
    // curs_set(0);          // cursor symbol is not not displayed on the screen (Linux)

    m_window_height = window_height;
    m_window_width = window_width;

    m_window = newwin(m_window_height, m_window_width, 0, 0);
    m_gameWindow = subwin(m_window, m_window_height, static_cast<int>(window_width * 0.8), 0, 0);

    // // making box border with default border styles
    box(m_window, 0, 0);

    // // move and print in window
    refresh();
    wrefresh(m_window);
    getch();
}

Ncurses::~Ncurses()
{
    delwin(m_window);
    delwin(m_gameWindow);
    endwin();
}
