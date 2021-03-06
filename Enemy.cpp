#include "Enemy.h"
#include "Game.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int


extern Game * game;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    //set random x position
    int random_number = rand() % 700;
    setPos(random_number,-75);

    // draw the enemy
    setPixmap(QPixmap(":/images/asteroid.png"));

    // make/connect a timer to move() the enemy every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(50);
}

void Enemy::move(){
    // move enemy down with increasing difficulty as score goes up
    if(game->score->getScore() < 10){
        setPos(x(),y()+5);
    }
    if (game->score->getScore() >= 10 && game->score->getScore() < 20){
        setPos(x(),y()+6);
    }
    if (game->score->getScore() >= 20 && game->score->getScore() < 30){
        setPos(x(),y()+7);
    }
    if (game->score->getScore() >= 30 && game->score->getScore() < 40){
        setPos(x(),y()+8.5);
    }
    if (game->score->getScore() >= 40 && game->score->getScore() < 50){
        setPos(x(),y()+12);
    }
    if (game->score->getScore() >= 50 && game->score->getScore() < 60){
        setPos(x(),y()+15);
    }
    if (game->score->getScore() >= 60){
        setPos(x(),y()+18);
    }

    // destroy enemy when it goes out of the screen
    if (pos().y() > 600){
//        decrease the health
        game->health->decrease();

        scene()->removeItem(this);
        delete this;
    }
}
