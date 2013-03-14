#ifndef BALL_H
#define BALL_H

#include <QtGui>
#include <QLabel>
#include <QString>


class Ball : public QLabel
{
    Q_OBJECT
public:
    explicit Ball(int size, int color, QWidget *parent = 0);

    int color;
    int value;
    int multiplier;
    int size;
    bool clicked;

    static QString colors[16];
    void virtual nextTurn();
    void virtual paint();
    bool matches(Ball *another);
    void mousePressEvent(QMouseEvent *event);

signals:
    void click();
public slots:
    
};

#endif // BALL_H
