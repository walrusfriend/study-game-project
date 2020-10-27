#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QKeyEvent>

#include "person.h"

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Player(QPixmap);
    void keyPressEvent(QKeyEvent* event);

    int health() {return curr_health;}
    QGraphicsRectItem* health_bar;

private:
    // player stats

    int width = 80;
    int height = 40;
    int step_size = 10;

    int curr_health = 100;
    int max_health = 100;


    bool isWallCollied();
    bool isEnemyCollied();

signals:
    void collisionWithEnemy();
};

#endif // PLAYER_H
