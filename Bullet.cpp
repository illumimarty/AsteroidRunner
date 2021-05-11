#include "Bullet.h"
#include "Enemy.h"
#include "Game.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QMovie>
#include <QLabel>

extern Game * game; // there is an external global object called game

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // draw the bullet
    setPixmap(QPixmap(":/images/ShipShot.png"));

    //add the explosion sound
    explosionSound = new QMediaPlayer();
    explosionSound->setMedia(QUrl("qrc:/sounds/asteroid_explosion.mp3"));
    explosionSound->setVolume(10);

    // make/connect a timer to move() the bullet every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(30);
}

void Bullet::move(){
    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Enemy)){
            // increase the score
            game->score->increase();
            //play explosion sound
            if (explosionSound->state() == QMediaPlayer::PlayingState){
                explosionSound->setPosition(0);
            }//if its not playing play it
            else if (explosionSound->state() == QMediaPlayer::StoppedState){
                explosionSound->play();
            }
            // remove them from the scene (still on the heap)
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // delete them from the heap to save memory
            delete colliding_items[i];
            delete this;

            // return (all code below refers to a non existint bullet)
            return;
        }
    }

    // if there was no collision with an Enemy, move the bullet forward
    setPos(x(),y()-20);
    // if the bullet is off the screen, destroy it
    if (pos().y() < -30){
        scene()->removeItem(this);
        delete this;
    }
}
