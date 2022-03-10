  #ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QDebug>

class pacman:public QObject,public QGraphicsItem
{
    Q_OBJECT
public:

    pacman();
    pacman(int x, int y);

    //QGraphicsScene *scena;            //Graficar la escena
    QTimer *timer;
    QPixmap *pixmap;

    float fila,columna;
    float ancho,alto;
    int minimo=0,maximo=90;

    //orientacion del pacman:
    void orientacion(int);

    int velocidad=8;

    //posicion del pacman:350,530
    int posx,posy;
    int getPosx() const;
    void setPosx(int px);
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

#endif // PACMAN_H
