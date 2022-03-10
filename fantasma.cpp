#include "fantasma.h"

fantasma::fantasma(int x, int y)
{
    posx = x;
    posy = y;
    setPos(posx,posy);
    timer = new QTimer();
    fila = 0;
    columna =120;
    pixmap =new QPixmap(":/imagenes/Pacmandeff.png");

    //dimensiones de cada imagen
    ancho=30;
    alto=30;
    timer->start(100);//tiempo con que cambia la imagen
    connect(timer,&QTimer::timeout,this,&fantasma::Actualizacion);
}
void fantasma::orientacion(int num)     //para ir viendo la oriendatacion es para ir sacando el dibujo
{
    switch (num) {
        case 0:
            minimo=0;
            maximo=60;
            fila=minimo;
        break;
        case 1:
            minimo=60;
            maximo=90;
            fila=minimo;
        break;
        case 2:
            minimo=90;
            maximo=120;
            fila=minimo;
        break;
        case 3:
            minimo=120;
            maximo=150;
            fila=minimo;
        break;
   }
}

int fantasma::getPosx() const
{
    return posx;
}

void fantasma::setPosx(int px)
{
    posx=px;
}

int fantasma::getPosy() const
{
    return posy;
}

void fantasma::setPosy(int py)
{
    posy=py;
}

void fantasma::up()
{
    posy-=velocidad;
    setPos(posx,posy);//dan la nueva posicion
}

void fantasma::down()
{
    posy+=velocidad;
    setPos(posx,posy);
}

void fantasma::left()
{
    posx-=velocidad;
    setPos(posx,posy);
}

void fantasma::right()
{
    posx+=velocidad;
    setPos(posx,posy);
}

void fantasma::Actualizacion()          //va sacando los dibujos de la imagen
{
    fila +=30;
    if(fila>=maximo){
        fila=minimo;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}

QRectF fantasma::boundingRect() const               //dibujar el fantasma
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void fantasma::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columna,fila,ancho,alto);
}
