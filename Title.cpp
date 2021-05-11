#include "Title.h"
#include "Game.h"

#include <QGraphicsScene>

extern Game * game; // there is an external global object called game

Title::Title(QGraphicsItem *parent): QGraphicsPixmapItem(parent){

    //draw title
    setPixmap(QPixmap(":/images/title.png"));

}
