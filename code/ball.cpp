#include "ball.h"

Ball::Ball(int size, int color, QWidget *parent) :
    QLabel(parent)
{
    this->size = size;
    this->color = color;
    this->value = color;
    this->multiplier = 1;
    clicked = false;
    setFrameShape(QFrame::NoFrame);
    setFrameShadow(QFrame::Plain);
}

QString Ball::colors[16] = {tr(":/ball/0small.png"), tr(":/ball/1small.png"), tr(":/ball/2small.png"), tr(":/ball/3small.png"),
                            tr(":/ball/4small.png"), tr(":/ball/5small.png"), tr(":/ball/6small.png"), tr(":/ball/7small.png"),
                            tr(":/ball/8small.png"), tr(":/ball/9small.png"), tr(":/ball/10small.png"), tr(":/ball/11small.png"),
                            tr(":/ball/12small.png"), tr(":/ball/13small.png"), tr(":/ball/14small.png"), tr(":/ball/15small.png")};

void Ball::paint() {
    QPixmap map(size,size);
    map.fill(Qt::transparent);
    QPainter paintingTool;
    paintingTool.begin(&map);
    QImage img(colors[color]);
    paintingTool.drawImage(QRectF(0,0,size,size), img);
    paintingTool.end();
    hide();
    setPixmap(map);
    show();
}

void Ball::mousePressEvent(QMouseEvent *event) {
    qDebug() << "cos sie stalo";
    clicked = true;
    emit click();
}

void Ball::nextTurn() {
    return;
}

bool Ball::matches(Ball *another) {
    if (another->color == this->color)
        return true;
    if (this->color == 0)
        return true;
    if (another->color == 0)
        return true;
    return false;
}
