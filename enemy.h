#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QSize>
#include <utility>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(QPixmap img, int width = 80, int height = 40);
};

#endif // ENEMY_H
