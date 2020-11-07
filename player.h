#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QKeyEvent>
#include <QPainter>

#include "person.h"

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Player();
    void keyPressEvent(QKeyEvent* event);

    int health() {return curr_health;}
    QGraphicsRectItem* health_bar;

private:
    // player stats
    QPixmap* player_pix;

    int width = 80;
    int height = 40;
    int step_size = 10;                     // length of the player's step on map

    int curr_health = 100;
    int max_health = 100;

    QRect cut_shape;

    bool isWallCollied();
    bool isEnemyCollied();

    bool attack();                          // return true if hit the enemy

    void setRotation(int hex_direction);    // Rotate player according to pressed key

signals:
    void collisionWithEnemy();
};

#endif // PLAYER_H
