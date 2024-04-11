#include "Trabajador.h"
#include <iostream>
#include <fstream>
#include "cstring"

using namespace std;

Trabajador::Trabajador()
{
    //ctor
}

Trabajador::~Trabajador()
{
    //dtor
}

string fileName = "Trabajadores.txt";
int mat[1000][1000];
string ids[1000];
int numsOfIds = 0;

void Trabajador::agregar()
{
    Trabajador trab;
    cout << "Ingrese el id: ";
    fflush(stdin);
    cin.getline(trab.id, 3);

    cout << "Ingrese el Nombre: ";
    fflush(stdin);
    cin.getline(trab.nombre, 25);

    cout << "Ingrese el Apellido Paterno: ";
    fflush(stdin);
    cin.getline(trab.apellidoP, 25);

    cout << "Ingrese el Apellido Materno: ";
    fflush(stdin);
    cin.getline(trab.apellidoM, 25);

    cout << "Ingrese el salario: ";
    fflush(stdin);
    cin.getline(trab.salario, 6);

    cout << "Ingrese el area: ";
    fflush(stdin);
    cin.getline(trab.area, 20);

    cout << "Ingrese el horario: ";
    fflush(stdin);
    cin.getline(trab.horario, 20);


    ofstream archivo(fileName, ios::app);
    archivo.write((char*)&trab, sizeof(Trabajador));
    archivo.close();
}

void Trabajador::imprimirTrabajador(Trabajador tra)
{
    cout << "Id: " << tra.id << endl
         << "Nombre: " << tra.nombre << endl
         << "Apellido Paterno: " << tra.apellidoP << endl
         << "Apellido Materno: " << tra.apellidoM << endl
         << "Salario: " << tra.salario << endl
         << "Area: " << tra.area << endl
         << "Horario: " << tra.horario << endl << endl;

}

void Trabajador::imprimir()
{
    ifstream archivo(fileName, ios::in);

    if(!archivo.good())
    {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    Trabajador tra;

    while(!archivo.eof())
    {
        archivo.read((char*)&tra, sizeof(Trabajador));
        if(!archivo.eof())
            imprimirTrabajador(tra);
    }

    archivo.close();
}

void Trabajador::buscar()
{
    ifstream archivo(fileName, ios::in);
    char id[4];

    if(!archivo.good())
    {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    cout << "Ingrese el id del trabajador: ";
    fflush(stdin);
    cin.getline(id, 4);

    Trabajador tra;

    while(!archivo.eof())
    {
        archivo.read((char*)&tra, sizeof(Trabajador));
        if(!archivo.eof() && strcmp(tra.id, id) == 0)
        {
            imprimirTrabajador(tra);
            archivo.close();
            return;
        }
    }

    cout << "REGISTRO NO ENCONTRADO" << endl << endl;
    archivo.close();
}

void Trabajador::modificar()
{
    ifstream archivo(fileName, ios::in);
    char id[4];
    int op;

    if(!archivo.good())
    {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    cout << "Ingrese el id del trabajador: ";
    fflush(stdin);
    cin.getline(id, 4);

    Trabajador tra;

    while(!archivo.eof())
    {
        archivo.read((char*)&tra, sizeof(Trabajador));
        if(!archivo.eof() && strcmp(tra.id, id) == 0)
        {
            imprimirTrabajador(tra);
            cout << "Estas seguro que quieres modificar este trabajador (si == 1)? ";
            cin >> op;
            break;
        }
    }

    archivo.close();

    if(op == 1)
    {
        ifstream mod(fileName, ios::in);
        ofstream temp("temp.txt", ios::app);

        if(!mod.good())
        {
            cout << "Archivo no encontrado" << endl;
            return;
        }

        while(!mod.eof())
        {
            mod.read((char*)&tra, sizeof(Trabajador));
            if(!mod.eof() && strcmp(tra.id, id) == 0)
            {
                cout << "1) Id" << endl
                     << "2) Nombre" << endl
                     << "3) Apellido Paterno" << endl
                     << "4) Apellido Materno" << endl
                     << "5) Salario" << endl
                     << "6) Area" << endl
                     << "7) Horario" << endl << endl;

                cout << "Que datos deseas modificar? ";
                cin >> op;

                fflush(stdin);

                switch(op)
                {
                case 1:
                    cout << "Id: ";
                    cin.getline(tra.id, 3);
                    break;

                case 2:
                    cout << "Nombre: ";
                    cin.getline(tra.nombre, 25);
                    break;

                case 3:
                    cout << "Apellido Paterno: ";
                    cin.getline(tra.apellidoP, 25);
                    break;

                case 4:
                    cout << "Apellido Materno: ";
                    cin.getline(tra.apellidoM, 25);
                    break;

                case 5:
                    cout << "Salario: ";
                    cin.getline(tra.salario, 6);
                    break;

                case 6:
                    cout << "Area: ";
                    cin.getline(tra.area, 20);
                    break;

                case 7:
                    cout << "Horario: ";
                    cin.getline(tra.horario, 20);
                    break;

                }
            }


            if(!mod.eof())
                temp.write((char*)&tra, sizeof(Trabajador));
        }

        temp.close();
        mod.close();

        remove("Trabajadores.txt");
        rename("temp.txt", "Trabajadores.txt");

        return;
    }

}

void Trabajador::eliminar()
{
    ifstream archivo(fileName, ios::in);
    char id[4];
    int op;

    if(!archivo.good())
    {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    cout << "Ingrese el id del trabajador: ";
    fflush(stdin);
    cin.getline(id, 4);

    Trabajador tra;

    while(!archivo.eof())
    {
        archivo.read((char*)&tra, sizeof(Trabajador));
        if(!archivo.eof() && strcmp(tra.id, id) == 0)
        {
            imprimirTrabajador(tra);
            cout << "Estas seguro que quieres eliminar este trabajador (si == 1)? ";
            cin >> op;
            break;
        }
    }

    archivo.close();

    if(op == 1)
    {
        ifstream mod(fileName, ios::in);
        ofstream temp("temp.txt", ios::app);

        if(!mod.good())
        {
            cout << "Archivo no encontrado" << endl;
            return;
        }

        while(!mod.eof())
        {
            mod.read((char*)&tra, sizeof(Trabajador));
            if(!mod.eof() && strcmp(tra.id, id) != 0)
                temp.write((char*)&tra, sizeof(Trabajador));

        }

        temp.close();
        mod.close();

        remove("Trabajadores.txt");
        rename("temp.txt", "Trabajadores.txt");

        return;
    }

}

void Trabajador::generarGrafos()
{
    Trabajador tra;
    ifstream archivo(fileName, ios::in);
    numsOfIds = 0;

    int op = 0;

    while(!archivo.eof())
    {
        archivo.read((char*)&tra, sizeof(Trabajador));
        if(!archivo.eof())
        {
            ids[numsOfIds] = tra.id;
            numsOfIds++;
        }
    }

    archivo.close();

    for(int i = 0; i < numsOfIds; i++)
    {
        for(int j = 0; j < numsOfIds; j++)
        {
            if(ids[i] != ids[j])
            {
                cout << "El id: " << ids[i] << " se une con el id: " << ids[j] << " ? ";
                cin >> op;
                mat[i][j] = op;
            }
        }
    }
}

void Trabajador::mostrarGrafos()
{

    cout << '\t';

    for(int i = 0; i < numsOfIds; i++)
        cout << ids[i] << '\t';

    cout << endl;
    for(int i = 0; i < numsOfIds; i++)
    {
        cout << ids[i] << '\t';
        for(int j = 0; j < numsOfIds; j++)
            cout << mat[i][j] << '\t';

        cout << endl;
    }

    cout << endl;

    ofstream archivo("Grafos.txt", ios::app);

    archivo << '\t';

    for(int i = 0; i < numsOfIds; i++)
        archivo << ids[i] << '\t';

    archivo << endl;
    for(int i = 0; i < numsOfIds; i++)
    {
        archivo << ids[i] << '\t';
        for(int j = 0; j < numsOfIds; j++)
            archivo << mat[i][j] << '\t';

        archivo << endl;
    }

    archivo << endl;
    archivo.close();
}
