#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ESTRUCTURA DEL PROGRAMA
//Cada nodo representa las posiciones de una sucursal y el puntero al siguiente nodo

typedef struct sucursales{
	int fila;
	int columna;
	struct sucursales *siguiente;
	
}Sucursales;

////////////////FUNCIONES DEL PROGRAMA ////////////////////

void agregarSucursal(Sucursales* inicio,Sucursales* sucur);
int ** crearMatriz(int filas,int columnas,Sucursales* inicio);
void imprimir(int **matriz,int filas,int columnas);
int ** bruteForce(int **matriz,int filas,int columnas,Sucursales* inicio,int cantidadS);
Sucursales* comenzarArbol(Sucursales* inicio,int i,int j,int filas,int columnas,int cantidadS,int largoFinal,Sucursales* final);
int comprobarDiagonal(int i,int j,int filas,int columnas,Sucursales* inicio);
int obtenerLargo(Sucursales* inicio);
void reiniciarSucursales(Sucursales* inicio,int cantidadS);
void escribirArchivo(Sucursales *inicio,int** matriz,int filas,int columnas);
int** fuerzaBrutaInicial(int** matriz,int filas,int columnas,Sucursales* inicio,int cantidadS,Sucursales* final);
void liberarMemoria(Sucursales* inicio);
int obtenerLargoFinal(Sucursales* final);
Sucursales* crearFinal(Sucursales* inicio,Sucursales* final);
void printCurrent(Sucursales* final,int filas,int columnas);





