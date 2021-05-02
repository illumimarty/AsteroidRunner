#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <stdlib.h>  // rand()

Enemy::Enemy(): QObject(), QGraphicsRectItem(){

    // set random position
    int randNum = rand() % 700;

    setPos(randNum, 0);


    // drew the rect
    setRect(0,0,10,50);

    // connect
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void Enemy::move(){
    // move enemy up
    setPos(x(),y()+5);
    if(pos().y() + rect().height() < 0){
        scene()->removeItem(this);
        delete this;
        qDebug() << "bullet deleted";
    }
}
