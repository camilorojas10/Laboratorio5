#ifndef PUNTOS_H
#define PUNTOS_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QObject>
#include <QPainter>

class puntos: public QObject, public QGraphicsItem
{
public:
    puntos();
    QPixmap *pixmap;
    int r=4;                //Radio
    int posx, posy;
    puntos(int x, int y);
    QRectF boundingRect() const;        //Dibujar
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);//Funcion QT
};

#endif // PUNTOS_H
