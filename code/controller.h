#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>
#include "ball.h"
#include "factory.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QWidget *ballsParent,QObject *parent = 0);
    int players;
    QWidget *ballsParent;
    int size;
    int ballsSize;
    int margin;
    int colors;
    int joker;
    int bonus;
    int skull;
    int cameleon;
    int hourglass;
    int firstScore, secondScore;
    bool firstTurn, game;

    int score;
    int multi;
    QVector<QVector< Ball* > > board;
    Factory *ballGiver;
    static Controller *control;
    void init(QWidget *ballsParent);

private:
    Ball* ballAt(int i, int j);

signals:
    void newFirstScore(int);
    void newSecondScore(int);
    void mayContinue();

public slots:
    void setDefault();
    void fillBoard();
    void removeMatching();
    void gravity();
    void addPoints();
    void moveBalls(Ball *first, Ball *second);
    void setPlayers(int);
    void setSize(int);
    void setColors(int);
};

#endif // CONTROLLER_H
