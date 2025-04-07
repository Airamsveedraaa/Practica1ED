#include "Clasificacion.h"
#include "Comun.h"
#include <iostream>
using namespace std;

Clasificacion::Clasificacion()
{

    tamano=0; //tama�o inicial
    elementos=new Jugador[tamano]; //no tiene memoria de primeras
    Jugadores=0;

}


void Clasificacion::anadirjugador(Jugador j)
{

        /*El método anadirjugador añade la estructura Jugador pasada como parámetro a la tabla de
elementos del objeto Clasificación. Si dicha tabla estuviera llena habrá que redimensionar la
tabla a un tamaño igual al anterior + SALTO (siendo SALTO una constante definida en el
programa, con valor de 4, con el propósito de no tener que redimensionar la tabla con cada
inserción, sino cada “SALTO” inserciones). */

    if(elementos==nullptr){
        cout << "Error,anadirjugador()" << endl;
    }


    if(Jugadores==tamano)
    {
        tamano+=SALTO;
        Jugador *nuevoVector=new Jugador[tamano]; //creamos memoria para el nuevo vector
        for(int i=0; i<Jugadores; i++)
        {
            nuevoVector[i]=elementos[i];
        }
        delete [] elementos;
        elementos=nuevoVector;
    }

    elementos[Jugadores]=j;
    Jugadores++;

}

void Clasificacion::eliminar(int i)
{

    /*El método eliminar, eliminará de la tabla dinámica el Jugador que ocupe la posición i, pasada
como parámetro, en la tabla. */

      if (elementos==nullptr){
        cout<<"Error en eliminar clasificacion"<<endl;
    }


    if(i < 0 || i>Jugadores)
    {
        cout << "Error, posicion invalida" << endl;
    }
    for(int j=i; j<Jugadores; j++)
    {
        elementos[j]=elementos[j+1]; //pasamos datos de una posicion a la anterior a partir de la posicion dada para mantener el orden
    }
    Jugadores--; //actualizar numero de jugadores


}

Jugador Clasificacion::consultar(int n)
{
    /*El método consultar permite obtener el Jugador que se encuentre en la tabla dinámica en la
posición pasada. */



    if(n<0 || n> Jugadores)
    {
        cout << "Error, posicion invalida" << endl;
    }

    else
    {
        return elementos[n];
    }

}


bool Clasificacion::vacio()
{

    /*El método vacio devuelve verdadero si la tabla dinámica elementos está vacía o falso en caso
contrario.*/


    bool Vacio;
    if(Jugadores==0)
        Vacio=true;
    else
        Vacio=false;

    return Vacio;

}

int Clasificacion::numjugadores()
{


    return Jugadores;

}

void Clasificacion::ordenar()
{

    /*El método ordenar ordena la tabla dinámica elementos por el algoritmo burbuja. */

     if (elementos==nullptr){
        cout<<"Error en ordenar clasificacion"<<endl;
    }


    for(int i=0; i<Jugadores-1; i++)
    {
        for(int j=0; j<Jugadores-i-1; j++)
        {
            if (elementos[j].resultado > elementos[j+1].resultado)
            {
                Jugador temporal=elementos[j];
                elementos[j]=elementos[j+1];
                elementos[j+1]=temporal;
            }
        }
    }
}

Clasificacion::~Clasificacion(){

delete [] elementos;


}
