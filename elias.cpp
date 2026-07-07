#include "funcioneselias.cpp"
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
                // Pasamos los datos fijos a la funcion encargada del archivo
                switch (comprar)
                {
                case 1: agregarAlCarrito(1, "Pupusas", 1.00, cant); break;
                case 2: agregarAlCarrito(2, "Jugo Natural", 1.50, cant); break;
                case 3: agregarAlCarrito(3, "Fruta", 1.50, cant); break;
                case 4: agregarAlCarrito(4, "Plato del dia", 4.00, cant); break;
                case 5: agregarAlCarrito(5, "Gaseosa", 1.00, cant); break;
                case 6: agregarAlCarrito(6, "Botella de agua", 0.80, cant); break;
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

/*
    FUNCION: agregarAlCarrito()
    Busca si el producto ya existe en el carrito.txt para sumar la cantidad,
    o lo añade al final si es un producto nuevo. Usa la logica de archivo temporal.
*/

void agregarAlCarrito(int cod, string nom, float prec, int cantNueva)
{
    ifstream archivo("carrito.txt");
    ofstream temp("temp.txt");
    char separador;
    Producto p;
    bool encontrado = false;

    // Si el archivo ya existe, leemos los registros actuales
    if (archivo.is_open())
    {
        while (archivo >> p.codigo >> separador)
        {
            getline(archivo, p.nombre, ';');
            archivo >> p.precio >> separador >> p.cantidad;
            archivo.ignore(); // Limpia el salto de linea

            if (p.codigo == cod)
            {
                p.cantidad += cantNueva; // Si ya estaba, sumamos la cantidad
                encontrado = true;
            }
            
            // Guardamos en el archivo temporal con el formato de delimitadores
            temp << p.codigo << ";" << p.nombre << ";" << p.precio << ";" << p.cantidad << endl;
        }
        archivo.close();
    }

    // Si es un producto que no estaba en el carrito, se escribe como nuevo registro
    if (!encontrado)
    {
        temp << cod << ";" << nom << ";" << prec << ";" << cantNueva << endl;
    }
    temp.close();

    // Reemplazamos el archivo original por el temporal
    remove("carrito.txt");
    rename("temp.txt", "carrito.txt");

    cout << "Agregado al carrito correctamente.\n";
}
/*
    FUNCION: mostrarCarrito()
    Lee el archivo carrito.txt utilizando el formateo de punto y coma
    e imprime los registros calculando el total acumulado.
*/
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

    // Mismo patron de lectura con separadores que usamos en buscarJuego
    while (archivo >> p.codigo >> separador)
    {
        getline(archivo, p.nombre, ';');
        archivo >> p.precio >> separador >> p.cantidad;
        archivo.ignore();

        float subtotal = p.precio * p.cantidad;
        total += subtotal;

        cout << p.codigo << "\t" << p.nombre << "\t$" << p.precio << "\t" << p.cantidad << "\t$" << subtotal << endl;
    }
    archivo.close(); // El .close infaltable

    cout << "-----------------------------------------------\n";
    cout << "Total acumulado a pagar: $" << total << endl;
    cout << "===============================================\n";
    
}

/*
    FUNCION: modificarCompra()
    Permite cambiar la cantidad de un producto específico en el carrito
    buscándolo por su código.
*/
void modificarCompra()
{
    int codigoBuscar, nuevaCantidad;
    cout << "\nIngrese el codigo del producto que desea modificar: ";
    cout << "Codigo: \n"; 
        cout << "1) Pupusas \n";
        cout << "2) Jugo Natural \n";
        cout << "3) Fruta \n";
        cout << "4) Plato del dia \n";
        cout << "5) Gaseosa \n";
        cout << "6) Botella de agua \n";
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

        // Solo se guarda en el archivo si la cantidad es mayor a cero
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
        cout << "El codigo de producto no esta en el carrito.\n";
}


/*
    FUNCION: cancelarCompra()
    Borra físicamente el archivo del carrito, lo cual vacía los datos almacenados.
*/
void cancelarCompra()
{
    ifstream archivo("carrito.txt");
    if (archivo.is_open())
    {
        archivo.close();
        remove("carrito.txt");
        cout << "\nCompra cancelada. El carrito se ha vaciado por completo.\n";
    }
    else
    {
        cout << "\nNo hay ninguna compra activa para cancelar.\n";
    }
}

/*
    FUNCION: generarFactura()
    Crea un reporte final en un archivo de texto independiente,
    muestra el total definitivo y vacía el archivo del carrito de compras.
*/
void generarFactura()
{
    ifstream archivo("carrito.txt");
    char separador;
    Producto p;
    float total = 0.0;

    if (!archivo.is_open())
    {
        cout << "\nNo hay productos en el carrito para facturar.\n";
        return;
    }

    // Se escribe la factura final en un archivo de salida independiente
    ofstream factura("factura_cafeteria.txt", ios::app);

    factura << "\n=========================================\n";
    factura << "          FACTURA CAFETERIA UCA          \n";
    factura << "=========================================\n";

    cout << "\n===== PROCESANDO FACTURACION =====\n";

    while (archivo >> p.codigo >> separador)
    {
        getline(archivo, p.nombre, ';');
        archivo >> p.precio >> separador >> p.cantidad;
        archivo.ignore();

        float subtotal = p.precio * p.cantidad;
        total += subtotal;

        cout << "total a pagar: $" << total << endl;
        //descuento para trabajadores de la UCA
        cout<< "Es usted trabajador de la UCA? (1=si, 2=no): \n"; 
        int esTrabajador;
        cin >> esTrabajador;
        if (esTrabajador == 1)
        {
            int codigotrabajador;
        cout<< "Ingrese su codigo de trabajador: \n";
        cin >> codigotrabajador;
        while (codigotrabajador != 6767)
        {
            cout << "Codigo de trabajador invalido.\n";
            cout<< "Ingrese su codigo de trabajador: \n";
            cin >> codigotrabajador;
        }
        cout << "Codigo de trabajador valido,descuento 10%.\n";
        float descuento = 0.0;
         descuento = total * 0.10;
         total -= descuento;
        cout << "descuento aplicado con exito, su total a pagar es: $" << total << endl;
        } else if (esTrabajador == 2)
        {
            cout << "No se aplicara descuento.\n";
        } else {
            cout << "Opcion invalida, no se aplicara descuento.\n";
        }
        

        int MetododePago;   

        cout << "Seleccione el metodo de pago:\n";
        cout << "1. Efectivo\n";
        cout << "2. Tarjeta \n";
        cin >> MetododePago;


        if (MetododePago == 1)
{
        float montoEntregado;

        cout << "Ingrese el monto entregado: $";
        cin >> montoEntregado;

        while (montoEntregado < total)
        {
        cout << "El monto ingresado es insuficiente.\n";
        cout << "Ingrese nuevamente el monto: $";
        cin >> montoEntregado;
        }

        float cambio = montoEntregado - total;

        cout << "Cambio: $" << cambio << endl;

        factura << "Metodo de pago: Efectivo\n";
        factura << "Monto entregado: $" << montoEntregado << endl;
        factura << "Cambio: $" << cambio << endl;
    }  else if (MetododePago == 2)
      {
        cout << "Pago realizado con tarjeta.\n";
        cout << "Gracias por su compra.\n";
      }

        factura << p.nombre << " x" << p.cantidad << " \tSubtotal: $" << subtotal << endl;
    }
    archivo.close();

    factura << "-----------------------------------------\n";
    factura << "TOTAL FINAL PAGADO: $" << total << endl;
    factura << "=========================================\n";
    factura.close();

    cout << "Factura generada con éxito en el archivo 'factura_cafeteria.txt'.\n";

    // Al concluir la transacción, removemos el carrito actual
    remove("carrito.txt");
}

void BuscarProducto()
{
    string nombre [6] = {"Pupusas", "Jugo Natural", "Fruta", "Plato del Día", "Gaseosa", "Botella de Agua"};
    float precio [6] = {1.00, 1.50, 1.50, 4.00, 1.00, 0.80};
    string buscar;
    bool encontrado = false;

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
}
