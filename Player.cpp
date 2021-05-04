#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"
#include "Enemy.h"

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
    // create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}
