#ifndef MUROS_H
#define MUROS_H


#include <map>
#include <stdlib.h>
#include <string.h>
using namespace std;


class muros
{
private:

public:
    muros();
    map<string,int> muro;
    map<string,int> :: iterator it2;
    void AgregarMuro(string,int);
};
#endif // MUROS_H
