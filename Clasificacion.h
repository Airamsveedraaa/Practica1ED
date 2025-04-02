#ifndef CLASIFICACION_H_INCLUDED
#define CLASIFICACION_H_INCLUDED

//Definicion estructura Jugador
struct Jugador
{
    int indice;
    int resultado;
};


//Declaracion clase Clasificacion
class Clasificacion
{
    Jugador *elementos; //puntero a objeto tipo jugador, seran almacenados como un vector
    int Jugadores;      //Numero de jugadores efectivos
    int tamano;         //tamaño del vector que contiene a los jugadores
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
