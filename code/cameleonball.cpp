#include "cameleonball.h"

CameleonBall::CameleonBall(int size, int color, QWidget *parent)
    : Ball(size, color, parent)
{
}

void CameleonBall::paint() {
    QPixmap map(size,size);
    map.fill(Qt::transparent);
    QPainter paintingTool;
    paintingTool.begin(&map);
    QImage img(colors[color]);
    paintingTool.drawImage(QRectF(0,0,size,size), img);
    QImage extraImg(":/extra/cameleon.png");
    paintingTool.drawImage(QRectF((int) size/2,0,(int) size/2,(int) size/2), extraImg);
    paintingTool.end();
    hide();
    setPixmap(map);
    show();
}

void CameleonBall::nextTurn() {
}
