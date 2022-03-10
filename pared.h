#ifndef PARED_H
#define PARED_H
#include <QGraphicsItem>
#include <QPainter>

class pared: public QGraphicsItem
{
    int w,h;
    int posx, posy;
public:
    pared(int w_, int h_, int x_, int y_);
    QRectF boundingRect() const;  //Funcion para definir el recatangulo que encierra el objeto
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget=nullptr); //Funcion para darle la forma y caracteristicas a la pared

};

#endif // PARED_H
