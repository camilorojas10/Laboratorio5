#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QGraphicsItem>
#include <QRect>
#include <QtDebug>
#include <QGraphicsScene>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QTimer>
#include "pacman.h"
#include "puntos.h"
#include "fantasma.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();                                    //elimina

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scena;
    pacman *personaje;
    float x,y,ancho,alto; //para darle el tamaño a la pantalla
    int puntaje;
    void keyPressEvent(QKeyEvent *evento);          //Teclado
    bool bordercollision(pacman *personaje);            //Colisiones
    bool verificacion(int caso);                            //verfica que se puede mover
    void puntuacion(pacman *temp);
    void llenado();
    void Transportar(pacman *personaje);
    void MoverFantasma(fantasma *f,int);
};

#endif // MAINWINDOW_H
