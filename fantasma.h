#ifndef FANTASMA_H
#define FANTASMA_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

class fantasma:public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    fantasma();
    fantasma(int x, int y);

    QTimer *timer;
    QPixmap *pixmap;

    float fila,columna;
    float ancho,alto;
    int minimo=0,maximo=60;
    //orientacion del pacman:
    void orientacion(int);

    int velocidad=8;                //Pixeles

    //posicion del pacman:350,530
    int posx,posy;
    int getPosx() const;                //toma la posicion
    void setPosx(int px);               //modidficar la posicion
    int getPosy() const;
    void setPosy(int py);

    //Movimientos del pacman:
    void up();
    void down();
    void left();
    void right();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

signals:
public slots: //Funciones que trabaja por si sola sin necesidad de yo estarla llamando
    void Actualizacion();

};

#endif // FANTASMA_H
