#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Game.h"

#include <QGraphicsScene>
#include <QKeyEvent>

extern Game * game; // there is an external global object called game

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    //set the bullet sound
    bulletSound = new QMediaPlayer();
    bulletSound->setMedia(QUrl("qrc:/sounds/Ship_Shot.mp3"));
    bulletSound->setVolume(10);

    //draw player
    setPixmap(QPixmap(":/images/SpaceShip.png"));

}

void Player::keyPressEvent(QKeyEvent *event){

    // move the player left and right
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
        setPos(x()-10,y());
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800)
        setPos(x()+10,y());
    }
    // shoot with the spacebar
    else if (event->key() == Qt::Key_Space){
        // create a bullet
        Bullet * bullet = new Bullet();
        bullet->setPos(x(),y());
        scene()->addItem(bullet);

        //play bullet sound
        //if its playing set the position to the beginning
        if (bulletSound->state() == QMediaPlayer::PlayingState){
            bulletSound->setPosition(0);
        }//if its not playing play it
        else if (bulletSound->state() == QMediaPlayer::StoppedState){
            bulletSound->play();
        }

    }
}

void Player::spawn(){
    // get a list of all the items currently colliding with this player
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Enemy)){
            // decrease the score
            game->health->decrease();

            // remove them from the scene (still on the heap)
            scene()->removeItem(colliding_items[i]);

            // delete them from the heap to save memory
            delete colliding_items[i];
            // return (all code below refers to a non existint bullet)
            return;
        }
    }
}
