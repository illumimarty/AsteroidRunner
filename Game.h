#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>

#include "Player.h"
#include "Score.h"
#include "Health.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget * parent=0);

    //public methods
    void displayGameOverWindow(QString textToDisplay);
    void end();


    QGraphicsScene * scene;
    Player * player;
    Score * score;
    Health * health;
    QTimer * timer;


public slots:
     void start();
     void displayMainMenu();
     void restartGame();
};

#endif // GAME_H
