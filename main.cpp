#include <iostream>
#include <unistd.h>

#include "includes/IObject.hpp"
#include "includes/Entity.hpp"
#include "includes/Ncurses.hpp"

using namespace std;

int main(void)
{
    Ncurses ncurses(35, 80);

    // bool continueGame = true;
    // int i = 0;
    // // game loop
    // while (continueGame)
    // {
    //     // print
    //     mvwprintw(gameWin, 1, test->getPosition(), "A");
    //     wrefresh(gameWin);
    //     // retrive key to action game
    //     int keyPressed = getch();
    //     switch (keyPressed)
    //     {
    //     case KEY_LEFT:
    //         test->setPosition(test->getPosition() - 1);
    //         break;
    //     case KEY_RIGHT:
    //         test->setPosition(test->getPosition() + 1);
    //         break;
    //     case ' ':
    //         cout << "space" << endl;
    //         break;
    //     }
    //     wclear(gameWin);
    //     box(gameWin, 0, 0);
    //     mvwprintw(gameWin, 1, test->getPosition(), "A");
    //     refresh();
    //     usleep(10000);
    // }
    // nodelay(stdscr, false);
    // getch();
    // endwin();
    // free(gameWin);
    return 0;
}
