#include <iostream>
#include <unistd.h>
#include "includes/Game.hpp"

using namespace std;

int main(void)
{
    Game *game = new Game;
    game->start();
    delete (game);
    return 0;
}
