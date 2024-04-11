#include <iostream>
#include "Pagos.h"

using namespace std;

int main()
{
    Pagos pagos;

    int op;

    do
    {
        cout << "1) Agregar pago" << endl
             << "2) Mostrar pagos" << endl
             << "3) Buscar pago" << endl
             << "4) eliminar pago" << endl
             << "5) modificar pago" << endl
             << "6) Salir" << endl;
        cin >> op;

        switch (op)
        {
        case 1:
            pagos.agregar();
            break;
        case 2:
            pagos.mostrar();
            break;
        case 3:
            pagos.buscar();
            break;
        case 4:
            pagos.eliminar();
            break;
        case 5:
            pagos.modificar();
            break;
        }

        system("pause");
        system("cls");

    }while(op != 6);


    return 0;
}
