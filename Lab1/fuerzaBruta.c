#include "funciones.h"


///FUNCION MAIN////
//entrada: se ingresa el archivo de entrada y el nombre del archivo de salida
//Funcion: guarda las coordenadas iniciales del archivo (si es que hay, las agrega a una lista enlazada para luego ir al metodo de fuerza bruta
//Salida: Escribe en el archivo de salida la lista enlazada final con las posiciones de las sucursales
int main(int argc,char **argv){
	char linea[10];
	int **matriz;
	int count=0,filas,columnas,cant;
	int colum,fil;
	Sucursales *sucur;
	//Se lee el codigo de la entrada
	FILE* archivo;
	archivo= fopen("entrada.in","r");
	Sucursales *inicio=NULL;
	Sucursales *final=NULL;
	
	//En el caso de que el archivo no exista
	if(archivo == NULL){
		printf("No se ha encontrado el archivo\n");
		exit(0);
	}
	
	while(!feof(archivo)){
		if(count==0){
			fscanf(archivo,"%s",linea);
			filas=atoi(linea);
			fscanf(archivo,"%s",linea);
			columnas=atoi(linea);
			count++;
		}else if(count==1){
			fscanf(archivo,"%s",linea);
			cant=atoi(linea);
			count++;
		}else{
			fscanf(archivo,"%s",linea);
			fil=atoi(linea);
			sucur=(Sucursales*)malloc(sizeof(Sucursales));
			sucur->fila=fil;
			fscanf(archivo,"%s",linea);
			colum=atoi(linea);
			sucur->columna=colum;
			sucur->siguiente=NULL;
			if(inicio==NULL){
				inicio=sucur;
			}else{
				agregarSucursal(inicio,sucur);
			}
			
		}
	}
	fclose(archivo);
	matriz=crearMatriz(filas,columnas,inicio);	
	//imprimir(matriz,filas,columnas);
	matriz=bruteForce(matriz,filas,columnas,inicio,cant);
	Sucursales *sucur2;
	int i,j;
	for(i=0;i<filas;i++){
		for(j=0;j<columnas;j++){
			if(matriz[i][j]==1){
				sucur2=(Sucursales*)malloc(sizeof(Sucursales));
				sucur2->fila=i;
				sucur2->columna=j;
				sucur2->siguiente=NULL;
				if(final==NULL){
					final=sucur2;
				}else{
					agregarSucursal(final,sucur2);
				}
			}
		}
	}
	escribirArchivo(final,matriz,filas,columnas);
	liberarMemoria(inicio);
	liberarMemoria(final);
	printf("Archivo Creado\n");
	return 0;	
}


//Entrada: lista enlazada
//Funcion: libera la memoria 
void liberarMemoria(Sucursales* inicio){
	Sucursales* aux;
	while(inicio!=NULL){
		aux=inicio;
		inicio=inicio->siguiente;
		free(aux);
	}
}


//Entrada: lista enlazada final, matriz final con el largo y ancho de la matriz
//Funcion: crea el archivo de salida
void escribirArchivo(Sucursales *inicio,int** matriz,int filas,int columnas){
	int largo=0;
	Sucursales* aux;
	aux=inicio;
	while(aux!=NULL){
		largo++;
		aux=aux->siguiente;
	}
	//Solucion
	FILE* solucion;
	solucion = fopen("solucion.out","w");
	fprintf(solucion,"%i",largo);
	fprintf(solucion,"\n");
	aux=inicio;
	while(aux!=NULL){
		fprintf(solucion,"%i-%i ||",aux->fila,aux->columna);
		aux=aux->siguiente;
	}
	fprintf(solucion,"\n");
	int i,j;
	for(i=0;i<filas;i++){
		for(j=0;j<columnas;j++){
			if(matriz[i][j]==0){
				fprintf(solucion,"- ");
			}else if(matriz[i][j]==1){
				fprintf(solucion,"X ");
			}
		}
		fprintf(solucion,"\n");
	}
	fclose(solucion);
}

//Entrada: lista enlazada y nodo a agregar
//Funcion: Funcionalidad basica de lista, la cual es agregar nodo a la lista
void agregarSucursal(Sucursales* inicio,Sucursales* sucur){
	Sucursales* aux;
	Sucursales* ultimo;
	aux=inicio;
	ultimo=inicio;
	while(aux!=NULL){
		ultimo=aux;
		aux=aux->siguiente;
	}
	ultimo->siguiente=sucur;
	sucur->siguiente=NULL;
}

//Entrada: lista enlazada y ancho y largo de la matriz
//Funcion: crear matriz con las posiciones incluidas en la lista enzalada
//Salida: matriz con las posiciones de las sucursales
int** crearMatriz(int filas,int columnas,Sucursales* inicio){
	Sucursales* aux;
	int** mat;
	int i,j,val=0;
	aux=inicio;
	mat=(int**)malloc((filas)*sizeof(int*));
	if(mat==NULL){
		printf("No se ha podido reservar memoria\n");
		exit(1);
	}
	for(i=0;i<filas;i++){
		mat[i]= (int*)malloc((columnas)*sizeof(int));
		if (mat[i] == NULL){
			printf ("No se ha podido reservar memoria ");
		    exit(1);
		}		
	}
	if(inicio==NULL){
		for(i=0;i<filas;i++){
			for(j=0;j<columnas;j++){
				mat[i][j]=0;
			}
		}
	}else{
		for(i=0;i<filas;i++){
			for(j=0;j<columnas;j++){
				while(aux!=NULL){
					if(aux->fila==i && aux->columna==j){
						mat[i][j]=1;
						val=1;
						break;
					}else{
						aux=aux->siguiente;
					}
				}if(val==0){
					mat[i][j]=0;
				}
				aux=inicio;
				val=0;
			}
		}	
	}
	return mat;	
}

////////////////////////////////METODO FUERZA BRUTA////////////////////////////////////////////


//Entradas: matriz inicial, ancho y largo de la matriz, lista enlazada con sucursales iniciones y cantidad de sucursales iniciales
//Funcion: Realiza el metodo de fuerza bruta, comienza verificando posicion por posicion de la matriz, si esa posicion cumple con las restricciones iniciales
//va vrificando con las sucursales que se encuentran en la lista inicial, en el caso de que en la posicion se pueda ingresar una sucursal ingresa el metodo recusivo
//comenzarArbol que se podria conciderar como la parte dos del metodo.
//Salida: matriz con las posiciones de las sucursales finales
int** bruteForce(int **matriz,int filas,int columnas,Sucursales* inicio,int cantidadS){
	Sucursales* aux;
	Sucursales* final=NULL;
	int **matriz2,val=0;
	int noPuede=1,largo,largoFinal=0,entreUna=0;
	aux=inicio;
	int salir=0;
	
	//Si no se contiene sucursales iniciales se parte con la matriz vacia, y se realiza una fuerza bruta solo para este caso 
	if(cantidadS==0){
		matriz2=fuerzaBrutaInicial(matriz,filas,columnas,inicio,cantidadS,final);
	}
	
	//Si contiene sucursales iniciales realiza fuerza bruta actual
	else{
		val=1;
		int i,j;
		for(i=0;i<filas;i++){
			for(j=0;j<columnas;j++){
				aux=inicio;
				while(aux!=NULL && salir==0){
					if(i==aux->fila || j==aux->columna){
						noPuede=0;
						salir=1;
					}else if(comprobarDiagonal(i,j,filas,columnas,aux)==1){
						noPuede=0;
						salir=1;
					}
					aux=aux->siguiente;
				}
				if(noPuede==1){
					entreUna=1;
					final=comenzarArbol(inicio,i,j,filas,columnas,cantidadS,largoFinal,final);
					reiniciarSucursales(inicio,cantidadS);
				}
				salir=0;
				noPuede=1;
				printCurrent(final,filas,columnas);
			}
		}
	}
	if(val==1){
		matriz2=crearMatriz(filas,columnas,final);
	}
	if(entreUna==0 && val==1){
		matriz2=matriz;
	}
	return matriz2;
}

//Entrada: matriz inicial, largo y ancho de la matriz, lista enlazada inicial, lista enlazada final
//Funcion: realiza lo mismo que la funcion anterior solo que esta es para el caso donde no hay sucursales iniciales
//Salida: matriz final
int** fuerzaBrutaInicial(int** matriz,int filas,int columnas,Sucursales* inicio,int cantidadS,Sucursales* final){
	int i,j;
	int largo,largoFinal;
	int** matriz2;
	Sucursales* sucur;
	cantidadS++;
	for(i=0;i<filas;i++){
		for(j=0;j<columnas;j++){
			sucur=(Sucursales*)malloc(sizeof(Sucursales));
			sucur->fila=i;
			sucur->columna=j;
			sucur->siguiente=NULL;
			final=comenzarArbol(sucur,i,j,filas,columnas,cantidadS,largoFinal,final);
			printCurrent(final,filas,columnas);
		}
	}
	matriz2=crearMatriz(filas,columnas,final);
	return matriz2;
}


//Entrada: lista enlazada y cantidad de sucursales
//Funcion: para poder ir actualizando la lista dependiendo en que nivel del arbol vaya, se necesita ir actualizando la lista, es decir,
//Si se esta en el nivel 4 de recorrido y la lista tiene largo 5, se tiene que borrar el ultimo elemento
void reiniciarSucursales(Sucursales* inicio,int cantidadS){
	int n=1;
	Sucursales* aux;
	Sucursales* aux2;
	aux=inicio;
	while(n<=cantidadS){
		if(n==cantidadS){
			aux->siguiente=NULL;
			n++;
		}else{
			aux=aux->siguiente;
		    n++;
		}	
	}
}


//Entrada: lista enlazada,posicion i y j que se verifica , largo y ancho de la matriz, cantidad de sucursales que se lleva, largo final, lista enlazada final
//Funcion: Segunda parte de la fuerza bruta, esta incia cuando se tiene una posicion que cumple con las restricciones, esta funcion es recursiva ya que si se
//cumple denuevo los casos inicales se llama a su misma para realizar lo mismo. Es fuerza bruta ya que verifica muchas veces las misma posiciones que no se pueden
//Salida: si se llega a una hoja del arbol devolvera la lista final y asi sucesuvamente hasta subir todos los niveles del arbol.
Sucursales* comenzarArbol(Sucursales* inicio,int i,int j,int filas,int columnas,int cantidadS,int largoFinal,Sucursales* final){
	Sucursales* aux;
	Sucursales* nuevoNodo;
	nuevoNodo=(Sucursales*)malloc(sizeof(Sucursales));
	nuevoNodo->fila=i;
	nuevoNodo->columna=j;
	nuevoNodo->siguiente=NULL;
	aux=inicio;
	int largo;
	int noPuede=1,salir=0;
	agregarSucursal(inicio,nuevoNodo);
	cantidadS++;
	for(i=0;i<filas;i++){
		for(j=0;j<columnas;j++){
			aux=inicio;
			while(aux!=NULL && salir==0){
				if(i==aux->fila || j==aux->columna){
					noPuede=0;
					salir=1;
				}else if(comprobarDiagonal(i,j,filas,columnas,aux)==1){
					noPuede=0;
					salir=1;
				}
				aux=aux->siguiente;
			}
			if(noPuede==1){
				final=comenzarArbol( inicio,i,j,filas,columnas,cantidadS,largoFinal,final);	
				reiniciarSucursales(inicio,cantidadS);		
			}
			salir=0;
			noPuede=1;
		}
	}
	largo=obtenerLargo(inicio);
	largoFinal= obtenerLargoFinal(final);
	if(largo>=largoFinal){
		largoFinal=largo;
		final=NULL;
		final=crearFinal(inicio,final);
	}
	return final;
}


//Funciones hacen lo mismo, calculan largo de lista, me di cuenta despues XD

int obtenerLargo(Sucursales* inicio){
	Sucursales* aux;
	aux=inicio;
	int largo=0;
	while(aux!=NULL){
		largo++;
		aux=aux->siguiente;
	}
	return largo;
}

int obtenerLargoFinal(Sucursales* final){
	Sucursales* aux;
	aux=final;
	int count=0;
	while(aux!=NULL){
		count++;
		aux=aux->siguiente;
	}
	return count;
}


//Entradas: lista enlazada actual, lista enlazada final
//Funcion: transforma la lista enzalada actual en la lista final 
//Salida: lista final
Sucursales* crearFinal(Sucursales* inicio,Sucursales* final){
	Sucursales* aux;
	Sucursales* sucur;
	aux=inicio;
	while(aux!=NULL){
		sucur=(Sucursales*)malloc(sizeof(Sucursales));
		sucur->fila=aux->fila;
		sucur->columna=aux->columna;
		sucur->siguiente=NULL;
		if(final==NULL){
			final=sucur;
		}else{

			agregarSucursal(final,sucur);
		}
		aux=aux->siguiente;
	}
	return final;
}

//Entradas: posiciones a evaluar i y j, ancho y largo de la matriz, y lista enlazada con posiciones inicales
//Funcion: comprueba si la posicion a evaluar es diagonal de alguna de las sucursales de la lista enzalada
//Salida: 0: no es diagonal -  1: si es diagonal
int comprobarDiagonal(int i,int j,int filas,int columnas,Sucursales* sucur){
	int n=1;
	if(j<sucur->columna && i>sucur->fila){
		while(n!=1000){
			if(sucur->fila+n==i && sucur->columna-n==j){
				return 1;
			}else{
				n++;
				if(sucur->fila+n > filas || sucur->columna-n < 0){
					n=1000;
				}
			}
		}
	}else if(j<sucur->columna && i<sucur->fila){
		while(n!=1000){
			if(sucur->fila-n==i && sucur->columna-n==j){
				return 1;
			}else{
				n++;
				if(sucur->fila-n < 0 || sucur->columna-n < 0){
					n=1000;
				}
			}
		}
	}else if(j>sucur->columna && i<sucur->fila){
		while(n!=1000){
			if(sucur->fila-n==i && sucur->columna+n==j){
				return 1;
			}else{
				n++;
				if(sucur->fila+n < 0 || sucur->columna+n > columnas){
					n=1000;
				}
			}
		}
	}else if(j>sucur->columna && i>sucur->fila){
		while(n!=1000){
			if(sucur->fila+n==i && sucur->columna+n==j){
				return 1;
			}else{
				n++;
				if(sucur->fila+n > filas || sucur->columna+n >columnas){
					n=1000;
				}
			}
		}
	}
	return 0;		
}



////////////////PRINT CURRENT//////////////////////////

//entrada: lista enlazada, ancho y largo de la matrirz
//Funcion: imprime la matriz de la lista enlazada
void printCurrent(Sucursales* final,int filas,int columnas){
	#ifdef DEBUG
	int **matriz;
	Sucursales* aux;
	aux=final;
	while(aux!=NULL){
		printf("%i-%i ||",aux->fila,aux->columna);
		aux=aux->siguiente;
	}
	printf("\n");
	matriz=crearMatriz(filas,columnas,final);
	imprimir(matriz,filas,columnas);
	while(getchar() != '\n');
	printf("Enter para continuar...\n");
	#endif
}

//Funcion que muestra por pantalla la matriz
void imprimir(int **matriz,int filas,int columnas){
	int i,j;
	for(i=0;i<filas;i++){
		for(j=0;j<columnas;j++){
			if(matriz[i][j]==0){
				printf("- ");
			}else if(matriz[i][j]==1){
				printf("X ");
			}
		}
		printf("\n");
	}
}






