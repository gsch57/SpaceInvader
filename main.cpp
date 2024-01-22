#include <iostream>
#include <ncurses.h>
#include "includes/IObject.hpp"
#include "includes/Entity.hpp"
#include <unistd.h>

using namespace std;

int main(void)
{
    Entity *test = new Entity(100, 10);
    initscr();
    nodelay(stdscr, TRUE);
    keypad(stdscr, true); // initialise the keyboard: we can use arrows for directions
    noecho();             // user input is not displayed on the screen
    curs_set(0);          // cursor symbol is not not displayed on the screen (Linux)

    // // creating a window;
    // // with height = 15 and width = 10
    // // also with start x axis 10 and start y axis = 20
    WINDOW *gameWin = newwin(25, 50, 0, 0);

    // // making box border with default border styles
    box(gameWin, 0, 0);

    // // move and print in window
    refresh();
    bool continueGame = true;
    int i = 0;
    // game loop
    while (continueGame)
    {
        // print
        mvwprintw(gameWin, 1, test->getPosition(), "A");
        wrefresh(gameWin);
        // retrive key to action game
        int keyPressed = getch();
        switch (keyPressed)
        {
        case KEY_LEFT:
            test->setPosition(test->getPosition() - 1);
            break;
        case KEY_RIGHT:
            test->setPosition(test->getPosition() + 1);
            break;
        case ' ':
            cout << "space" << endl;
            break;
        }
        wclear(gameWin);
        box(gameWin, 0, 0);
        mvwprintw(gameWin, 1, test->getPosition(), "A");
        refresh();
        usleep(10000);
    }
    nodelay(stdscr, false);
    getch();
    endwin();
    free(gameWin);
    return 0;
}
