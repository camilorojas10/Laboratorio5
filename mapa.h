#ifndef MAPA_H
#define MAPA_H

#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
#include "pared.h"
#include "muros.h"
using namespace std;

class mapa
{
private:
    map<string,muros> mundo;
    map<string,muros> :: iterator it;
public:
    mapa();
    void leerArchivo();
    int longitudMundo();
};

#endif // MAPA_H
