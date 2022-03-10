#include "pacman.h"

pacman::pacman(int x, int y)
{
    posx = x;
    posy = y;
    setPos(posx,posy);
    timer = new QTimer();
    fila = 0;
    columna =510
            ;
    pixmap =new QPixmap(":/imagenes/Pacmandeff.png");//Imagen donde está el pacman

    //dimensiones de cada imagen
    ancho=30;
    alto=30;
    timer->start(100);//tiempo con que cambia la imagen
    connect(timer,&QTimer::timeout,this,&pacman::Actualizacion);
}

/*El movimiento de la boca del pacman esta dado por 3 imagenes consecutivas de 30*30 pixeles,al cambiar de direccion se cambian
las filas sobre las cuales se itera*/
void pacman::orientacion(int num)
{
    switch (num) {                       // para ir viendo la direccion donde va abriendo la boca
        case 0:
            minimo=0;
            maximo=90;
            fila=minimo;
        break;
        case 1:
            minimo=90;
            maximo=180;
            fila=minimo;
        break;
        case 2:
            minimo=180;
            maximo=270;
            fila=minimo;
        break;
        case 3:
            minimo=270;
            maximo=360;
            fila=minimo;
        break;
   }
}

int pacman::getPosx() const
{
    return posx;
}

void pacman::setPosx(int px)
{
    posx=px;
}

int pacman::getPosy() const
{
    return posy;
}

void pacman::setPosy(int py)
{
    posy=py;
}

void pacman::up()
{
    posy-=velocidad;
    setPos(posx,posy);//dan la nueva posicion
}

void pacman::down()
{
    posy+=velocidad;
    setPos(posx,posy);
}

void pacman::left()
{
    posx-=velocidad;
    setPos(posx,posy);
}

void pacman::right()
{
    posx+=velocidad;
    setPos(posx,posy);
}

/*Se itera la fila en la que se encuentra el pacman para dar el efecto de abrir y cerrar la boca*/
void pacman::Actualizacion()
{
    fila +=30;
    if(fila>=maximo){               // recorrer casos para dar el efecto
        fila=minimo;
    }
    this->update(-ancho/2,-alto/2,ancho,alto);          //tamaño de la imagen
}

QRectF pacman::boundingRect() const             //Rectangulo para pegar la imagen
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void pacman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)  //Funcion de QT
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columna,fila,ancho,alto);
}

