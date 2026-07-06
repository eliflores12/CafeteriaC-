#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <string>
using namespace std;

// Declaración de funciones
struct Producto
{
    int codigo;
    string nombre;
    float precio;
    int cantidad;
};

void menuCompra();
void agregarAlCarrito(int cod, string nom, float prec, int cantNueva);
void mostrarCarrito();
void modificarCompra();
void cancelarCompra();
void generarFactura();

// FUNCIONES_H
#endif 