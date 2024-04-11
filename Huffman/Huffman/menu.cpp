#include "menu.h"

Menu::Menu()
{
    string op;
    Platillo plat;
    coding();
    while (true) {
        cout<<"\n+--------------------------------+"<<endl
            <<"|\t    MENU PRINCIPAL       |"     <<endl
            <<"+--------------------------------+"<<endl
            <<"|\t1.- Crear Platillo       |"     <<endl
            <<"|\t2.- Mostrar Platillos    |"     <<endl
            <<"|\t3.- Buscar Platillo      |"     <<endl
            <<"|\t4.- Modificar Platillo   |"     <<endl
            <<"|\t5.- Eliminacion Fisica   |"     <<endl
            <<"|\t6.- Eliminacion Logica   |"     <<endl
            <<"|\t7.- Activar Platillos    |"     <<endl
            <<"|\t8.- Cifrado Huffman      |"     <<endl
            <<"|\t9.- Descifrado Huffman   |"     <<endl
            <<"|\t0.- Salir                |"     <<endl
            <<"|________________________________|"<<endl
            <<"\nSeleccione una opcion: ";
        getline(cin,op);

        if(op == "1"){
            system("cls");
            crearP(plat);
            escribir(plat);
        }
        else if(op == "2"){
            system("cls");
            MostrarP();
        }
        else if (op == "3") {
            system("cls");
            BuscarP();
        }
        else if (op == "4") {
            system("cls");
            ModificarP();
        }
        else if (op == "5") {
            system("cls");
            Eliminar_F_P();
        }
        else if (op == "6") {
            system("cls");
            Eliminar_L_P();
        }
        else if (op == "7") {
            ActivarP();
        }
        else if (op == "8"){
            system("cls");
            Huffman();
        }
        else if (op == "9"){
            system("cls");
            descifrado();
        }
        else if (op == "0"){
            cout<<"\n+--------------------------------+"<<endl
                <<"|\t    HASTA LUEGO          |"       <<endl
                <<"+--------------------------------+\n"<<endl;
            break;
        }
        else
            cout<<"\nERROR!! Opcion NO Valida"<<endl;
    }

}
void Menu::crearP(Platillo &p)
{
    string temporal, a="1";

    cout<<"+--------------------------------+"<<endl
        <<"|\t  NUEVO PLATILLO         |"     <<endl
        <<"+--------------------------------+"<<endl;

    cout<<"Ingrese el Nombre: ";
    getline(cin, temporal);
    p.setNombre(temporal);

    cout<<"Ingrese su Descripcion: ";
    getline(cin, temporal);
    p.setDescrip(temporal);

    cout<<"Ingrese el Precio: ";
    getline(cin, temporal);
    p.setPrecio(temporal);

    int i=getCont();
    i++;
    string cod = to_string(i);
    p.setCodigo(cod);
    setCont(i);

    p.setBandera(a);
    cout<<"\n\tPlatillo Agregado"<<endl;
}
void Menu::escribir(const Platillo &p)
{
    ofstream escribir("Platillos.txt", ios::app);
    if(!escribir.is_open()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
        return;
    }
    escribir<<p;
    escribir.close();
}
void Menu::mostrar(Platillo &p)
{
    cout<<"Nombre: "      <<p.getNombre()<<endl
        <<"Descripcion: " <<p.getDescrip()<<endl
        <<"Precio: "      <<p.getPrecio()<<endl
        <<"Codigo: "      <<p.getCodigo()<<endl
        <<"---------------------------------\n"<<endl;
}
void Menu::MostrarP()
{
    Platillo p_temp;
    ifstream leer("Platillos.txt");
    string temporal;
    if(!leer.good()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
    }
    else{
        cout<<"+--------------------------------+"<<endl
            <<"|\t     PLATILLOS           |"     <<endl
            <<"+--------------------------------+\n"<<endl;

        while (!leer.eof()) {
            getline(leer,temporal,',');
            p_temp.setNombre(temporal);

            getline(leer,temporal,',');
            p_temp.setDescrip(temporal);

            getline(leer,temporal,',');
            p_temp.setPrecio(temporal);

            getline(leer,temporal,',');
            p_temp.setCodigo(temporal);

            getline(leer,temporal,',');
            p_temp.setBandera(temporal);
            if (leer.eof()) {
                break;
            }
            if (p_temp.getBandera() == "1") {
                mostrar(p_temp);
            }

        }
        leer.close();
    }

}
void Menu::coding()
{
    ifstream c("Platillos.txt");
    string temporal,temporal2;
    int i;
    if(!c.good()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
        return;
    }
    else{
        while(!c.eof()){
            getline(c,temporal,',');
            getline(c,temporal,',');
            getline(c,temporal,',');
            getline(c,temporal,',');
            getline(c,temporal2,',');
            if(c.eof()){
                break;
            }
            i=stoi(temporal);
            setCont(i);
        }
    }
    c.close();
}
void Menu::BuscarP()
{
    ifstream busqueda("Platillos.txt");
    string temporal;
    Platillo p_temp;
    if(!busqueda.good()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
        return;
    }
    else{
        string code;
        bool band = false;

        cout<<"+--------------------------------+"<<endl
            <<"|\t   BUSCAR DE PLATILLO    |"     <<endl
            <<"+--------------------------------+\n"<<endl;

        cout<<"Digite el Codigo: ";
        getline(cin,code);

        while(!busqueda.eof()){
            getline(busqueda,temporal,',');
            p_temp.setNombre(temporal);

            getline(busqueda,temporal,',');
            p_temp.setDescrip(temporal);

            getline(busqueda,temporal,',');
            p_temp.setPrecio(temporal);

            getline(busqueda,temporal,',');
            p_temp.setCodigo(temporal);

            getline(busqueda,temporal,',');
            p_temp.setBandera(temporal);

            if (code == p_temp.getCodigo() && p_temp.getBandera() == "1") {

                cout<<"\n\tPlatillo Encontrado\n"<<endl;
                mostrar(p_temp);
                band = true;
                break;
            }
            if(busqueda.eof()){
                break;
            }
        }
        if (band == false) {
            cout<<"\n\tPlatillo NO Encontrado"<<endl;
        }
        busqueda.close();
    }
}
void Menu::ModificarP()
{
    ifstream old("Platillos.txt");
    ofstream copia("copia.txt", ios::app);
    Platillo p;
    bool band= false;
    string temporal, temp2;
    if(!old.good()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
        return;
    }
    else{

        cout<<"+--------------------------------+"<<endl
            <<"|\t MODIFICAR PLATILLO      |"     <<endl
            <<"+--------------------------------+\n"<<endl;

        cout<<"Digite el Codigo: ";
        string code;
        getline(cin,code);

        while(!old.eof()){
            getline(old,temporal,',');
            p.setNombre(temporal);

            getline(old,temporal,',');
            p.setDescrip(temporal);

            getline(old,temporal,',');
            p.setPrecio(temporal);

            getline(old,temporal,',');
            p.setCodigo(temporal);

            getline(old,temporal,',');
            p.setBandera(temporal);
            if(old.eof()){
                break;
            }
            if (code == p.getCodigo() && p.getBandera() == "1") {
                cout<<"Ingrese los NUEVOS Datos\n"<<endl;

                cout<<"Nombre: ";
                getline(cin, temp2);
                p.setNombre(temp2);

                cout<<"Descripcion: ";
                getline(cin, temp2);
                p.setDescrip(temp2);

                cout<<"Precio: ";
                getline(cin, temp2);
                p.setPrecio(temp2);

                temp2 = "1";
                p.setBandera(temp2);
                cout<<"\n\tPlatillo Eliminado"<<endl;
                band = true;

            }
            copia<<p;
        }
        if (band==false) {
            cout<<"\n\tPlatillo NO Encontrado"<<endl;
        }
        old.close();
        copia.close();
        remove("Platillos.txt");
        rename("copia.txt","Platillos.txt");
    }
}
void Menu::Eliminar_F_P()
{
    ifstream eliminar("Platillos.txt");
    bool band = false;
    Platillo p;
    string temporal;

    if(!eliminar.good()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
        return;
    }
    else{

        cout<<"+--------------------------------+"<<endl
            <<"|\t ELIMINAR PLATILLO       |"     <<endl
            <<"+--------------------------------+\n"<<endl;

        cout<<"Digite el Codigo: ";
        string code;
        getline(cin,code);

        ofstream copia("copia.txt");
        while(!eliminar.eof()){
            getline(eliminar,temporal,',');
            p.setNombre(temporal);

            getline(eliminar,temporal,',');
            p.setDescrip(temporal);

            getline(eliminar,temporal,',');
            p.setPrecio(temporal);

            getline(eliminar,temporal,',');
            p.setCodigo(temporal);

            getline(eliminar,temporal,',');
            p.setBandera(temporal);

            if(eliminar.eof()){
                break;
            }
            if (code != p.getCodigo()){
                band=true;
                copia<<p;
            }
            if(p.getBandera() == "0"){
                band=true;
                copia<<p;

            }
        }
        if (band == false) {
            cout<<"\n\tPlatillo NO Encontrado"<<endl;
        }
        eliminar.close();
        copia.close();
        remove("Platillos.txt");
        rename("copia.txt","Platillos.txt");

    }

}
void Menu::Eliminar_L_P()
{
    ifstream eliminar("Platillos.txt");
    ofstream copia("copia.txt");
    Platillo p;
    string temporal;

    cout<<"+--------------------------------+"<<endl
        <<"|\t ELIMINAR PLATILLO       |"     <<endl
        <<"+--------------------------------+\n"<<endl;

    cout<<"Digite el Codigo: ";
    string code;

    bool band = false;
    getline(cin,code);

    if(!eliminar.good()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
        return;
    }
    else{
        while(!eliminar.eof()){

            getline(eliminar,temporal,',');
            p.setNombre(temporal);

            getline(eliminar,temporal,',');
            p.setDescrip(temporal);

            getline(eliminar,temporal,',');
            p.setPrecio(temporal);

            getline(eliminar,temporal,',');
            p.setCodigo(temporal);

            getline(eliminar,temporal,',');
            p.setBandera(temporal);

            if(eliminar.eof()){
                break;
            }
            if (code == p.getCodigo()){
                temporal = "0";
                p.setBandera(temporal);
                band =true;

            }
            copia<<p;
        }
        if (band==true) {
            cout<<"\n\tPlatillo Eliminado"<<endl;
        }
        else {
            cout<<"\n\tPlatillo NO Encontrado"<<endl;
        }
        eliminar.close();
        copia.close();
        remove("Platillos.txt");
        rename("copia.txt","Platillos.txt");
    }
}
void Menu::ActivarP()
{
    ifstream activar("Platillos.txt");
    ofstream copia("copia.txt");
    Platillo p;
    string temporal;

    bool band = false;

    if(!activar.good()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
        return;
    }
    else{

        cout<<"+--------------------------------+"<<endl
            <<"|\t ACTIVAR PLATILLO       |"     <<endl
            <<"+--------------------------------+\n"<<endl;

        cout<<"Digite el Codigo: ";
        string code;
        getline(cin,code);

        while(!activar.eof()){
            getline(activar,temporal,',');
            p.setNombre(temporal);

            getline(activar,temporal,',');
            p.setDescrip(temporal);

            getline(activar,temporal,',');
            p.setPrecio(temporal);

            getline(activar,temporal,',');
            p.setCodigo(temporal);

            getline(activar,temporal,',');
            p.setBandera(temporal);
            if(activar.eof()){
                break;
            }
            if (code == p.getCodigo() && p.getBandera()=="0"){
                temporal = "1";
                p.setBandera(temporal);
                band =true;
            }
            copia<<p;
        }
        if (band==true) {
            cout<<"\n\tPlatillo Restaurado"<<endl;
        }
        else {
            cout<<"\n\tPlatillo NO Encontrado"<<endl;
        }
        activar.close();
        copia.close();
        remove("Platillos.txt");
        rename("copia.txt","Platillos.txt");
    }
}

void Menu::Huffman()
{
    cargarFrase();
    mostrarLista();
    listaOrdenada();
    mostrarListaArbol();
    mostrarDiccionario();
}

void Menu::cargarFrase()
{
    ifstream archivo("Platillos.txt");

    string aux;
    string frase;

    if(!archivo.good()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
        return;
    }
    else{

        lista.clear();

        while(!archivo.eof()){
            getline(archivo,aux);
            frase += aux;
            if(archivo.eof()){
                break;
            }
        }
        cout<<frase<<endl;

        int tam = frase.length();

        for(int i = 0; i < tam; i++){
            NodoL* nodo = lista.findDataChar(frase[i]);

            if(nodo == nullptr){
                lista.insertData(lista.getLast(), 1, frase[i]);
            }
            else{
                nodo->aumentarFrecuencia();
            }
        }
    }
    archivo.close();
    texto = frase;
    getchar();
}

void Menu::mostrarLista()
{
//    system("cls");
    cout<<"+--------------------------------+"<<endl
        <<"|\tLISTA DE CARACTERES      |"     <<endl
        <<"+--------------------------------+\n"<<endl;

//    cout<<"Frase: " << texto<<endl;
    cout<<"\nLista de Caracteres: \n"<<endl;
//    lista.imprimirLista();
//    getchar();
}

void Menu::listaOrdenada()
{
//    system("cls");
    cout<<"\n+--------------------------------+"<<endl
        <<"|\t  LISTA ORDENADA           |"     <<endl
        <<"+--------------------------------+\n"<<endl;

    cout<<"\nLista Ordenada Ascendetemente: \n"<< endl;
    lista.ordenarLista();
//    lista.imprimirLista();
//    getchar();
}

void Menu::mostrarListaArbol()
{
//    system("cls");
    cout<<"\n+--------------------------------+"<<endl
        <<"|\t  LISTA A ARBOL          |"       <<endl
        <<"+--------------------------------+\n"<<endl;

    lista.convertirToArbol();
//    lista.mostrarArbol(lista.getFirst(), 0);

//    string a = lista.stringTotal;

//    system("cls");
//    int x,y;
//    x=60;
//    y=10;

//    lista.mostrarArbol2(lista.getFirst(),x,y);
//    getchar();

//    system("cls");
//    lista.mostrarArbol3(lista.getFirst(),0);
    //    getchar();
}

void Menu::mostrarDiccionario()
{
    cout<<"\n+--------------------------------+"<<endl
        <<"|      DICCIONARIO DE DATOS      |"<<endl
        <<"+--------------------------------+\n"<<endl;

    lista.diccionario(lista.getFirst(),0);

    cout<<"\n+--------------------------------+"<<endl
        <<"|     TRADUCCION DE CADENA       |"<<endl
        <<"+--------------------------------+\n"<<endl;

    lista.transformarConDiccionario(texto);
    lista.empaquetar();
    string a = lista.cifrado;

    cout<<"C: "<<a<<endl;
    lista.guardarDiccionario();
}

void Menu::descifrado()
{
    lista.leerArchivo();
}

int Menu::getCont() const
{
    return cont;
}

void Menu::setCont(int value)
{
    cont = value;
}

string Menu::getTexto() const
{
    return texto;
}

void Menu::setTexto(const string &value)
{
    texto = value;
}
