/*
 *  Simple game
 *
 *  task list:
 *      + create game window
 *      + create player and enemies and place them on the scene
 *      + add collision with player and enemies
 *      + create wall and wall collision with characters (bad)
 *      + add healt bar and death mechanics
 *      + improve a player's movement: add various planes and turning mechanics)
 *      + create confirm window after exit
 *      - add attack motion to the player
 *      - add atatck to the enemies
 *      - create am interface:
 *          - add attack icon in the interface field
 *          - add inventory (a few squares in the bottom of the game scene)
 *          - ..
 *      - create various enemies
 *      - create comparable spawn system
 *      - create level design system
 *      - ...
 *
*/

#include <QApplication>

#include "game.h"

Game* game;
void restart(Game* old_game);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // set random seed
    srand(time(0));

    game = new Game;

    game->show();

    return a.exec();
}

void restart(Game* old_game) {
    old_game->hide();
    delete old_game;

    game = new Game;
    game->show();
}
