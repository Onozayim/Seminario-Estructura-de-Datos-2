#include "Pagos.h"
#include <iostream>
#include <string>
#include <charconv>
#include <fstream>
#include <stdlib.h>
#include <cstring>

using namespace std;

#include "ConceptoPago.h"

Pagos::Pagos()
{
    //ctor
}

Pagos::~Pagos()
{
    //dtor
}

int dim1, dim2, dim3, dim4, dim5, dim6, dim7;

void Pagos::agregar()
{
    ConceptoPago pago;

    cout << "Ingrese el id del pago: ";
    fflush(stdin);
    cin.getline(pago.idAlumno, 4);

    cout << "Ingrese el nombre del alumno: ";
    fflush(stdin);
    cin.getline(pago.nombreALumno, 50);

    cout << "Ingrese el nombre del tutor de  alumno: ";
    fflush(stdin);
    cin.getline(pago.nombreTutor, 50);

    cout << "Ingrese el nombre de la tutora del alumno: ";
    fflush(stdin);
    cin.getline(pago.nombreTutora, 50);

    cout << "Ingrese la cantidad a pagar: ";
    fflush(stdin);
    cin.getline(pago.cantidadPago, 6);

    cout << "Ingrese la gecha yyyy/mm/dd: ";
    fflush(stdin);
    cin.getline(pago.fecha, 11);

    dim2 = strlen(pago.idAlumno);
    dim3 = strlen(pago.nombreALumno);
    dim4 = strlen(pago.nombreTutor);
    dim5 = strlen(pago.nombreTutora);
    dim6 = strlen(pago.cantidadPago);
    dim7 = strlen(pago.fecha);

    ofstream Archivo("Pagos.txt", ios::app);

    Archivo.write((char*)&dim2, sizeof(int));
    Archivo.write((char*)&pago.idAlumno, dim2);
    Archivo.write((char*)&dim3, sizeof(int));
    Archivo.write((char*)&pago.nombreALumno, dim3);
    Archivo.write((char*)&dim4, sizeof(int));
    Archivo.write((char*)&pago.nombreTutor, dim4);
    Archivo.write((char*)&dim5, sizeof(int));
    Archivo.write((char*)&pago.nombreTutora, dim5);
    Archivo.write((char*)&dim6, sizeof(int));
    Archivo.write((char*)&pago.cantidadPago, dim6);
    Archivo.write((char*)&dim7, sizeof(int));
    Archivo.write((char*)&pago.fecha, dim7);

    this->pagos[this->idPago] = pago;
    this->idPago++;

    Archivo.close();


}

void Pagos::mostrar()
{
    ifstream Archivo("Pagos.txt");

    if(!Archivo.good())
    {
        cout << "Archivo no valido" << endl;
        return;
    }

    ConceptoPago pago;

    while(!Archivo.eof())
    {
        Archivo.read((char*)&dim2, sizeof(int));
        Archivo.read((char*)&pago.idAlumno, dim2);
        Archivo.read((char*)&dim3, sizeof(int));
        Archivo.read((char*)&pago.nombreALumno, dim3);
        Archivo.read((char*)&dim4, sizeof(int));
        Archivo.read((char*)&pago.nombreTutor, dim4);
        Archivo.read((char*)&dim5, sizeof(int));
        Archivo.read((char*)&pago.nombreTutora, dim5);
        Archivo.read((char*)&dim6, sizeof(int));
        Archivo.read((char*)&pago.cantidadPago, dim6);
        Archivo.read((char*)&dim7, sizeof(int));
        Archivo.read((char*)&pago.fecha, dim7);

        pago.idAlumno[dim2] = '\0';
        pago.nombreALumno[dim3] = '\0';
        pago.nombreTutor[dim4] = '\0';
        pago.nombreTutora[dim5] = '\0';
        pago.cantidadPago[dim6] = '\0';
        pago.fecha[dim7] = '\0';

        if(!Archivo.eof())
        {
            cout
                 << "idPago: " << pago.idAlumno << endl
                 << "nombre Alumno: " << pago.nombreALumno << endl
                 << "nombre tutor: " << pago.nombreTutor << endl
                 << "Nombre tutora: " << pago.nombreTutora << endl
                 << "Cantidad Pago: " << pago.cantidadPago << endl
                 << "Fecha: " << pago.fecha << endl << endl;
        }

    }

    Archivo.close();
}

void Pagos::buscar()
{
    ifstream Archivo("Pagos.txt");

    if(!Archivo.good())
    {
        cout << "Archivo no valido" << endl;
        return;
    }

    ConceptoPago pago;

    char idAlumno[4];

    cout << "Ingrese el id del pago a buscar: ";
    fflush(stdin);
    cin.getline(idAlumno, 4);

    while(!Archivo.eof())
    {
        Archivo.read((char*)&dim2, sizeof(int));
        Archivo.read((char*)&pago.idAlumno, dim2);
        Archivo.read((char*)&dim3, sizeof(int));
        Archivo.read((char*)&pago.nombreALumno, dim3);
        Archivo.read((char*)&dim4, sizeof(int));
        Archivo.read((char*)&pago.nombreTutor, dim4);
        Archivo.read((char*)&dim5, sizeof(int));
        Archivo.read((char*)&pago.nombreTutora, dim5);
        Archivo.read((char*)&dim6, sizeof(int));
        Archivo.read((char*)&pago.cantidadPago, dim6);
        Archivo.read((char*)&dim7, sizeof(int));
        Archivo.read((char*)&pago.fecha, dim7);

        pago.idAlumno[dim2] = '\0';
        pago.nombreALumno[dim3] = '\0';
        pago.nombreTutor[dim4] = '\0';
        pago.nombreTutora[dim5] = '\0';
        pago.cantidadPago[dim6] = '\0';
        pago.fecha[dim7] = '\0';

        if(!Archivo.eof() && strcasecmp(idAlumno, pago.idAlumno) == 0)
        {
            cout
                 << "idPago: " << pago.idAlumno << endl
                 << "nombre Alumno: " << pago.nombreALumno << endl
                 << "nombre tutor: " << pago.nombreTutor << endl
                 << "Nombre tutora: " << pago.nombreTutora << endl
                 << "Cantidad Pago: " << pago.cantidadPago << endl
                 << "Fecha: " << pago.fecha << endl << endl;

            Archivo.close();
            return;
        }

    }

    Archivo.close();

    cout << "No se enontro al pago" << endl << endl;
}

void Pagos::eliminar()
{
    ifstream Archivo("Pagos.txt");

    if(!Archivo.good())
    {
        cout << "Archivo no valido" << endl;
        return;
    }

    ConceptoPago pago;

    char idAlumno[4];
    int op = 0;

    cout << "Ingrese el id del pago a eliminar: ";
    fflush(stdin);
    cin.getline(idAlumno, 4);

    while(!Archivo.eof())
    {
        Archivo.read((char*)&dim2, sizeof(int));
        Archivo.read((char*)&pago.idAlumno, dim2);
        Archivo.read((char*)&dim3, sizeof(int));
        Archivo.read((char*)&pago.nombreALumno, dim3);
        Archivo.read((char*)&dim4, sizeof(int));
        Archivo.read((char*)&pago.nombreTutor, dim4);
        Archivo.read((char*)&dim5, sizeof(int));
        Archivo.read((char*)&pago.nombreTutora, dim5);
        Archivo.read((char*)&dim6, sizeof(int));
        Archivo.read((char*)&pago.cantidadPago, dim6);
        Archivo.read((char*)&dim7, sizeof(int));
        Archivo.read((char*)&pago.fecha, dim7);

        pago.idAlumno[dim2] = '\0';
        pago.nombreALumno[dim3] = '\0';
        pago.nombreTutor[dim4] = '\0';
        pago.nombreTutora[dim5] = '\0';
        pago.cantidadPago[dim6] = '\0';
        pago.fecha[dim7] = '\0';

        if(!Archivo.eof() && strcasecmp(idAlumno, pago.idAlumno) == 0)
        {
            cout
                 << "idPago: " << pago.idAlumno << endl
                 << "nombre Alumno: " << pago.nombreALumno << endl
                 << "nombre tutor: " << pago.nombreTutor << endl
                 << "Nombre tutora: " << pago.nombreTutora << endl
                 << "Cantidad Pago: " << pago.cantidadPago << endl
                 << "Fecha: " << pago.fecha << endl << endl;

            cout << "Quieres eliminar este registro (si = 1): " << endl;
            cin >> op;

            Archivo.close();
            break;
        }

    }
    Archivo.close();

    if(op == 1)
    {
        ifstream Archivo("Pagos.txt");
        ofstream temp("Temporal.txt");

        while(!Archivo.eof())
        {
            Archivo.read((char*)&dim2, sizeof(int));
            Archivo.read((char*)&pago.idAlumno, dim2);
            Archivo.read((char*)&dim3, sizeof(int));
            Archivo.read((char*)&pago.nombreALumno, dim3);
            Archivo.read((char*)&dim4, sizeof(int));
            Archivo.read((char*)&pago.nombreTutor, dim4);
            Archivo.read((char*)&dim5, sizeof(int));
            Archivo.read((char*)&pago.nombreTutora, dim5);
            Archivo.read((char*)&dim6, sizeof(int));
            Archivo.read((char*)&pago.cantidadPago, dim6);
            Archivo.read((char*)&dim7, sizeof(int));
            Archivo.read((char*)&pago.fecha, dim7);

            if(!Archivo.eof() && !strcasecmp(idAlumno, pago.idAlumno) == 0)
            {
                temp.write((char*)&dim2, sizeof(int));
                temp.write((char*)&pago.idAlumno, dim2);
                temp.write((char*)&dim3, sizeof(int));
                temp.write((char*)&pago.nombreALumno, dim3);
                temp.write((char*)&dim4, sizeof(int));
                temp.write((char*)&pago.nombreTutor, dim4);
                temp.write((char*)&dim5, sizeof(int));
                temp.write((char*)&pago.nombreTutora, dim5);
                temp.write((char*)&dim6, sizeof(int));
                temp.write((char*)&pago.cantidadPago, dim6);
                temp.write((char*)&dim7, sizeof(int));
                temp.write((char*)&pago.fecha, dim7);
            }
        }

        Archivo.close();
        temp.close();
        remove("Pagos.txt");
        rename("Temporal.txt", "Pagos.txt");

        return;
    }


    cout << "No se enontro al pago" << endl << endl;
}


void Pagos::modificar()
{
    ifstream Archivo("Pagos.txt");

    if(!Archivo.good())
    {
        cout << "Archivo no valido" << endl;
        return;
    }

    ConceptoPago pago;

    char idAlumno[4];
    int op = 0;

    cout << "Ingrese el id del alumno a modificar: ";
    fflush(stdin);
    cin.getline(idAlumno, 4);

    while(!Archivo.eof())
    {
        Archivo.read((char*)&dim2, sizeof(int));
        Archivo.read((char*)&pago.idAlumno, dim2);
        Archivo.read((char*)&dim3, sizeof(int));
        Archivo.read((char*)&pago.nombreALumno, dim3);
        Archivo.read((char*)&dim4, sizeof(int));
        Archivo.read((char*)&pago.nombreTutor, dim4);
        Archivo.read((char*)&dim5, sizeof(int));
        Archivo.read((char*)&pago.nombreTutora, dim5);
        Archivo.read((char*)&dim6, sizeof(int));
        Archivo.read((char*)&pago.cantidadPago, dim6);
        Archivo.read((char*)&dim7, sizeof(int));
        Archivo.read((char*)&pago.fecha, dim7);

        pago.idAlumno[dim2] = '\0';
        pago.nombreALumno[dim3] = '\0';
        pago.nombreTutor[dim4] = '\0';
        pago.nombreTutora[dim5] = '\0';
        pago.cantidadPago[dim6] = '\0';
        pago.fecha[dim7] = '\0';

        if(!Archivo.eof() && strcasecmp(idAlumno, pago.idAlumno) == 0)
        {
            cout
                 << "idPago: " << pago.idAlumno << endl
                 << "nombre Alumno: " << pago.nombreALumno << endl
                 << "nombre tutor: " << pago.nombreTutor << endl
                 << "Nombre tutora: " << pago.nombreTutora << endl
                 << "Cantidad Pago: " << pago.cantidadPago << endl
                 << "Fecha: " << pago.fecha << endl << endl;

            cout << "Quieres modificar este registro (si = 1): " << endl;
            cin >> op;

            Archivo.close();
            break;
        }

    }
    Archivo.close();

    if(op == 1)
    {
        ifstream Archivo("Pagos.txt");
        ofstream temp("Temporal.txt");

        while(!Archivo.eof())
        {
            Archivo.read((char*)&dim2, sizeof(int));
            Archivo.read((char*)&pago.idAlumno, dim2);
            Archivo.read((char*)&dim3, sizeof(int));
            Archivo.read((char*)&pago.nombreALumno, dim3);
            Archivo.read((char*)&dim4, sizeof(int));
            Archivo.read((char*)&pago.nombreTutor, dim4);
            Archivo.read((char*)&dim5, sizeof(int));
            Archivo.read((char*)&pago.nombreTutora, dim5);
            Archivo.read((char*)&dim6, sizeof(int));
            Archivo.read((char*)&pago.cantidadPago, dim6);
            Archivo.read((char*)&dim7, sizeof(int));
            Archivo.read((char*)&pago.fecha, dim7);

            if(!Archivo.eof() && strcasecmp(idAlumno, pago.idAlumno) == 0)
            {
                int op2;

                cout << "Ingrese el dato a modificar" << endl
                     << "1)Nombre Alumno" << endl
                     << "2)Nombre tutor" << endl
                     << "3)Nombre tutora" << endl
                     << "4)Cantidad pago" << endl
                     << "5)Fecha" << endl << endl;

                cin >> op2;

                switch(op2)
                {
                case 1:
                    fflush(stdin);
                    cin.getline(pago.nombreALumno, 50);
                    dim3 = strlen(pago.nombreALumno);
                    break;
                case 2:
                    fflush(stdin);
                    cin.getline(pago.nombreTutor, 50);
                    dim4 = strlen(pago.nombreTutor);
                    break;
                case 3:
                    fflush(stdin);
                    cin.getline(pago.nombreTutora, 50);
                    dim5 = strlen(pago.nombreTutora);
                    break;
                case 4:
                    fflush(stdin);
                    cin.getline(pago.cantidadPago, 6);
                    dim6 = strlen(pago.cantidadPago);
                    break;
                case 5:
                    fflush(stdin);
                    cin.getline(pago.fecha, 11);
                    dim7 = strlen(pago.fecha);
                    break;
                }
            }

            if(!Archivo.eof())
            {
                temp.write((char*)&dim2, sizeof(int));
                temp.write((char*)&pago.idAlumno, dim2);
                temp.write((char*)&dim3, sizeof(int));
                temp.write((char*)&pago.nombreALumno, dim3);
                temp.write((char*)&dim4, sizeof(int));
                temp.write((char*)&pago.nombreTutor, dim4);
                temp.write((char*)&dim5, sizeof(int));
                temp.write((char*)&pago.nombreTutora, dim5);
                temp.write((char*)&dim6, sizeof(int));
                temp.write((char*)&pago.cantidadPago, dim6);
                temp.write((char*)&dim7, sizeof(int));
                temp.write((char*)&pago.fecha, dim7);
            }

        }

        Archivo.close();
        temp.close();
        remove("Pagos.txt");
        rename("Temporal.txt", "Pagos.txt");

        return;
    }


    cout << "No se enontro al pago" << endl << endl;
}
