#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    const int playerSpeed = 35;
public slots:
    void spawn();
private:
    QMediaPlayer * bulletSound;
    QMediaPlayer * explosionSound;
};

#endif // PLAYER_H
