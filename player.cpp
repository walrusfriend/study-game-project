#include "player.h"
#include "enemy.h"
#include "game.h"

#include <QDebug>

extern Game* game;

Player::Player(QPixmap img)
{
    QPixmap newpix = img.scaled(width, height, Qt::KeepAspectRatio);
    setPixmap(newpix);
    health_bar = new QGraphicsRectItem;
    health_bar->setBrush(Qt::red);
    health_bar->setRect(20, 20, curr_health, 20);
}

void Player::keyPressEvent(QKeyEvent *event)
{

    // works very bad IMHO
    if(event->key() == Qt::Key_A) {
        // try to step on this direction
        setPos(x() - step_size, y());
        // if meet the wall step back
        if(isWallCollied()) {
            setPos(x() + step_size, y());
        }
    }
    else if(event->key() == Qt::Key_D) {
        setPos(x() + step_size, y());
        if(isWallCollied()) {
            setPos(x() - step_size, y());
        }
    }
    else if(event->key() == Qt::Key_W) {
        setPos(x(), y() - step_size);
        if(isWallCollied()) {
            setPos(x(), y() + step_size);
        }
    }
    else if(event->key() == Qt::Key_S) {
        setPos(x(), y() + step_size);
        if(isWallCollied()) {
            setPos(x(), y() - step_size);
        }
    }

    // check for collision with enemy
    isEnemyCollied();
}

bool Player::isWallCollied()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; ++i) {
        if(typeid(*(colliding_items[i])) == typeid(Walls)) {
            qDebug() << "We hit to the wall!";
            return true;
        }
    }
    return false;
}

bool Player::isEnemyCollied()
{
        // if player collides with a enemy, game over
        QList<QGraphicsItem*> colliding_items = collidingItems();
        for(int i = 0, n = colliding_items.size(); i < n; i++){
            if(typeid(*(colliding_items[i])) == typeid(Enemy)) {
                qDebug() << "Collision with enemy!";
                if(curr_health == 0)
                    game->gameover();
                else {
                    curr_health -= 10;
                    health_bar->setRect(20, 20, curr_health, 20);
                }
                return true;
            }
    }
        return false;
}


