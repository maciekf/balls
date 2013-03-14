#include "factory.h"

Factory::Factory(QObject *parent) :
    QObject(parent)
{
    srand((unsigned)time(0));
}

Ball* Factory::giveBall(QWidget *parent) {
    int currcolor = (rand() % colors) +1;
    return new Ball(size, currcolor, parent);
}
