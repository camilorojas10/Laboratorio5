#include "mapa.h"

mapa::mapa()
{

}

void mapa::leerArchivo()
{
    muros muro;
    string Nmuro,linea,aux="",letra;
    int cont=0,num=0,ancho,alto,x,y;
    ifstream textoArch;
    textoArch.open("paredes.txt",ios::in); //Abriendo en modo lectura
    if(textoArch.fail()){
        cout<<"No se pudo abrir el archivo"<<endl;
        exit(1);
    }
     while(!textoArch.eof()){//Mientras no sea el final del archivo
         getline(textoArch,linea);
         for(int i=0;i<linea.length();i++){
             letra=linea[i];
             if(letra!=" ") aux.append(letra);
             else{
                  switch(cont){

                      case 0:Nmuro=aux; break;
                      case 1:ancho=atoi(aux.c_str());break;
                      case 2:alto=atoi(aux.c_str());break;
                      case 3:x=atoi(aux.c_str());break;
                      case 4:y=atoi(aux.c_str());break;
                  }
                  cont+=1;aux="";
             }

         }
         muro.AgregarMuro("ancho",ancho);
         muro.AgregarMuro("alto",alto);
         muro.AgregarMuro("x",x);
         muro.AgregarMuro("y",y);

         mundo.insert(pair<string,muros>(Nmuro,muro));
         cont=0;
         num+=1;
     }

}

int mapa::longitudMundo()
{
    int cont=0;
    for(it=mundo.begin();it!=mundo.end();it++){
        cont+=1;
    }
}
