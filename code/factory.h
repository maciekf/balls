#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include <cstdlib>
#include <ctime>
#include "ball.h"
#include "cameleonball.h"


class Factory : public QObject
{
    Q_OBJECT
public:
    explicit Factory(QObject *parent = 0);
    int colors;
    int size;
    int joker;
    int bonus;
    int skull;
    int cameleon;
    int hourglass;
    Ball* giveBall(QWidget *parent = 0);

signals:
    
public slots:
    
};

#endif // FACTORY_H
