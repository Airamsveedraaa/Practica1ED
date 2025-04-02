#include "Clasificacion.h"
#include "Comun.h"
#include <iostream>
using namespace std;

Clasificacion::Clasificacion()
{

    tamano=0; //tama�o inicial
    elementos=nullptr; //no tiene memoria de primeras
    Jugadores=0;

}


void Clasificacion::anadirjugador(Jugador j)
{

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

    Jugador j;

    if(n<0 || n> Jugadores)
    {
        cout << "Error, posicion invalida" << endl;
    }

    else
    {
        cout << "Datos del jugador " << n << " :" << endl;
        cout << "\n" << j.indice << endl;
        cout << "\n" << j.resultado << endl;
    }

}


bool Clasificacion::vacio()
{

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

    for(int i=0; i<Jugadores; i++)
    {
        for(int j=i+1; j<Jugadores; j++)
        {
            if (elementos[i].resultado > elementos[j].resultado)
            {
                Jugador temporal=elementos[i];
                elementos[i]=elementos[j];
                elementos[j]=temporal;
            }
        }
    }
}
