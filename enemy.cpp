#include "enemy.h"
#include "game.h"

#include <QDebug>

extern Game* game;

Enemy::Enemy(QPixmap img, int width, int height)
{
    QPixmap newpix = img.scaled(width, height, Qt::KeepAspectRatio);
    setPixmap(newpix);
}


