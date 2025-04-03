#include "Torneo.h"
#include "Clasificacion.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
Torneo::Torneo()
{
    fstream fichero;
    numGolfistas=0;
    strcpy(nomFichero,"");
    strcpy(nomTorneo,"");

}

int Torneo::getNumGolfistas()
{

    return numGolfistas;

}

void Torneo::putNumGolfistas(int n)
{

    numGolfistas=n;

}

void Torneo::getNomTorneo(cadena nombre)
{

    strcpy(nombre,nomTorneo);

}

void Torneo::getNomFichero(cadena nombre)
{

    strcpy(nombre,nomFichero);

}

void Torneo::putNomTorneo(cadena nombre)
{

    strcpy(nomTorneo,nombre);

}

void Torneo::putNomFichero(cadena nombre)
{


    strcpy(nomFichero,nombre);

}

void Torneo::crearFichero(char nombreFichero[])
{

    fichero.open(nombreFichero, ios::binary | ios::in | ios::out );
    if(fichero.fail())
    {
        fichero.clear();
        fichero.close(); //quitar estatus de error y cerrar fichero
        fichero.open(nombreFichero, ios::binary | ios::out );
        fichero.close(); //abrirlo en modo escritura para forzar creacion del fichero
        fichero.open(nombreFichero, ios::binary | ios::in | ios::out); //abrirlo normal para usarlo en el programa
        numGolfistas=0;
        fichero.write((char*)&numGolfistas,sizeof(int));
    }
    else
    {
        fichero.read((char*)&numGolfistas,sizeof(int));
    }
    strcpy(nomFichero,nombreFichero);
}


void Torneo::mostrar(float hdcp)
{
    Golfista g;
    fichero.seekg(sizeof(int),ios::beg);
    if(numGolfistas==0)
    {
        cout << "No hay golfistas para mostrar" << endl;
    }
    else
    {
        if(hdcp!=-1)
        {
            fichero.seekg(0,ios::beg);
            fichero.read((char*)&numGolfistas,sizeof(int));
            cout << "Numero de golfistas inscritos: " << numGolfistas << endl;
            fichero.seekg(sizeof(int),ios::beg);
            cout << "Mostrando golfistas con handicap: " << hdcp << endl;
            for(int i=0; i<numGolfistas; i++)
            {
                fichero.read((char*)&g,sizeof(Golfista));
                if(g.handicap==hdcp)
                {
                    cout << "Golfista " << i + 1 << ":" << endl;
                    cout << "\n  Licencia: " << g.licencia << endl;
                    cout << "\n  Handicap: " << g.handicap << endl;
                    cout << "\n  Nombre: " << g.nombre << endl;
                    cout << "\n  Apellidos: " << g.apellidos << endl;
                    cout << "\n  Golpes: " << g.golpes << endl;
                    cout << "\n  Resultado: " << g.resultado << endl;
                }
            }
        }
        else
        {
            fichero.seekg(0,ios::beg);
            fichero.read((char*)&numGolfistas,sizeof(int));
            cout << "Numero de golfistas: " << numGolfistas << endl;
            fichero.seekg(sizeof(int),ios::beg);
            for(int i=0; i<numGolfistas; i++)
            {
                fichero.read((char*)&g,sizeof(Golfista));
                cout << "Golfista " << i + 1 << ":" << endl;
                cout << "  Licencia: " << g.licencia << endl;
                cout << "  Handicap: " << g.handicap << endl;
                cout << "  Nombre: " << g.nombre << endl;
                cout << "  Apellidos: " << g.apellidos << endl;
                cout << "  Golpes: " << g.golpes << endl;
                cout << "  Resultado: " << g.resultado << endl;
            }
        }

    }
}


Golfista Torneo::consultar(int posicion)
{

    Golfista g;
    fichero.seekg(0,ios::beg); //posicionado al inicio
    int pos=sizeof(int) + (posicion-1)*sizeof(Golfista); //posicion que queremos buscar
    fichero.seekg(pos,ios::beg); //posicion buscada para leer
    fichero.read((char*)&g,sizeof(Golfista)); //lectura golfista buscado
    cout << "Datos del golfista ubicado en la posicion " << posicion << " :" << endl;
    cout << "  Licencia: " << g.licencia << endl;
    cout << "  Handicap: " << g.handicap << endl;
    cout << "  Nombre: " << g.nombre << endl;
    cout << "  Apellidos: " << g.apellidos << endl;
    cout << "  Golpes: " << g.golpes << endl;
    cout << "  Resultado: " << g.resultado << endl;
}

int Torneo::buscar(cadena licencia)
{
    Golfista g;
    bool encontrado=false;
    int i=0;
    int pos=-1;
    fichero.seekg(sizeof(int),ios::beg); //posicionamos justo en el primer golfista
    while(i<numGolfistas && !encontrado)
    {
        fichero.read((char*)&g,sizeof(Golfista));
        if(strcmp(g.licencia,licencia)==0)
        {
            pos=i+1;
            encontrado=true;
        }
        else
            i++;

    }
    return pos;

}

void Torneo::insertar(Golfista g)
{

    cout << "Datos del golfista: " << endl;
    cout << "Licencia: " << endl;
    cin >> g.licencia;
    cout << "Handicap: " << endl;
    cin >> g.handicap;
    cout << "Nombre: " << endl;
    cin >> g.nombre;
    cout << "Apellidos: " << endl;
    cin >> g.apellidos;

    fichero.seekp(sizeof(int)+numGolfistas*sizeof(Golfista),ios::beg);
    fichero.write((char*)&g,sizeof(Golfista));
    numGolfistas++;
    fichero.seekp(0,ios::beg);
    fichero.write((char*)&numGolfistas,sizeof(int));
    cout << "Golfista insertado" << endl;
}

void Torneo::modificar(Golfista c, int posicion)
{
    if(posicion > 0 && posicion < numGolfistas) //quiere decir que se encuentra al golfista
    {
        Golfista golfistaexistente;
        fichero.seekg(sizeof(int) + posicion * sizeof(Golfista),ios::beg); //me desplazo desde el inicio hacia la posicion que quiero modificar??
        fichero.read((char*)&golfistaexistente,sizeof(Golfista));
        cout << "Licencia: " << endl;
        cin >> golfistaexistente.licencia;
        cout << "Nombre: " << endl;
        cin >> golfistaexistente.nombre;
        cout << "Apellidos: " << endl;
        cin >> golfistaexistente.apellidos;     //escribo informacion en esa posicion para modificar los atributos del golfista�?
        fichero.seekp(sizeof(int) + posicion * sizeof(Golfista),ios::beg);
        fichero.write((char*)&golfistaexistente,sizeof(Golfista));
        cout << "Datos del golfista modificados correctamente" << endl;
        cout << "Mostrando datos actualizados: " << endl;
        mostrar(-1);
    }
    else
        cout << "Golfista no encontrado" << endl;

}

void Torneo::eliminar(int posicion)
{
    if (posicion > 0 && posicion <= numGolfistas)
    {
        Golfista golfistaExistente;
        for (int i = posicion; i < numGolfistas; i++)
        {
            fichero.seekg(sizeof(int) + i * sizeof(Golfista), ios::beg);
            fichero.read((char*)&golfistaExistente, sizeof(Golfista));
            fichero.seekp(sizeof(int) + (i - 1) * sizeof(Golfista), ios::beg);
            fichero.write((char*)&golfistaExistente, sizeof(Golfista));
        }
        numGolfistas--; // Actualizar el n�mero de golfistas
        fichero.seekp(0, ios::beg);
        fichero.write((char*)&numGolfistas, sizeof(int));
        cout << "Golfista eliminado con exito" << endl;
        cout << "Mostrando datos actualizados: " << endl;
        mostrar(-1); // Mostrar todos los datos actualizados para comprobar que se ha eliminado correctamente
    }
    else
    {
        cout << "Golfista a eliminar no encontrado" << endl;
    }
}

void Torneo::Clasificar()
{
    if (numGolfistas == 0)
    {
        cout << "No hay golfistas inscritos en el torneo." << endl;
        return;
    }
    srand(time(0)); // Inicializar semilla para n�meros aleatorios

    // 1. Crear vector din�mico de estructuras Jugador
    Jugador* clasificacion = new Jugador[numGolfistas];
    int jugadoresProcesados = 0;

    // 2. Recorrer todos los golfistas del torneo
    fichero.seekg(sizeof(int), ios::beg); // Posicionarse despu�s del contador
    for (int i = 0; i < numGolfistas; i++)
    {
        Golfista g;
        fichero.read((char*)&g, sizeof(Golfista));

        // Simular n�mero de golpes aleatorio (entre 60 y 100)
        g.golpes = 60 + rand() % 41; // rand() % 41 da valores entre 0 y 40 y le sumamos 60 para que vaya desde 60 a 100

        // Calcular resultado (golpes - par del campo)
        g.resultado = g.golpes - PAR;

        // Actualizar el golfista en el fichero con los nuevos datos,sobreescribiendo los campos golpes y resultados con la info nueva
        fichero.seekp(sizeof(int) + i * sizeof(Golfista), ios::beg);
        fichero.write((char*)&g, sizeof(Golfista));

        // Redimensionar el vector si es necesario (en este caso no ser�a necesario
        // porque ya sabemos el tama�o m�ximo (numGolfistas), pero lo implemento
        // como ejemplo de c�mo se har�a si fuera creciendo din�micamente)
        if (jugadoresProcesados >= numGolfistas)
        {
            // Redimensionar (aunque en este caso espec�fico no deber�a ocurrir)
            Jugador* nuevaClasificacion = new Jugador[jugadoresProcesados + 1];
            for (int j = 0; j < jugadoresProcesados; j++)
            {
                nuevaClasificacion[j] = clasificacion[j];
            }
            delete[] clasificacion;
            clasificacion = nuevaClasificacion;
        }

        // A�adir jugador al vector de clasificaci�n
        clasificacion[jugadoresProcesados].indice = i;
        clasificacion[jugadoresProcesados].resultado = g.resultado;
        jugadoresProcesados++;
    }

    // Ordenar la clasificaci�n por resultado (de menor a mayor) - Algoritmo burbuja
    for (int i = 0; i < jugadoresProcesados - 1; i++)
    {
        for (int j = 0; j < jugadoresProcesados - i - 1; j++)
        {
            if (clasificacion[j].resultado > clasificacion[j + 1].resultado)
            {
                // Intercambiar posiciones
                Jugador temp = clasificacion[j];
                clasificacion[j] = clasificacion[j + 1];
                clasificacion[j + 1] = temp;
            }
        }
    }

    // Mostrar la clasificaci�n final
    cout << "\n--- CLASIFICACION FINAL DEL TORNEO " << nomTorneo << " ---" << endl;
    cout << "Pos.\tLicencia\tNombre\tApellidos\tHandicap\tGolpes\tResultado" << endl;

    for (int pos = 0; pos < jugadoresProcesados; pos++)
    {
        // Leer el golfista correspondiente del fichero
        Golfista g;
        fichero.seekg(sizeof(int) + clasificacion[pos].indice * sizeof(Golfista), ios::beg);
        fichero.read((char*)&g, sizeof(Golfista));

        // Mostrar datos del golfista
        cout << pos + 1 << "\t" << g.licencia << "\t" << "\t" << g.nombre << "\t" << g.apellidos << "\t"
             << "\t" << g.handicap << "\t" << "\t" << g.golpes << "\t";

        // Mostrar resultado de forma m�s legible (PAR, +n o -n)
        if (g.resultado == 0)
        {
            cout << "PAR";
        }
        else if (g.resultado > 0)
        {
            cout << "+" << g.resultado;
        }
        else
        {
            cout << g.resultado; // Los negativos ya llevan el signo
        }

        cout << endl;
    }

    //Liberar memoria del vector din�mico
    delete[] clasificacion;
}

Torneo::~Torneo()
{

    fichero.close();

}

