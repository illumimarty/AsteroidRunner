#include "Health.h"
#include "Game.h"

#include <QFont>
#include <QMediaPlayer>

extern Game * game; // there is an external global object called game

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    //initialize the score to zero
    health = 3;

    //draw the text
    setPlainText(QString("Health: ") + QString::number(health));
    //set the text's color
    setDefaultTextColor(Qt::red);
    //set the text's font QFont(string of name of font, int of size of font)
    setFont(QFont("times", 16));

}

void Health::decrease()
{
    health--;
    //redraw the text
    setPlainText(QString("Health: ") + QString::number(health));
    QString message;
    if (health <= 0)
    {
        message = "Game Over!";
        game->displayGameOverWindow(message);
        health = 0;
    }
}

int Health::getHealth()
{
    return health;
}
