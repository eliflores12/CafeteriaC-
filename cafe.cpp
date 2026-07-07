#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "funcioneselias.cpp"

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    int opcion;

    // Menu principal estructurado correctamente
    do
    {
        cout << "\n===== SISTEMA DE CAFETERIA UCA =====\n";
        cout << "1. Mostrar Menu de Productos y Comprar\n";
        cout << "2. Ver Carrito de Compras\n";
        cout << "3. Modificar Cantidad de un Producto\n";
        cout << "4. Cancelar Compra (Vaciar Carrito)\n";
        cout << "5. Finalizar Compra y Generar Factura\n";
        cout << "6. Buscar Producto\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            menuCompra();
            break;

        case 2:
            mostrarCarrito();
            break;

        case 3:
            modificarCompra();
            break;

        case 4:
            cancelarCompra();
            break;

        case 5:
            generarFactura();
            break;

        case 6:
            BuscarProducto();
            break;
            

        case 7:
            cout << "Gracias por visitar la cafeteria UCA.\n";
            break;

        

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 7);

    return 0;
}