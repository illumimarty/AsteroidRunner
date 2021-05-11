#include "Game.h"
#include "Enemy.h"
#include "Button.h"

#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QImage>
#include <QDebug>
#include <QMediaPlaylist>


Game::Game(QWidget *parent){
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600); // make the scene 800x600 instead of infinity by infinity (default)
    setBackgroundBrush(QBrush(QImage(":/images/Background2.png")));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    // play background music
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/Galaxy_Blast.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlayer * music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(10);
    music->play();
}

void Game::start(){


    qDebug() << "new";
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600); // make the scene 800x600 instead of infinity by infinity (default)
    setBackgroundBrush(QBrush(QImage(":/images/Background.png")));

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    // create the player
    player = new Player();
    player->setPos(350,500); // TODO generalize to always be in the middle bottom of screen
    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // add the player to the scene
    scene->addItem(player);

    // create the score/health
    score = new Score();
    score->setPos(score->x()+400, score->y()+569);
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x()+300,health->y()+570);
    scene->addItem(health);

    // spawn enemies
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(1100);
}

void Game::restartGame(){
    //clear all items
    scene->clear();
    start();
}


void Game::displayGameOverWindow(QString textToDisplay){

    timer->stop();
    QObject::disconnect(timer, SIGNAL(timeout()),player,SLOT(spawn()));
    // create playAgain button
    Button* playAgain = new Button(QString("Play Again"));
    int bxPos = this->width()/2 - playAgain->boundingRect().width()/2;
    int byPos = 275;
    playAgain->setPos(bxPos,byPos);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));

    // create quit button
    Button* quit = new Button(QString("Main Menu"));
    int qxPos = this->width()/2 - quit->boundingRect().width()/2;
    int qyPos = 350;
    quit->setPos(qxPos,qyPos);
    scene->addItem(quit);
    connect(quit,SIGNAL(clicked()),this,SLOT(displayMainMenu()));

    // create text
    QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
    overText->setPos(460,225);
    scene->addItem(overText);
}

void Game::displayMainMenu(){
    scene->clear();
    // create the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600); // make the scene 800x600 instead of infinity by infinity (default)
    setBackgroundBrush(QBrush(QImage(":/images/Background.png")));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    //create the title
    title = new Title();
    int titleXPos = this->width()/2 - title->boundingRect().width()/2;
    int titleYPos = 100;
    title->setPos(titleXPos, titleYPos);
    scene->addItem(title);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}
