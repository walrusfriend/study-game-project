#include "player.h"
#include "enemy.h"
#include "game.h"

#include <QDebug>

extern Game* game;

Player::Player()
{
    player_pix = new QPixmap(":/image/player.png");

    // Set the border of the cutting frame
    cut_shape = QRect(0, 0, 20, 40);
    // Cut image and set it in player image
    QPixmap cutted = player_pix->copy(cut_shape);
    setPixmap(cutted);

    // Set start position
    setPos(400, 300);

    // Set health properties
    health_bar = new QGraphicsRectItem;
    health_bar->setBrush(Qt::red);
    health_bar->setRect(20, 20, curr_health, 20);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    // works very bad IMHO
    if(key == Qt::Key_A) {
        // Turn player to the up
        setRotation(event->key());

        // try to step on this direction
        setPos(x() - step_size, y());
        // if meet the wall step back
        if(isWallCollied()) {
            setPos(x() + step_size, y());
        }
    }
    else if(key == Qt::Key_D) {
        // Turn player to the down
        setRotation(event->key());

        // Try tp step
        setPos(x() + step_size, y());
        if(isWallCollied()) {
            setPos(x() - step_size, y());
        }
    }
    else if(key == Qt::Key_W) {
        // Turn player to the right
        setRotation(event->key());

        // Try tp step
        setPos(x(), y() - step_size);
        if(isWallCollied()) {
            setPos(x(), y() + step_size);
        }
    }
    else if(key == Qt::Key_S) {
        // Turn player to the left
        setRotation(event->key());

        // Try tp step
        setPos(x(), y() + step_size);
        if(isWallCollied()) {
            setPos(x(), y() - step_size);
        }
    }
    else if (key == Qt::Key_Space) {
        if(attack()) {
            // hit an enemy

        }
    }
    else if(key == Qt::Key_Escape) {
        game->gameover();
    }

    // check for collision with enemy
    isEnemyCollied();
}

bool Player::isWallCollied()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; ++i) {
        if(typeid(*(colliding_items[i])) == typeid(Walls)) {
            //qDebug() << "We hit to the wall!";
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
            //qDebug() << "Collision with enemy!";
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

bool Player::attack()
{
    return true;
}

void Player::setRotation(int hex_direction)
{
    // The numbering of the keys in accordance
    //with player rotation on the picture

    //qDebug() << "Select rotation:" << hex_direction;
    switch (hex_direction) {
    case Qt::Key_S:
        cut_shape.setCoords(0, 0, 20, 40);
        break;
    case Qt::Key_W:
        cut_shape.setCoords(20, 0, 40, 40);
        break;
    case Qt::Key_D:
        cut_shape.setCoords(40, 0, 60, 40);
        break;
    case Qt::Key_A:
        cut_shape.setCoords(60, 0, 80, 40);
        break;
    }
    QPixmap cutted = player_pix->copy(cut_shape);
    setPixmap(cutted);
}
