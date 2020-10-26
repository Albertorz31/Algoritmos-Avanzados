#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct movimientos{
	char movimiento[15];
	struct movimientos *siguiente;
}Movimientos;

int validarEntradas(int argc,char** argv);
Movimientos* backtrackingI(int puzzle[][3],int mantMaxima,int iteracion,Movimientos* movFinal);
Movimientos* crearFinal(Movimientos* inicio,Movimientos* final);
Movimientos* backtracking(int puzzle[][3],Movimientos* movInicial,int mantMaxima,int iteracion,Movimientos* movFinal,int puzzle2[][3]);
void reiniciarMovimientos(Movimientos* inicio,int iteracion);
int compararPuzzleA(int puzzle1[][3],int puzzle2[][3]);
void agregarMovimiento(Movimientos* inicio,Movimientos* nuevo);
int obtenerLargo(Movimientos* inicio);
int comprobarPuzzles(int puzzle[][3]);
int obtenerCantFichasDes(int puzzle[][3]);
int obtenerCaminoM(int puzzle[][3]);
void liberarMemoria(Movimientos* inicio);
void escribirArchivo(Movimientos* inicio,FILE* solucion);
void printCurrent(int puzzle[][3],int iteracion,int mantMaxima);
