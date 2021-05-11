#ifndef TITLE_H
#define TITLE_H


#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Title:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Title(QGraphicsItem * parent=0);
};

#endif // TITLE_H
