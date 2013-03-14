#ifndef CAMELEONBALL_H
#define CAMELEONBALL_H

#include "ball.h"

class CameleonBall : public Ball
{
    Q_OBJECT
public:
    explicit CameleonBall(int size, int color, QWidget *parent = 0);
    void virtual paint();
    void virtual nextTurn();
};

#endif // CAMELEONBALL_H
