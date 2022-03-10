#include "muros.h"
using namespace std;
muros::muros()
{

}

void muros::AgregarMuro(string dimension, int valor) //ir agg los muros al mapa
{
    muro[dimension]=valor;
}
