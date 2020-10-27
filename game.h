#ifndef GAME_H
#define GAME_H

// main game window

#include <vector>

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QObject>
#include <QDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QPushButton>
#include <QLayout>

#include "player.h"
#include "enemy.h"
#include "walls.h"

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    Game();

    QGraphicsScene* scene;
    Player* player;
    std::vector<Enemy*> enemies;
    std::vector<Walls*> walls;

    void spawnEnemies(int number_of_enemies);
    void drawHorizontalWall(int x_start, int x_end, int y);
    void drawVerticalWall(int y_start, int y_end, int x);

    void gameover();

public slots:
    void restart_g();

};

#endif // GAME_H
