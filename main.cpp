#include "Torneo.h"
#include "Clasificacion.h"
#include <iostream>

using namespace std;
struct TorneoAux
{
    int nG;
    cadena nTorneo;
    cadena Nfichero;
};

int main()
{
    int opc;
    int nT = 0;
    Torneo t[N];
    TorneoAux r;
    cadena nombreTorneo, nombreFichero;

    fstream f("Torneos.dat", ios::binary | ios::in | ios::out);
    if (f.fail())
    {
        f.clear();
        f.close();
        f.open("Torneos.dat", ios::binary | ios::out);
        f.close();
        f.open("Torneos.dat", ios::binary | ios::in | ios::out);
    }
    else
    {
        f.seekg(0,ios::beg);

        f.read((char*)&r, sizeof(TorneoAux));
        while (!f.eof())
        {
            t[nT].crearFichero(r.Nfichero);
            t[nT].putNumGolfistas(r.nG);
            t[nT].putNomFichero(r.Nfichero);
            t[nT].putNomTorneo(r.nTorneo);
            nT++;
            f.read((char*)&r, sizeof(TorneoAux));
        }


        if(f.fail())
            f.clear();
    }
    f.close();
    do
    {
        cout << "CLUB DE GOLF" << "\n" ;
        cout << "-------------------------------" << endl;
        cout << "Torneos: " << nT
             << "\n" << "\n1.-Listado Torneos Abiertos"
             << "\n2.-Alta Torneo"
             << "\n3.-Elegir Torneo"
             << "\n4.-Salir"
             << "\nIndique la opcion deseada: " << endl;
        cin >> opc;
        system("cls");
        switch(opc)
        {

        case 1:
            if(nT==0)
            {
                cout << "Actualmente no hay torneos abiertos a inscripciones" << endl;
            }
            else
            {
                cout << "Torneos abiertos a inscripcion :"<< endl;
                for (int i = 0; i < nT; i++)
                {
                    t[i].getNomTorneo(nombreTorneo);
                    t[i].getNomFichero(nombreFichero);
                    cout << "Torneo " << i + 1 << ":" << endl;
                    cout << "  Nombre: " << nombreTorneo << endl;
                    cout << "  Fichero: " << nombreFichero << endl;
                    cout << "  Numero de golfistas: " << t[i].getNumGolfistas() << endl;
                }

            }

            break;

        case 2:

            if(nT>=N)
            {
                cout << "No se pueden crear mas torneos" << endl;
            }
            else
            {
                f.open("Torneos.dat", ios::binary | ios::in | ios::out);
                cout << "Introduzca el fichero que almacenara la informacion: " << endl;
                cin >> r.Nfichero;

                cout << "Introduzca el nombre del torneo a dar de alta: " << endl;
                cin >> r.nTorneo;

                t[nT].crearFichero(r.Nfichero);
                t[nT].putNomTorneo(r.nTorneo);

                r.nG = t[nT].getNumGolfistas();

                f.seekp(0,ios::end);
                f.write((char*)&r,sizeof(TorneoAux));
                nT++;
                f.close();
                cout << "INFORMACION DEL CLUB ACTUALIZADA: " << endl;
                cout << "Torneos:" << nT << endl;
                for (int i = 0; i < nT; i++)
                {
                    t[i].getNomTorneo(nombreTorneo);
                    t[i].getNomFichero(nombreFichero);
                    cout << "Torneo " << i + 1 << ":" << endl;
                    cout << "  Nombre: " << nombreTorneo << endl;
                    cout << "  Fichero: " << nombreFichero << endl;
                    cout << "  Numero de golfistas: " << t[i].getNumGolfistas() << endl;
                }
                break;

            case 3:

                if(nT==0)
                {
                    cout << "No hay torneos para mostrar" << endl;
                }
                else
                {
                    cout << "TORNEOS: " << endl;
                    for(int i=0; i<nT; i++)
                    {
                        t[i].getNomTorneo(nombreTorneo);
                        cout << i+1 << "." << nombreTorneo << endl;
                    }
                    int OpcTorneo,OpcMenuTorneo;
                    do
                    {
                        cout << "Elija torneo: " << endl;
                        cin >> OpcTorneo;
                    }
                    while (OpcTorneo <1 || OpcTorneo > nT);

                    do
                    {
                        t[OpcTorneo-1].getNomTorneo(nombreTorneo);
                        cout << "Torneo " << nombreTorneo << endl;
                        cout << "--------------------------------"
                             << "\n" << "golfistas: " << t[OpcTorneo-1].getNumGolfistas()
                             << "\n\n1.Consulta de inscripciones "
                             << "\n2.Inscripcion al torneo "
                             << "\n3.Busqueda de una inscripcion"
                             << "\n4.Modificar datos de una inscripcion"
                             << "\n5.Eliminar una inscripcion"
                             << "\n6.Mostrar Resultados del Torneo"
                             << "\n7.Salir"
                             << "\n\nIndique la opcion deseada: " << endl;
                        cin >> OpcMenuTorneo;
                        system("cls");
                        switch(OpcMenuTorneo)
                        {

                        case 1:
                            float handicap;
                            cout << "Introduzca el handicap de los golfistas a mostrar (-1 si quiere ver todos los golfistas) : " << endl;
                            cin >> handicap;
                            t[OpcTorneo-1].mostrar(handicap);
                            break;

                        case 2:
                            cadena nombre,apellidos,licencia;
                            Golfista golfista1;
                            cout << "Datos del golfista: " << endl;
                            cout << "Licencia: " << endl;
                            cin >> golfista1.licencia;
                            cout << "Handicap: " << endl;
                            cin >> golfista1.handicap;
                            cin.ignore();
                            cout << "Nombre: " << endl;
                            cin.getline(golfista1.nombre,30);
                            cout << "Apellidos: " << endl;
                            cin.ignore();
                            cin.getline(golfista1.apellidos,30);
                            golfista1.golpes=0;
                            golfista1.resultado=0; //golpes y resultado inicialmente en 0
                            t[OpcTorneo-1].insertar(golfista1);
                        }
                    }
                    while(OpcMenuTorneo !=7);
                }

                break;

            case 4:
                cout << "Saliendo del menu..." << endl;
                break;

            default:
                break;

            }
        }
    }
    while(opc!=4);
    f.close();

    return 0;
}
