/*
 *  Simple game
 *
 *  task list:
 *      + create game window
 *      + create player and enemies and place them on the scene
 *      + add collision with player and enemies
 *      + create wall and wall collision with characters (bad)
 *      + add healt bar and death mechanics
 *      - create comparable spawn system
 *      - create level design system
 *      - and more...
 *
*/

#include <QApplication>

#include "game.h"

Game* game;
void restart(Game* old_game);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
