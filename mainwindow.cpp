#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);      //interfax de usuario

    //tamaño y posicion de la pantalla
    x=0;
    y=0;
    ancho=700;      //en pixeles
    alto=700;
    scena=new QGraphicsScene(x,y,ancho,alto);                   //Se crea la escena
    scena->setBackgroundBrush(QPixmap(":/imagenes/mundo.png")); //Se agrega la imagen del laberinto

    ui->graphicsView->setScene(scena);
    ui->graphicsView->setStyleSheet("background-color:black;"); //se agrega un fondo negro

    personaje=new pacman(350,530);                              // Se la dan las condiciones iniciales al personaje

    scena->addItem(personaje);              //lo agrega a la escena
    puntaje=0;
    llenado();                                                   //Funcion que llena de puntos el mapa
    fantasma *f1=new fantasma(40,130);
    scena->addItem(f1);
}

void MainWindow::keyPressEvent(QKeyEvent *evento)                //Verifica cuando precionan una tecla
{
    if(evento->key()==Qt::Key_A){
        if(verificacion(1)==true){                               //Se verifica si el personaje se puede mover
            personaje->orientacion(2);                           //Se le da una orientacion al personaje dependiendo de la direccion
            personaje->left();
        }
    }
    if(evento->key()==Qt::Key_D){
        if(verificacion(2)==true){
            personaje->right();
            personaje->orientacion(0);
        }
    }
    if(evento->key()==Qt::Key_S){
        if(verificacion(3)==true){
            personaje->up();
            personaje->orientacion(3);
        }
    }
    if(evento->key()==Qt::Key_Z){
        if(verificacion(4)==true){
            personaje->down();
            personaje->orientacion(1);
        }
    }
    ui->puntos->setText("Puntuacion: " + QString::number(puntaje));//Se muestra la puntuacion en el label llamado puntos
    puntuacion(personaje);
    Transportar(personaje);
    //MoverFantasma(f1,660);

}

bool MainWindow::verificacion(int caso)
{
    int velocidad = 8;
    int posx = personaje->getPosx();
    int posy = personaje->getPosy();
    pacman *personaje_temp = nullptr;
    bool validate = false;
    //Valida si se puede mover debido a las colisiones con las paredes
    if (caso == 1){
        posx -= 1*velocidad;
        personaje_temp = new pacman(posx,posy);
        validate = bordercollision(personaje_temp);         //valida el limite
    }
    else if (caso == 2) {
        posx+=1*velocidad;
        personaje_temp = new pacman(posx,posy);
        validate = bordercollision(personaje_temp);
    }
    else if (caso == 3) {
        posy -= 1*velocidad;
        personaje_temp = new pacman(posx,posy);
        validate = bordercollision(personaje_temp);
    }
    else if (caso == 4) {
        posy+=1*velocidad;
        personaje_temp = new pacman(posx,posy);
        validate = bordercollision(personaje_temp);
    }
    //Transportar(personaje);
    delete personaje_temp; //Elimina el personaje temporal
    return validate;
}

/*Se verifica cuando el personaje colisiona con un onjetp de la clase puntos para eliminar dicho objeto de la escena*/
void MainWindow::puntuacion(pacman *temp)
{
    QList<QGraphicsItem *>choques=temp->collidingItems(); //Se crea una lista con los objetos que chocan al personaje
    for(int i=0;i<choques.size();i++){                    //Se recorre dicha lista
        if(typeid (*(choques[i]))==typeid(puntos)){       //Se verifica se cada elemento de la lista es de la clase puntos
            scena->removeItem(choques[i]);                //De ser así se elimmina dicho objeto
            puntaje++;                                    //Se suma un punto
        }
    }
}
//Funcion con la que se transporta el personaje a traves de los tuneles
void MainWindow::Transportar(pacman *personaje)
{
    if(personaje->getPosx()<=0){
        personaje->setPosx(680);                            //Cambiar las posiciones en pixeles
        personaje->setPos(680,personaje->getPosy());
    }
    else if(personaje->getPosx()>=700){
        personaje->setPosx(20);
        personaje->setPos(20,personaje->getPosy());
    }
}


void MainWindow::MoverFantasma(fantasma *f,int final)
{
    if(f->getPosx()<=final){
        f->right();
    }

}

bool MainWindow::bordercollision(pacman *personaje) //Para deliminar al personaje
                                                    //Puntos de la imagen
{
    //se definen las posibles posiciones que puede tomar el personaje a lo largo del laberinto
    if(personaje->getPosx()>=35 && personaje->getPosx()<=315 && personaje->getPosy()>=45 && personaje->getPosy()<=55)return true;//1
    if(personaje->getPosx()>=35 && personaje->getPosx()<=660 && personaje->getPosy()>=125 && personaje->getPosy()<=135)return true;//3
    if(personaje->getPosx()>=35 && personaje->getPosx()<=45 && personaje->getPosy()>=45 && personaje->getPosy()<=200)return true;//2
    if(personaje->getPosx()>=650 && personaje->getPosx()<=660 && personaje->getPosy()>=45 && personaje->getPosy()<=200)return true;//4
    if(personaje->getPosx()>=385 && personaje->getPosx()<=660 && personaje->getPosy()>=45 && personaje->getPosy()<=55)return true;//5
    if(personaje->getPosx()>=163 && personaje->getPosx()<=173 && personaje->getPosy()>=45 && personaje->getPosy()<=600)return true;//6
    if(personaje->getPosx()>=305 && personaje->getPosx()<=315 && personaje->getPosy()>=45 && personaje->getPosy()<=135)return true;//7
    if(personaje->getPosx()>=385 && personaje->getPosx()<=395 && personaje->getPosy()>=45 && personaje->getPosy()<=135)return true;//8
    if(personaje->getPosx()>=530 && personaje->getPosx()<=540 && personaje->getPosy()>=45 && personaje->getPosy()<=600)return true;//9
    if(personaje->getPosx()>=35 && personaje->getPosx()<=173 && personaje->getPosy()>=190 && personaje->getPosy()<=200)return true;//10
    if(personaje->getPosx()>=530 && personaje->getPosx()<=660 && personaje->getPosy()>=190 && personaje->getPosy()<=200)return true;//11
    if(personaje->getPosx()>=35 && personaje->getPosx()<=173 && personaje->getPosy()>=590 && personaje->getPosy()<=600)return true;//12
    if(personaje->getPosx()>=530 && personaje->getPosx()<=660 && personaje->getPosy()>=590 && personaje->getPosy()<=600)return true;//13
    if(personaje->getPosx()>=35 && personaje->getPosx()<=45 && personaje->getPosy()>=590 && personaje->getPosy()<=660)return true;//14
    if(personaje->getPosx()>=650 && personaje->getPosx()<=660 && personaje->getPosy()>=590 && personaje->getPosy()<=660)return true;//15
    if(personaje->getPosx()>=35 && personaje->getPosx()<=660 && personaje->getPosy()>=655 && personaje->getPosy()<=660)return true;//16
    if(personaje->getPosx()>=163 && personaje->getPosx()<=540 && personaje->getPosy()>=525 && personaje->getPosy()<=535)return true;//17
    if(personaje->getPosx()>=-20 && personaje->getPosx()<=245 && personaje->getPosy()>=325 && personaje->getPosy()<=335)return true;//18
    if(personaje->getPosx()>=455 && personaje->getPosx()<=720 && personaje->getPosy()>=325 && personaje->getPosy()<=335)return true;//19
    if(personaje->getPosx()>=235 && personaje->getPosx()<=240 && personaje->getPosy()>=525 && personaje->getPosy()<=600)return true;//20
    if(personaje->getPosx()>=310 && personaje->getPosx()<=320 && personaje->getPosy()>=590 && personaje->getPosy()<=660)return true;//21
    if(personaje->getPosx()>=235 && personaje->getPosx()<=320 && personaje->getPosy()>=590 && personaje->getPosy()<=600)return true;//22
    if(personaje->getPosx()>=380 && personaje->getPosx()<=390 && personaje->getPosy()>=590 && personaje->getPosy()<=660)return true;//23
    if(personaje->getPosx()>=380 && personaje->getPosx()<=465 && personaje->getPosy()>=590 && personaje->getPosy()<=600)return true;//24
    if(personaje->getPosx()>=455 && personaje->getPosx()<=465 && personaje->getPosy()>=525 && personaje->getPosy()<=600)return true;//25
    if(personaje->getPosx()>=605 && personaje->getPosx()<=615 && personaje->getPosy()>=525 && personaje->getPosy()<=600)return true;//26
    if(personaje->getPosx()>=605 && personaje->getPosx()<=660 && personaje->getPosy()>=525 && personaje->getPosy()<=535)return true;//27
    if(personaje->getPosx()>=650 && personaje->getPosx()<=660 && personaje->getPosy()>=465 && personaje->getPosy()<=535)return true;//28
    if(personaje->getPosx()>=380 && personaje->getPosx()<=660 && personaje->getPosy()>=460 && personaje->getPosy()<=470)return true;//29
    if(personaje->getPosx()>=85 && personaje->getPosx()<=95 && personaje->getPosy()>=525 && personaje->getPosy()<=600)return true;//30
    if(personaje->getPosx()>=35 && personaje->getPosx()<=95 && personaje->getPosy()>=525 && personaje->getPosy()<=535)return true;//31
    if(personaje->getPosx()>=35 && personaje->getPosx()<=45 && personaje->getPosy()>=465 && personaje->getPosy()<=535)return true;//32
    if(personaje->getPosx()>=35 && personaje->getPosx()<=320 && personaje->getPosy()>=460 && personaje->getPosy()<=470)return true;//33
    if(personaje->getPosx()>=380 && personaje->getPosx()<=390 && personaje->getPosy()>=465 && personaje->getPosy()<=535)return true;//35
    if(personaje->getPosx()>=310 && personaje->getPosx()<=320 && personaje->getPosy()>=465 && personaje->getPosy()<=535)return true;//34
    if(personaje->getPosx()>=235 && personaje->getPosx()<=465 && personaje->getPosy()>=395 && personaje->getPosy()<=405)return true;//36
    if(personaje->getPosx()>=235 && personaje->getPosx()<=245 && personaje->getPosy()>=255 && personaje->getPosy()<=470)return true;//37
    if(personaje->getPosx()>=455 && personaje->getPosx()<=465 && personaje->getPosy()>=255 && personaje->getPosy()<=470)return true;//38
    if(personaje->getPosx()>=235 && personaje->getPosx()<=465 && personaje->getPosy()>=255 && personaje->getPosy()<=265)return true;//39
    if(personaje->getPosx()>=310 && personaje->getPosx()<=320 && personaje->getPosy()>=200 && personaje->getPosy()<=265)return true;//40
    if(personaje->getPosx()>=380 && personaje->getPosx()<=390 && personaje->getPosy()>=200 && personaje->getPosy()<=265)return true;//41
    if(personaje->getPosx()>=235 && personaje->getPosx()<=320 && personaje->getPosy()>=190 && personaje->getPosy()<=200)return true;///42
    if(personaje->getPosx()>=380 && personaje->getPosx()<=465 && personaje->getPosy()>=190 && personaje->getPosy()<=200)return true;///43
    if(personaje->getPosx()>=235 && personaje->getPosx()<=245 && personaje->getPosy()>=125 && personaje->getPosy()<=200)return true;//44
    if(personaje->getPosx()>=455 && personaje->getPosx()<=465 && personaje->getPosy()>=125 && personaje->getPosy()<=200)return true;//45
    if(personaje->getPosx()>=320 && personaje->getPosx()<=380 && personaje->getPosy()>=255 && personaje->getPosy()<=350)return true;//46
    if(personaje->getPosx()>=280 && personaje->getPosx()<=415 && personaje->getPosy()>=310 && personaje->getPosy()<=350)return true;//45
    return false;
}

void MainWindow::llenado()
{
    //Se crean los objetos de la clase puntos para llenar el mapa
    puntos *punt0=new puntos(40,50);            //posiciones en x,y
    scena->addItem(punt0);
    puntos *punt1=new puntos(70,50);
    scena->addItem(punt1);
    puntos *punt2=new puntos(110,50);
    scena->addItem(punt2);
    puntos *punt3=new puntos(150,50);
    scena->addItem(punt3);
    puntos *punt4=new puntos(190,50);
    scena->addItem(punt4);
    puntos *punt5=new puntos(230,50);
    scena->addItem(punt5);
    puntos *punt6=new puntos(270,50);
    scena->addItem(punt6);
    puntos *punt7=new puntos(310,50);
    scena->addItem(punt7);
    puntos *punt8=new puntos(310,90);
    scena->addItem(punt8);
    puntos *punt9=new puntos(310,130);
    scena->addItem(punt9);
    puntos *punt10=new puntos(350,130);
    scena->addItem(punt10);
    puntos *punt11=new puntos(390,130);
    scena->addItem(punt11);
    puntos *punt12=new puntos(390,90);
    scena->addItem(punt12);
    puntos *punt13=new puntos(390,50);
    scena->addItem(punt13);
    puntos *punt14=new puntos(435,50);
    scena->addItem(punt14);
    puntos *punt15=new puntos(479,50);
    scena->addItem(punt15);
    puntos *punt16=new puntos(524,50);
    scena->addItem(punt16);
    puntos *punt17=new puntos(569,50);
    scena->addItem(punt17);
    puntos *punt18=new puntos(614,50);
    scena->addItem(punt18);
    puntos *punt19=new puntos(655,50);
    scena->addItem(punt19);
    puntos *punt20=new puntos(655,97);
    scena->addItem(punt20);
    puntos *punt21=new puntos(655,144);
    scena->addItem(punt21);
    puntos *punt22=new puntos(655,191);
    scena->addItem(punt22);
    puntos *punt23=new puntos(615,191);
    scena->addItem(punt23);
    puntos *punt24=new puntos(575,191);
    scena->addItem(punt24);
    puntos *punt25=new puntos(535,165);
    scena->addItem(punt25);
    puntos *punt26=new puntos(615,130);
    scena->addItem(punt26);
    puntos *punt27=new puntos(575,130);
    scena->addItem(punt27);
    puntos *punt28=new puntos(535,90);
    scena->addItem(punt28);
    puntos *punt29=new puntos(535,130);
    scena->addItem(punt29);
    puntos *punt30=new puntos(485,130);
    scena->addItem(punt30);
    puntos *punt31=new puntos(435,130);
    scena->addItem(punt31);
    puntos *punt32=new puntos(70,130);
    scena->addItem(punt32);
    puntos *punt33=new puntos(110,130);
    scena->addItem(punt33);
    puntos *punt34=new puntos(150,130);
    scena->addItem(punt34);
    puntos *punt35=new puntos(190,130);
    scena->addItem(punt35);
    puntos *punt36=new puntos(230,130);
    scena->addItem(punt36);
    puntos *punt37=new puntos(270,130);
    scena->addItem(punt37);
    puntos *punt38=new puntos(40,97);
    scena->addItem(punt38);
    puntos *punt39=new puntos(40,144);
    scena->addItem(punt39);
    puntos *punt40=new puntos(40,191);
    scena->addItem(punt40);
    puntos *punt41=new puntos(165,90);
    scena->addItem(punt41);
    puntos *punt42=new puntos(81,191);
    scena->addItem(punt42);
    puntos *punt43=new puntos(122,191);
    scena->addItem(punt43);
    puntos *punt44=new puntos(165,165);
    scena->addItem(punt44);
    puntos *punt45=new puntos(165,210);
    scena->addItem(punt45);
    puntos *punt46=new puntos(165,265);
    scena->addItem(punt46);
    puntos *punt47=new puntos(165,310);
    scena->addItem(punt47);
    puntos *punt48=new puntos(165,355);
    scena->addItem(punt48);
    puntos *punt49=new puntos(165,400);
    scena->addItem(punt49);
    puntos *punt50=new puntos(165,445);
    scena->addItem(punt50);
    puntos *punt51=new puntos(165,490);
    scena->addItem(punt51);
    puntos *punt52=new puntos(165,540);
    scena->addItem(punt52);
    puntos *punt53=new puntos(165,590);
    scena->addItem(punt53);
    puntos *punt54=new puntos(165,265);
    scena->addItem(punt54);
    puntos *punt55=new puntos(535,310);
    scena->addItem(punt55);
    puntos *punt56=new puntos(535,355);
    scena->addItem(punt56);
    puntos *punt57=new puntos(535,400);
    scena->addItem(punt57);
    puntos *punt58=new puntos(535,445);
    scena->addItem(punt58);
    puntos *punt59=new puntos(535,490);
    scena->addItem(punt59);
    puntos *punt60=new puntos(535,540);
    scena->addItem(punt60);
    puntos *punt61=new puntos(535,590);
    scena->addItem(punt61);
    puntos *punt62=new puntos(535,265);
    scena->addItem(punt62);
    puntos *punt63=new puntos(535,210);
    scena->addItem(punt63);
    puntos *punt64=new puntos(40,655);
    scena->addItem(punt64);
    puntos *punt65=new puntos(85,655);
    scena->addItem(punt65);
    puntos *punt66=new puntos(125,655);
    scena->addItem(punt66);
    puntos *punt67=new puntos(165,655);
    scena->addItem(punt67);
    puntos *punt68=new puntos(205,655);
    scena->addItem(punt68);
    puntos *punt69=new puntos(245,655);
    scena->addItem(punt69);
    puntos *punt70=new puntos(285,655);
    scena->addItem(punt70);
    puntos *punt71=new puntos(325,655);
    scena->addItem(punt71);
    puntos *punt72=new puntos(370,655);
    scena->addItem(punt72);
    puntos *punt73=new puntos(410,655);
    scena->addItem(punt73);
    puntos *punt74=new puntos(450,655);
    scena->addItem(punt74);
    puntos *punt75=new puntos(490,655);
    scena->addItem(punt75);
    puntos *punt76=new puntos(530,655);
    scena->addItem(punt76);
    puntos *punt77=new puntos(570,655);
    scena->addItem(punt77);
    puntos *punt78=new puntos(610,655);
    scena->addItem(punt78);   
    puntos *punt79=new puntos(655,655);
    scena->addItem(punt79);
    puntos *punt80=new puntos(40,595);
    scena->addItem(punt80);
    puntos *punt81=new puntos(80,595);
    scena->addItem(punt81);
    puntos *punt82=new puntos(120,595);
    scena->addItem(punt82);
    puntos *punt83=new puntos(575,595);
    scena->addItem(punt83);
    puntos *punt84=new puntos(615,595);
    scena->addItem(punt84);
    puntos *punt85=new puntos(655,595);
    scena->addItem(punt85);    
    puntos *punt86=new puntos(400,530);
    scena->addItem(punt86);
    puntos *punt87=new puntos(445,530);
    scena->addItem(punt87);
    puntos *punt88=new puntos(490,530);
    scena->addItem(punt88);
    puntos *punt89=new puntos(300,530);
    scena->addItem(punt89);
    puntos *punt90=new puntos(255,530);
    scena->addItem(punt90);
    puntos *punt91=new puntos(210,530);
    scena->addItem(punt91);
    puntos *punt92=new puntos(240,560);
    scena->addItem(punt92);
    puntos *punt93=new puntos(240,595);
    scena->addItem(punt93);
    puntos *punt94=new puntos(275,595);
    scena->addItem(punt94);
    puntos *punt95=new puntos(310,595);
    scena->addItem(punt95);
    puntos *punt96=new puntos(310,625);
    scena->addItem(punt96);
    puntos *punt97=new puntos(460,595);
    scena->addItem(punt97);
    puntos *punt98=new puntos(390,595);
    scena->addItem(punt98);
    puntos *punt99=new puntos(425,595);
    scena->addItem(punt99);
    puntos *punt100=new puntos(390,625);
    scena->addItem(punt100);
    puntos *punt101=new puntos(460,560);
    scena->addItem(punt101);
    puntos *punt102=new puntos(40,465);
    scena->addItem(punt102);
    puntos *punt103=new puntos(80,465);
    scena->addItem(punt103);
    puntos *punt104=new puntos(120,465);
    scena->addItem(punt104);
    puntos *punt105=new puntos(575,465);
    scena->addItem(punt105);
    puntos *punt106=new puntos(615,465);
    scena->addItem(punt106);
    puntos *punt107=new puntos(655,465);
    scena->addItem(punt107);
    puntos *punt108=new puntos(610,525);
    scena->addItem(punt108);
    puntos *punt109=new puntos(655,525);
    scena->addItem(punt109);
    puntos *punt110=new puntos(40,525);
    scena->addItem(punt110);
    puntos *punt111=new puntos(85,525);
    scena->addItem(punt111);
    puntos *punt112=new puntos(300,460);
    scena->addItem(punt112);
    puntos *punt113=new puntos(255,460);
    scena->addItem(punt113);
    puntos *punt114=new puntos(210,460);
    scena->addItem(punt114);
    puntos *punt115=new puntos(400,460);
    scena->addItem(punt115);
    puntos *punt116=new puntos(445,460);
    scena->addItem(punt116);
    puntos *punt117=new puntos(490,460);
    scena->addItem(punt117);
    puntos *punt118=new puntos(660,330);
    scena->addItem(punt118);
    puntos *punt119=new puntos(620,330);
    scena->addItem(punt119);
    puntos *punt120=new puntos(580,330);
    scena->addItem(punt120);
    puntos *punt121=new puntos(495,330);
    scena->addItem(punt121);
    puntos *punt122=new puntos(460,355);
    scena->addItem(punt122);
    puntos *punt123=new puntos(40,330);
    scena->addItem(punt123);
    puntos *punt124=new puntos(80,330);
    scena->addItem(punt124);
    puntos *punt125=new puntos(120,330);
    scena->addItem(punt125);
    puntos *punt126=new puntos(205,330);
    scena->addItem(punt126);
    puntos *punt127=new puntos(240,355);
    scena->addItem(punt127);
    puntos *punt128=new puntos(370,395);
    scena->addItem(punt128);
    puntos *punt129=new puntos(410,395);
    scena->addItem(punt129);
    puntos *punt130=new puntos(325,395);
    scena->addItem(punt130);
    puntos *punt131=new puntos(285,395);
    scena->addItem(punt131);
    puntos *punt132=new puntos(460,395);
    scena->addItem(punt132);
    puntos *punt133=new puntos(240,395);
    scena->addItem(punt133);
    puntos *punt134=new puntos(240,200);
    scena->addItem(punt134);
    puntos *punt135=new puntos(275,200);
    scena->addItem(punt135);
    puntos *punt136=new puntos(310,200);
    scena->addItem(punt136);
    puntos *punt137=new puntos(385,200);
    scena->addItem(punt137);
    puntos *punt138=new puntos(420,200);
    scena->addItem(punt138);
    puntos *punt139=new puntos(455,200);
    scena->addItem(punt139);
    puntos *punt140=new puntos(370,260);
    scena->addItem(punt140);
    puntos *punt141=new puntos(410,260);
    scena->addItem(punt141);
    puntos *punt142=new puntos(325,260);
    scena->addItem(punt142);
    puntos *punt143=new puntos(285,260);
    scena->addItem(punt143);
    puntos *punt144=new puntos(460,260);
    scena->addItem(punt144);
    puntos *punt145=new puntos(240,260);
    scena->addItem(punt145);
    puntos *punt146=new puntos(240,300);
    scena->addItem(punt146);
    puntos *punt147=new puntos(460,300);
    scena->addItem(punt147);
}
MainWindow::~MainWindow()
{
    delete ui;
}
