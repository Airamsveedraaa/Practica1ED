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

    fstream fTorneo("TORNEOS.dat", ios::binary | ios::in);
    fTorneo.seekg(0, ios::beg);
    if(!fTorneo.fail())
    {
        cadena nombre, fichero;
        TorneoAux r;

        fTorneo.read((char*)&r, sizeof(TorneoAux));
        while(!fTorneo.eof())
        {
            t[nT].crearFichero(r.Nfichero);
            t[nT].putNomTorneo(r.nTorneo);
            nT++;

            fTorneo.read((char*)&r, sizeof(TorneoAux));
        }
    }
    else
    {
        fTorneo.close();
        fTorneo.open("TORNEOS.dat", ios::binary | ios::out);
        TorneoAux r;

        t[nT].crearFichero("AUDI.dat");
        t[nT].putNomTorneo("AUDI");
        r.nG = t[nT].getNumGolfistas();
        t[nT].getNomFichero(r.Nfichero);
        t[nT].getNomTorneo(r.nTorneo);
        fTorneo.write((char*)&r, sizeof(TorneoAux));
        nT++;

        t[nT].crearFichero("SONY.dat");
        t[nT].putNomTorneo("SONY");
        r.nG = t[nT].getNumGolfistas();
        t[nT].getNomFichero(r.Nfichero);
        t[nT].getNomTorneo(r.nTorneo);
        fTorneo.write((char*)&r, sizeof(TorneoAux));
        nT++;

        t[nT].crearFichero("IBM.dat");
        t[nT].putNomTorneo("IBM");
        r.nG = t[nT].getNumGolfistas();
        t[nT].getNomFichero(r.Nfichero);
        t[nT].getNomTorneo(r.nTorneo);
        fTorneo.write((char*)&r, sizeof(TorneoAux));
        nT++;


    }

    if(fTorneo.fail())
        fTorneo.clear();
    fTorneo.close();
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
                fTorneo.open("Torneos.dat", ios::binary | ios::in | ios::out);
                cout << "Introduzca el fichero que almacenara la informacion: " << endl;
                cin >> r.Nfichero;

                cout << "Introduzca el nombre del torneo a dar de alta: " << endl;
                cin >> r.nTorneo;

                t[nT].crearFichero(r.Nfichero);
                t[nT].putNomTorneo(r.nTorneo);

                r.nG = t[nT].getNumGolfistas();

                fTorneo.seekp(0,ios::end);
                fTorneo.write((char*)&r,sizeof(TorneoAux));
                nT++;
                fTorneo.close();
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
                    {


                        float handicap;
                        cout << "Introduzca el handicap de los golfistas a mostrar (-1 si quiere ver todos los golfistas) : " << endl;
                        cin >> handicap;
                        t[OpcTorneo-1].mostrar(handicap);
                        break;
                    }

                    case 2:
                    {


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

                        break;
                    }

                    case 3:
                    {


                        Golfista h;
                        cout << "Introduzca la licencia del golfista a consultar: " << endl;
                        cin >> h.licencia;

                        int pos= t[nT].buscar(h.licencia);
                        if(pos==-1)
                        {
                            cout << "No existe ningun golfista con esa licencia" << endl;
                        }

                        else
                        {

                            t[nT].consultar(pos);
                        }

                        break;
                    }

                    case 4:
                    {


                        Golfista j;
                        cadena nombre,apellidos,licencia;

                        cout << "Introduzca los datos del golfista a modificar: "
                             << "\nLicencia: " << endl;
                        cin >> j.licencia;
                        cout << "\nNombre: " << endl;
                        cin >> j.nombre;
                        cout << "\nApellidos: " << endl;
                        cin >> j.apellidos;
                        int pos=t[OpcTorneo -1].buscar(j.licencia);
                        if(pos==-1)
                        {
                            cout << "No existe ningun golfista con esa licencia" << endl;
                        }

                        else
                        {
                            t[OpcTorneo-1].modificar(j,pos);
                        }

                        break;
                    }

                    case 7:
                        cout << "Saliendo del menu..." << endl;
                        break;

                    default:
                        cout << "Error, opcion incorrecta" << endl;
                        break;

                    }
                }
                while(OpcMenuTorneo !=7);
            }





        case 4:
            cout << "Saliendo del menu..." << endl;
            break;

        default:
            break;

        }
    }

    while(opc!=4);
    fTorneo.close();

    return 0;
}
