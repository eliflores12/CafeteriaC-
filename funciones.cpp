#include "funciones.h"
#include <iostream>
#include <fstream>
using namespace std;

void menuCompra()
{
    int comprar, cant;
    char agregar;

    do
    {
        cout << "\n--- Productos Disponibles ---\n";
        cout << "1. Pupusas - $1.00\n";
        cout << "2. Jugo Natural - $1.50\n";
        cout << "3. Fruta - $1.50\n";
        cout << "4. Plato del dia - $4.00\n";
        cout << "5. Gaseosa - $1.00\n";
        cout << "6. Botella de agua - $0.80\n";
        cout << "Seleccione el producto que desea comprar: ";
        cin >> comprar;

        if (comprar >= 1 && comprar <= 6)
        {
            cout << "Cuantas unidades desea comprar?: ";
            cin >> cant;

            if (cant > 0)
            {

                switch (comprar)
                {
                case 1:
                    agregarAlCarrito(1, "Pupusas", 1.00, cant);
                    break;
                case 2:
                    agregarAlCarrito(2, "Jugo Natural", 1.50, cant);
                    break;
                case 3:
                    agregarAlCarrito(3, "Fruta", 1.50, cant);
                    break;
                case 4:
                    agregarAlCarrito(4, "Plato del dia", 4.00, cant);
                    break;
                case 5:
                    agregarAlCarrito(5, "Gaseosa", 1.00, cant);
                    break;
                case 6:
                    agregarAlCarrito(6, "Botella de agua", 0.80, cant);
                    break;
                }
            }
            else
            {
                cout << "Cantidad no valida.\n";
            }
        }
        else
        {
            cout << "Opcion de producto no valida.\n";
        }

        cout << "¿Deseas agregar mas productos al carrito? (s/n): ";
        cin >> agregar;

    } while (agregar == 's' || agregar == 'S');
}

// agregarAlCarrito -> Recibe los datos del producto y los almacena en un archivo de texto

void agregarAlCarrito(int cod, string nom, float prec, int cantNueva)
{
    ifstream archivo("carrito.txt");
    ofstream temp("temp.txt");
    char separador;
    Producto p;
    bool encontrado = false;

    if (archivo.is_open())
    {
        while (archivo >> p.codigo >> separador)
        {
            getline(archivo, p.nombre, ';');
            archivo >> p.precio >> separador >> p.cantidad;
            archivo.ignore();

            if (p.codigo == cod)
            {
                p.cantidad += cantNueva;
                encontrado = true;
            }

            temp << p.codigo << ";" << p.nombre << ";" << p.precio << ";" << p.cantidad << endl;
        }
        archivo.close();
    }

    if (!encontrado)
    {
        temp << cod << ";" << nom << ";" << prec << ";" << cantNueva << endl;
    }
    temp.close();

    remove("carrito.txt");
    rename("temp.txt", "carrito.txt");

    cout << "Agregado al carrito correctamente.\n";
}
// mostrarCarrito -> Muestra el contenido del carrito de compras y calcula el total acumulado

void mostrarCarrito()
{
    ifstream archivo("carrito.txt");
    char separador;
    Producto p;
    float total = 0.0;

    if (!archivo.is_open())
    {
        cout << "\nEl carrito de compras esta vacio.\n";
        return;
    }

    cout << "\n===== CARRITO DE COMPRAS =====\n";
    cout << "Cod\tProducto\tPrecio\tCant\tSubtotal\n";
    cout << "-----------------------------------------------\n";

    while (archivo >> p.codigo >> separador)
    {
        getline(archivo, p.nombre, ';');
        archivo >> p.precio >> separador >> p.cantidad;
        archivo.ignore();

        float subtotal = p.precio * p.cantidad;
        total += subtotal;

        // Utilizamos tabulaciones para alinear la salida de los productos en el carrito y formato delimitado por comas
        cout << p.codigo << "\t" << p.nombre << "\t$" << p.precio << "\t" << p.cantidad << "\t$" << subtotal << endl;
    }
    archivo.close();

    cout << "-----------------------------------------------\n";
    cout << "Total acumulado a pagar: $" << total << endl;
}

// modificarCompra -> Permite al usuario modificar la cantidad de un producto en el carrito de compras

void modificarCompra()
{
    int codigoBuscar, nuevaCantidad;
    cout << "\n Ingrese el codigo del producto que desea modificar: ";
    cin >> codigoBuscar;

    ifstream archivo("carrito.txt");
    ofstream temp("temp.txt");
    char separador;
    Producto p;
    bool encontrado = false;

    if (!archivo.is_open())
    {
        cout << "No hay un carrito activo para modificar.\n";
        temp.close();
        remove("temp.txt");
        return;
    }

    while (archivo >> p.codigo >> separador)
    {
        getline(archivo, p.nombre, ';');
        archivo >> p.precio >> separador >> p.cantidad;
        archivo.ignore();

        if (p.codigo == codigoBuscar)
        {
            encontrado = true;
            cout << "Producto seleccionado: " << p.nombre << " (Cantidad actual: " << p.cantidad << ")\n";
            cout << "Ingrese la nueva cantidad: ";
            cin >> nuevaCantidad;
            p.cantidad = nuevaCantidad;
        }

        if (p.cantidad > 0)
        {
            temp << p.codigo << ";" << p.nombre << ";" << p.precio << ";" << p.cantidad << endl;
        }
    }
    archivo.close();
    temp.close();

    remove("carrito.txt");
    rename("temp.txt", "carrito.txt");

    if (encontrado)
        cout << "Cantidad actualizada correctamente en el registro.\n";
    else
        cout << "El código de producto no esta en el carrito.\n";
}

// cancelarCompra -> Elimina el archivo del carrito de compras, vaciando el contenido

void cancelarCompra()
{
    ifstream archivo("carrito.txt");
    if (archivo.is_open())
    {
        archivo.close();
        remove("carrito.txt");
        cout << "\n Compra cancelada. El carrito se ha vaciado por completo.\n";
    }
    else
    {
        cout << "\n No hay ninguna compra activa para cancelar.\n";
    }
}

// generarFactura -> Genera un archivo de factura con el contenido del carrito y calcula el total final

void generarFactura()
{
    ifstream archivo("carrito.txt");
    char separador;
    Producto p;
    float total = 0.0;

    if (!archivo.is_open())
    {
        cout << "\n No hay productos en el carrito para facturar.\n";
        return;
    }

    // Se escribe la factura final en un archivo de salida independiente
    ofstream factura("factura_cafeteria.txt", ios::app);

    factura << "\n =========================================\n";
    factura << "          FACTURA CAFETERIA UCA          \n";
    factura << "\n =========================================\n";

    cout << "\n ===== PROCESANDO FACTURACION =====\n";

    while (archivo >> p.codigo >> separador)
    {
        getline(archivo, p.nombre, ';');
        archivo >> p.precio >> separador >> p.cantidad;
        archivo.ignore();

        float subtotal = p.precio * p.cantidad;
        total += subtotal;

        factura << p.nombre << " x" << p.cantidad << " \t Subtotal: $" << subtotal << endl;
    }
    archivo.close();

    factura << "-----------------------------------------\n";
    factura << "TOTAL FINAL PAGADO: $" << total << endl;
    factura << "=========================================\n";
    factura.close();
    cout << "Factura generada con éxito en el archivo 'factura_cafeteria.txt'.\n";
    remove("carrito.txt");
}

// Código para la función BuscarProducto, permite al usuario buscar un producto por nombre en el menú de la cafetería y muestra su precio si se encuentra.
void BuscarProducto()
{
    string nombre[6] = {"Pupusas", "Jugo Natural", "Fruta", "Plato del Día", "Gaseosa", "Botella de Agua"};
    float precio[6] = {1.00, 1.50, 1.50, 4.00, 1.00, 0.80};
    string buscar;
    bool encontrado = false;
    char agregar;

    do
    {
        cout << "Ingrese el nombre del producto a buscar: ";
        cin.ignore();
        getline(cin, buscar);

        for (int i = 0; i < 6; i++)
        {
            if (nombre[i] == buscar)
            {
                cout << "Producto encontrado: " << nombre[i] << " - Precio: $" << precio[i] << endl;
                encontrado = true;
                break;
            }
        }
        if (!encontrado)
        {
            cout << "Producto no encontrado en el menu.\n";
        }

        cout << "¿Deseas buscar otro producto? (s/n): ";
        cin >> agregar;

    } while (agregar == 's' || agregar == 'S');
}