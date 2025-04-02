#ifndef CLASIFICACION_H_INCLUDED
#define CLASIFICACION_H_INCLUDED
#include "comun.h"

//Declaracion estructura Jugador
struct Jugador
{
    int indice;
    int resultado;
};


//Declaracion clase clasificacion
class Clasificacion
{

    Jugador *elementos; //puntero a estructura, lo almacenaremos en forma de vector
    int Jugadores; //Numero de jugadores efectivos
    int tamano; //Tamaño del vector que contiene a los jugadores

public:

    Clasificacion();
    void anadirjugador(Jugador j);
    void eliminar(int i);
    Jugador consultar(int n);
    bool vacio();
    int numjugadores();
    void ordenar();
    ~Clasificacion();

};

#endif // CLASIFICACION_H_INCLUDED
