#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Se crea estrutura nodo, la cual contiene su numero, si fue recorrido (marcado).
typedef struct nodo{
	int numero;
	int marcado;
}nodo;


//Lista donde se guardará la ruta que realiza el algoritmo , cada nodo de la lista es un punto junto con el 
//costo de ir a el.
typedef struct lista{
	int nodo;
	int costo;
	struct lista* siguiente;
}Lista;

//Se crea un grafo que representa la conexion entre los puntos, donde cada punto se guardará como nodo, se
//guarda la cantidad de todos y una matriz de adyacencia el cual muestra el costo de ir de un pto. a otro
typedef struct grafo{
	nodo *vertice;
	int nodos;
	double** adj;
}grafo;



//Funciones de programa
int validarEntradas(int argc,char** argv);
Lista* greedy(grafo G);
void agregarNodo(Lista* inicio,Lista* nuevo);
void escribirArchivo(Lista* inicio,FILE* solucion);
void printCurrent(Lista* ruta);
void liberarMemoria(Lista* inicio);


