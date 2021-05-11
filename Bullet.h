#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QMediaPlayer>

class Bullet: public QObject,public QGraphicsPixmapItem{
   Q_OBJECT
public:
   Bullet(QGraphicsItem * parent=0);
public slots:
   void move();
private:
    QMediaPlayer * explosionSound;
};

#endif // BULLET_H
