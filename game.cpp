#include "game.h"

extern void restart(Game* old_game);

Game::Game()
{
    // create a scene
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 800, 600);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);

    // create a player
    player = new Player();
    scene->addItem(player);

    // make the player focusable and set him to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add health bar to the scene
    scene->addItem(player->health_bar);

    // draw wall frame
    drawHorizontalWall(0, 800, 0);
    drawHorizontalWall(0, 800, 600 - 20);
    drawVerticalWall(0, 600, 0);
    drawVerticalWall(0, 600, 800 - 20);

    // spawn enemies
    spawnEnemies(10);

}

void Game::spawnEnemies(int number_of_enemies)
{
    for(int i = 0; i < number_of_enemies; i++) {
        // step 1. Create the enemy
        Enemy* enemy = new Enemy(QPixmap(":/image/enemy.png"));

        // step 2. Generate the position
        enemy->setPos(rand() % (800 - 80), rand() % (600 - 40));

        // step 3. Place the enemy
        enemies.push_back(enemy);
        scene->addItem(enemies.back());

        // step 4. Check the collision
        QList<QGraphicsItem*> colliding_items = enemy->collidingItems();
        if(colliding_items.size()) {
            i--;
            scene->removeItem(enemies.back());
            delete enemy;
            continue;
        }
    }
}

void Game::drawHorizontalWall(int x_start, int x_end, int y) {
    QPixmap wall_brick_pix(QPixmap(":/image/brick.png").scaled(20, 20, Qt::KeepAspectRatio));
    for(int x = x_start; x <= x_end; ) {
        Walls* wall = new Walls;
        wall->setPixmap(wall_brick_pix);
        wall->setPos(x, y);
        walls.push_back(wall);
        scene->addItem(wall);
        x += wall_brick_pix.height();
    }
}

void Game::drawVerticalWall(int y_start, int y_end, int x) {
    QPixmap wall_brick_pix(QPixmap(":/image/brick.png").scaled(20, 20, Qt::KeepAspectRatio));
    for(int y = y_start; y <= y_end; ) {
        Walls* wall = new Walls;
        wall->setPixmap(wall_brick_pix);
        wall->setPos(x, y);
        walls.push_back(wall);
        scene->addItem(wall);
        y += wall_brick_pix.height();
    }
}

void Game::gameover()
{
    QDialog* gameover_win = new QDialog;
    gameover_win->setAttribute(Qt::WA_DeleteOnClose);
    gameover_win->setGeometry(
                (QApplication::desktop()->screenGeometry().width() - 200) / 2,
                (QApplication::desktop()->screenGeometry().height() - 200) / 2,
                200, 200);

    QLabel* message = new QLabel;
    message->setText("Game over");
    message->setAlignment(Qt::AlignCenter);

    QPushButton* pbt_restart = new QPushButton("&Restart");
    QPushButton* pbt_exit = new QPushButton("&Exit");

    QHBoxLayout* hbl = new QHBoxLayout;
    hbl->addWidget(pbt_restart);
    hbl->addWidget(pbt_exit);

    QVBoxLayout* vbl = new QVBoxLayout;
    vbl->addWidget(message);
    vbl->addLayout(hbl);

    // linking
    QObject::connect(pbt_restart, SIGNAL(clicked()), gameover_win, SLOT(close()));
    QObject::connect(pbt_restart, SIGNAL(clicked()), SLOT(restart_g()));

    //QObject::connect(pbt_exit, SIGNAL(clicked()), gameover_win, SLOT(close()));
    QObject::connect(pbt_exit, SIGNAL(clicked()), SLOT(confirmWindow()));

    gameover_win->setLayout(vbl);

    gameover_win->exec();

}

void Game::restart_g()
{
    restart(this);
}

void Game::confirmWindow(){
    QDialog* confirm_win = new QDialog;
    confirm_win->setAttribute(Qt::WA_DeleteOnClose);
    int widht = 200;
    int height = 100;
    confirm_win->setGeometry(
                (QApplication::desktop()->screenGeometry().width() - widht) / 2,
                (QApplication::desktop()->screenGeometry().height() - height) / 2,
                widht, height);

    QLabel* message = new QLabel;
    message->setText("You're sure?");
    message->setAlignment(Qt::AlignCenter);

    QPushButton* pbt_yes = new QPushButton("&Yes");
    QPushButton* pbt_no = new QPushButton("&No");

    QHBoxLayout* hbl = new QHBoxLayout;
    hbl->addWidget(pbt_yes);
    hbl->addWidget(pbt_no);

    QVBoxLayout* vbl = new QVBoxLayout;
    vbl->addWidget(message);
    vbl->addLayout(hbl);

    // linking
    QObject::connect(pbt_yes, SIGNAL(clicked()), confirm_win, SLOT(close()));
    QObject::connect(pbt_yes, SIGNAL(clicked()), qApp, SLOT(closeAllWindows()));

    QObject::connect(pbt_no, SIGNAL(clicked()), confirm_win, SLOT(close()));

    confirm_win->setLayout(vbl);

    confirm_win->exec();
}

