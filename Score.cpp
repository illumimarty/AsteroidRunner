#include "Score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    //initialize the score to zero
    score = 0;

    //draw the text
    setPlainText(QString("Score: ") + QString::number(score));
    //set the text's color
    setDefaultTextColor(Qt::blue);
    //set the text's font QFont(string of name of font, int of size of font)
    setFont(QFont("times", 16));
}

void Score::increase()
{
    score++;
    //redraw the text
    setPlainText(QString("Score: ") + QString::number(score));
}

int Score::getScore()
{
    return score;
}
