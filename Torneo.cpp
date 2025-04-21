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

    /*El método crearFichero del objeto Torneo será el método en el que se debe crear el fichero
    para comenzar a inscribir jugadores o abrir el fichero ya creado para seguir inscribiendo
    jugadores o gestionar las inscripciones (mostrarlas, modificarlas, eliminarles), así como
    simular la celebración del torneo y mostrar los resultados del torneo. Si el fichero
    nombrefichero no existe se procede a crear el fichero vacío (asignando y guardando el valor
    de 0 para el número de Golfistas). Si el fichero existe se abre para poder gestionarlo. */



    strcpy(nomFichero,nombreFichero);

    fichero.open(nombreFichero, ios::binary | ios::in | ios::out);
    if(fichero.fail())
    {
        fichero.clear();
        fichero.close(); //quitar estatus de error y cerrar fichero
        fichero.open(nombreFichero, ios::binary | ios::out );
        fichero.close(); //abrirlo en modo escritura para forzar creacion del fichero
        fichero.open(nombreFichero, ios::binary | ios::in | ios::out); //abrirlo normal para usarlo en el programa
        numGolfistas=0;
        fichero.seekp(0, ios::beg);
        fichero.write((char*)&numGolfistas, sizeof(int));
    }
    else
    {
        fichero.seekg(0, ios::beg);
        fichero.read((char*)&numGolfistas,sizeof(int));
    }


    if(fichero.fail())
        cout<<"Error fichero.fail() crearFichero "<<nombreFichero<<endl;
}


void Torneo::mostrar(float hdcp)
{

    /*El método mostrar se encarga de mostrar por pantalla los datos de todas las inscripciones de
    un determinado torneo que tengan el mismo hándicap pasado por parámetro. Si el valor pasado
    es -1 se mostrará por pantalla la información de todos los golfistas del fichero*/


    if(numGolfistas==0)
    {
        cout << "No hay golfistas para mostrar" << endl;
    }

    if(fichero.fail())
    {

        cout << "Error fichero.fail() mostrar" << endl;
    }

    else
    {
        Golfista g;
        fichero.seekg(sizeof(int),ios::beg);
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

    /*El método consultar devuelve el golfista cuya posición se pasa por parámetro. La posición
    del primer golfista en el fichero es la 1. */


    if(fichero.fail())
    {

        cout << "Error fichero.fail() consultar" << endl;
    }
    Golfista g;


    if(!fichero.fail())
    {
        fichero.seekg(sizeof(int) +(posicion-1)*sizeof(Golfista),ios::beg); //posicionamos para leer en la posicion pasada por parametro
        fichero.read((char*)&g,sizeof(Golfista));
    }

    return g;
}

int Torneo::buscar(cadena licencia)
{


    /*El método buscar devuelve la posición en el fichero del golfista cuya licencia se pasa como
    parámetro, si se encuentra, y en caso contrario devuelve el valor -1, para indicar que no existe
    ningún golfista con esa licencia en el fichero*/


    if(fichero.fail())
    {

        cout << "Error fichero.fail() buscar" << endl;
    }

    else
    {
        Golfista g;
        bool encontrado=false;
        int i=0;
        int pos=-1;
        fichero.seekg(sizeof(int),ios::beg); //posicionamos justo en el primer golfista
        while(i<numGolfistas && !encontrado)
        {
            fichero.read((char*)&g,sizeof(Golfista));
            i++;
            if(strcmp(g.licencia,licencia)==0)
            {
                pos=i;
                encontrado=true;
            }

        }
        return pos;

    }
}

void Torneo::insertar(Golfista g)
{


    /*El método insertar realiza la inserción de los datos de un nuevo golfista, teniendo en cuenta
    que los golfistas deben continuar en el fichero ordenados por hándicap, de menor a mayor.
    Habrá que controlar que no se insertan golfistas con la misma licencia de los ya inscritos en
    un mismo torneo.*/


    if(fichero.fail())
    {
        cout << "Error fichero.fail() insertar" << endl;
    }
    else
    {
        if(buscar(g.licencia)!=-1)
        {
            cout << "Golfista ya existente" << endl;
        }
        //Ordenar golfistas por handicap
        else
        {
            Golfista aux;
            int pos = 0;
            bool insertado = false;
            // Buscar posición correcta
            fichero.seekg(sizeof(int), ios::beg);
            while(pos < numGolfistas && !insertado)
            {
                fichero.read((char*)&aux, sizeof(Golfista));
                if(g.handicap < aux.handicap)
                {
                    insertado = true;
                }
                else
                {
                    pos++;
                }
            }

            // Desplazar elementos desde la posición encontrada
            for(int i = numGolfistas; i > pos; i--)
            {
                Golfista temp = consultar(i); // golfista en posición i-1
                fichero.seekp(sizeof(int) + i * sizeof(Golfista), ios::beg);
                fichero.write((char*)&temp, sizeof(Golfista));
            }

            // Insertar nuevo golfista
            fichero.seekp(sizeof(int) + pos * sizeof(Golfista), ios::beg);
            fichero.write((char*)&g, sizeof(Golfista));
            numGolfistas++;
            fichero.seekp(0,ios::beg);
            fichero.write((char*)&numGolfistas,sizeof(int));
            cout<<"\nGolfista insertado con exito\n"<<endl;



        }
        cout << "Golfista insertado" << endl;
        cout << "Licencia: " << g.licencia << endl;
        cout << "Nombre: " << g.nombre << endl;
        cout << "Apellidos: " << g.apellidos << endl;
    }
}

void Torneo::modificar(Golfista c, int posicion)
{

    /*El método modificar se encarga de actualizar los datos de un golfista ya inscrito. Se pasarán
    los nuevos datos del golfista y la posición donde se encuentra. Si el golfista pasado no
    estuviera inscrito en el torneo, se mostraría un mensaje indicándolo. Nota: No se admite en
    la modificación cambiar el hándicap del golfista.*/


    if(fichero.fail())
    {
        cout << "Error en el fichero. modificar()" << endl;

    }

    else if(posicion>numGolfistas || posicion<1)
    {
        cout << "El golfista no esta inscrito en el torneo" << endl;
    }

    else
    {

        fichero.seekp(sizeof(int)+ (posicion-1)*sizeof(Golfista),ios::beg);
        fichero.write((char*)&c, sizeof(Golfista));
    }
}

void Torneo::eliminar(int posicion)
{

    /*El método eliminar realiza la eliminación de los datos del golfista cuya posición se pasa por
    parámetro. Si la posición no existe, se mostraría un mensaje de error. Para eliminar una
    inscripción de un golfista del fichero, se desplazan una posición a la izquierda todas las
    inscripciones a continuación de la eliminada (para no dejar huecos).*/


    if(fichero.fail())
    {
        cout << "Error fichero.fail() eliminar" << endl;
    }

    else
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
        }
        else
        {
            cout << "Golfista a eliminar no encontrado" << endl;
        }
    }
}

/* El método Clasificar se encarga de realizar una simulación de la celebración del torneo
    con los golfistas que se han inscrito. Su detalle se explica más adelante. Este método simulará
    la celebración del torneo y mostrará por pantalla la clasificación final con los datos de los
    golfistas, junto con el número de golpes y los resultados obtenidos.*/
void Torneo:: Clasificar(){
    if(fichero.fail()){
        cout<<"Error en fichero.clasificar()"<<endl;
    }
    fichero.clear();
    fichero.seekp(0,ios::beg);
    fichero.read((char*)&numGolfistas, sizeof(int));
    if (numGolfistas==0){
        cout<<"No hay golfistas inscritos"<<endl;
    }
    srand(time(0));

    Clasificacion clasif;

    cout<<"Resultados del torneo: "<<nomTorneo<<endl;
    cout << "Puesto\tNombre\tApellidos\tHandicap\tGolpes\tResultado"<<endl;
    cout<<"----------------------------------------------------------------------"<<endl;

    for(int i=0; i<numGolfistas; i++){
        Golfista g;
        fichero.seekp(sizeof(int) +i*sizeof(Golfista), ios::beg);
        fichero.read((char*)&g, sizeof(Golfista));

        g.golpes=50+rand()%51;
        g.resultado=g.golpes-PAR;
        //Golfista
        fichero.seekp(sizeof(int) +i*sizeof(Golfista), ios::beg);
        fichero.write((char*)&g, sizeof(Golfista));
        //Clasificacion
        Jugador j;
        j.indice=i;
        j.resultado=g.resultado;
        clasif.anadirjugador(j); //de clase clasificacion
    }

    clasif.ordenar();

    for (int i=0; i<clasif.numjugadores(); i++){
        Jugador j=clasif.consultar(i);
        Golfista g;
        fichero.seekp(sizeof(int) +j.indice*sizeof(Golfista), ios::beg);
        fichero.read((char*)&g, sizeof(Golfista));
        cout<<i+1<<"\t";
        cout<<g.nombre<<"\t";
        cout<<g.apellidos<<"\t\t";
        cout<<g.handicap<<"\t\t";
        cout<<g.golpes<<"\t";
        cout<<g.resultado<<endl;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
}

Torneo::~Torneo()
{
    fichero.close();
}

