#include "platillo.h"

Platillo::Platillo()
{

}

string Platillo::getNombre() const
{
    return nombre;
}

void Platillo::setNombre(const string &value)
{
    nombre = value;
}

string Platillo::getDescrip() const
{
    return descrip;
}

void Platillo::setDescrip(const string &value)
{
    descrip = value;
}

string Platillo::getPrecio() const
{
    return precio;
}

void Platillo::setPrecio(const string &value)
{
    precio = value;
}

string Platillo::getCodigo() const
{
    return codigo;
}

void Platillo::setCodigo(const string &value)
{
    codigo = value;
}

string Platillo::getBandera() const
{
    return bandera;
}

void Platillo::setBandera(const string &value)
{
    bandera = value;
}
