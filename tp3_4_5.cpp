#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *TiposProductos[] = {"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

struct Producto
{
    int ProductoID;//Numerado en ciclo iterativo
    int Cantidad;// entre 1 y 10
    char *TipoProducto;   // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100
};
struct Cliente
{
    int ClienteID;    // Numerado en el ciclo iterativo
    char *NombreCliente;         // Ingresado por usuario
    int CantidadProductosAPedir; // (aleatorio entre 1 y 5)
    Producto *Productos;         //El tamaño de este arreglo depende de la variable
                                // "CantidadProductosAPedir"
};

void cargarProducto(Producto *pr,int cant){
    for (int i = 0; i < cant; i++)
    {
        (pr+i)->ProductoID=i+1;
        (pr+i)->Cantidad=1+rand()%11;
        (pr+i)->PrecioUnitario=10+rand()%101;
        (pr+i)->TipoProducto=TiposProductos[i];
    }
    
}

void cargarClientes(Cliente * pVector,int cant){
    for (int i = 0; i < cant; i++)
    {
        char s[100];//String auxiliar
        pVector[i].ClienteID=i;
        printf("Ingrese el nombre del cliente: ");

        scanf("%s",s);
        
        (pVector[i].NombreCliente)=(char *)malloc(sizeof(s)*strlen(s));
        strcpy((pVector[i].NombreCliente),s);

        int prodAPedir=rand()%5+1;
        pVector[i].CantidadProductosAPedir=prodAPedir;
        pVector[i].Productos=(Producto *)malloc(sizeof(Producto)*prodAPedir);
        cargarProducto(pVector[i].Productos,prodAPedir);            
    }
    
}
float precioProducto(Producto prod){
    return prod.Cantidad*prod.PrecioUnitario;
}
float mostrarProductos(Producto * pProd,int cant){
    float suma=0;
    for (int i = 0; i < cant; i++)
    {
        printf("\tID del producto: %d\n"\
                "\tCantidad: %d\n"\
                "\tTipo: %s\n"\
                "\tPrecio: %.2f\n\n",           
                pProd[i].ProductoID,pProd[i].Cantidad,
                pProd[i].TipoProducto,pProd[i].PrecioUnitario);
        suma+=precioProducto(pProd[i]);
    }
    return suma;
}
void mostrarClientes(Cliente * pVector,int cant){
    float Total_cliente;
    for (int i = 0; i < cant; i++)
    {
        printf("\nID del Cliente: %d\n"\
               "Nombre: %s\n"\
               "Cantidad de productos: %d\n",
               pVector[i].ClienteID,pVector[i].NombreCliente,
               pVector[i].CantidadProductosAPedir);
        Total_cliente=mostrarProductos(pVector[i].Productos,pVector[i].CantidadProductosAPedir);
        printf("\t\tTotal: %.2f\n",Total_cliente);
    }
    
}

int main(int argc, char const *argv[])
{
    printf("Cuántos clientes va a ingresar?: ");
    int cantClientes;
    scanf("%d", &cantClientes);
    Cliente *pClientes;
    pClientes = (Cliente *)malloc(sizeof(Cliente)*cantClientes);
    cargarClientes(pClientes,cantClientes);
    mostrarClientes(pClientes,cantClientes);
    free(pClientes);
    getchar();
    return 0;
}