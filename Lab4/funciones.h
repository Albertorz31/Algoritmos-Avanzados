#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//ESTRUCTURA DEL PROGRAMA
typedef struct inversiones{
	int costo;
	int utilidad;
	struct inversiones *siguiente;
}Inversiones;


////////////////FUNCIONES DEL PROGRAMA ////////////////////
int validarEntradas(int argc,char** argv);
int existeArchivo(char* nombre);
void agregarInversion(Inversiones* inicio,Inversiones* inv);
void ordenarInversiones(Inversiones* inicio);
int obtenerLargo(Inversiones* inicio);
Inversiones* dinamica(Inversiones* inicio,int capital,Inversiones* lista,int iteracion);
void liberarMemoria(Inversiones* inicio);
int verificarCosto(Inversiones* lista1, Inversiones* actual);
int calcularUtilidad(Inversiones* lista);
Inversiones* guardarLista(Inversiones* lista,Inversiones* listaAux);
void escribirArchivo(Inversiones* inicio,FILE* solucion);
void printCurrent(Inversiones* inicio);