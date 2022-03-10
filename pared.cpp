#include "pared.h"

pared::pared(int w_, int h_, int x_, int y_)
{
    w=w_;
    h=h_;
    posx=x_;
    posy=y_;
}

QRectF pared::boundingRect() const
{
    return QRectF(-posx,-posy,w,h);
}

void pared::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget)
{
    painter->setBrush(Qt::blue);//color de la pared
    painter->drawRect(boundingRect());//se le dan la posicion y dimensiones del rectangulo "Rect"
}
