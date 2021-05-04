#include "Health.h"
#include <QFont>

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
}

int Health::getHealth()
{
    return health;
}
