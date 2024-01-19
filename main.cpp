#include <iostream>
#include <ncurses.h>

using namespace std;

int main(void)
{
    initscr();

    // creating a window;
    // with height = 15 and width = 10
    // also with start x axis 10 and start y axis = 20
    WINDOW *gameWin = newwin(25, 50, 0, 0);
    WINDOW *scoreWin = newwin(25, 20, 0, 50);
    refresh();

    // making box border with default border styles
    box(gameWin, 0, 0);
    box(scoreWin, 0, 0);

    // move and print in window
    mvwprintw(gameWin, 1, 1, "A");
    mvwprintw(gameWin, 2, 1, "B");

    // move and print in window
    mvwprintw(scoreWin, 1, 1, "SCORE");
    mvwprintw(scoreWin, 2, 1, "100");

    // refreshing the window
    wrefresh(gameWin);
    wrefresh(scoreWin);

    getch();
    endwin();
    free(gameWin);
    free(scoreWin);
    return 0;
}
