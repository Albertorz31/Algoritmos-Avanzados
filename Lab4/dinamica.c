#include "funciones.h"

///FUNCION MAIN////
//Entrada: Se ingresa el archivo de entrada, junto con el nombre del archivo de salida
//Funcion: guarda los valores del archivo de entrada en una lista para despues llamar a la funcion de programacion dinamica
//Salida: Cuando se retorna la lista con las inversiones de mayor beneficio
int main(int argc,char **argv){
	char linea[1000];
	int count=0,capital,cantInv,costo,utilidad;
	Inversiones *inv;

	if(!validarEntradas(argc,argv)){
		return 0;
	}
	FILE* archivo;
	FILE* archivoS;
	archivo= fopen(argv[1],"r");
	archivoS=fopen(argv[2],"w");
	Inversiones *inicio=NULL;
	Inversiones* inversionFinal=NULL;

	while(!feof(archivo)){
		if(count==0){
			fscanf(archivo,"%s",linea);
		    capital=atoi(linea);
		    count++;
		}else if(count==1){
			fscanf(archivo,"%s",linea);
		    cantInv=atoi(linea);
		    count++;
		}else{
			fscanf(archivo,"%s",linea);
			costo=atoi(linea);
			fscanf(archivo,"%s",linea);
			utilidad=atoi(linea);
			inv=(Inversiones*)malloc(sizeof(Inversiones));
			inv->costo=costo;
			inv->utilidad=utilidad;
			inv->siguiente=NULL;
			if(inicio==NULL){
				inicio=inv;
			}else{
				agregarInversion(inicio,inv);
			}
			count++;
		}
	}
	fclose(archivo);


	//Se le da un valor a cada inversion de 1 hasta el largo de la lista
	int iteracion=1;

    Inversiones* lista1=NULL;

	inversionFinal=dinamica(inicio,capital,lista1,iteracion);
	escribirArchivo(inversionFinal,archivoS);

	//Se libera memoria
	liberarMemoria(inversionFinal);
	return 0;
}

//Entrada: los archivos de entrada
//Funcion: verificar que se ingresen los parametros correctos de entrada
//Salida: 0 o 1 dependiendo si son correctos los parametros de entradas
int validarEntradas(int argc,char** argv){
	if(argc==1){
		printf("Error: Faltan parametros en la linea de comando\n");
		return 0;
	}
	if(argc==2){
		printf("Error: Faltan parametros en la linea de comando\n");
		return 0;
	}
	if(argc > 3){
		printf("Error: Demasiado parametros en la linea de comando\n ");
	}
	if(existeArchivo(argv[1])==0){
    	printf("Error: El archivo de entrada no existe.\n");
        return 0;
    }
}

//Entrada: char con nombre del archivo
//Funcion: comprueba si existe el archivode entra
//Salida: 1 o 0 si existe
int existeArchivo(char* nombre){
   FILE* archivo =NULL;
   archivo = fopen(nombre,"r");
   if(archivo==NULL)
      return 0; 
   else{
      fclose(archivo);
      return 1;
   } 
   return 0;
}


//Entrada: lista enlazada y nodo a agregar
//Funcion: Funcionalidad basica de lista, la cual es agregar nodo a la lista
void agregarInversion(Inversiones* inicio,Inversiones* inv){
	Inversiones* aux;
	Inversiones* ultimo;
	aux=inicio;
	ultimo=inicio;
	while(aux!=NULL){
		ultimo=aux;
		aux=aux->siguiente;
	}
	ultimo->siguiente=inv;
	inv->siguiente=NULL;
}


//Entrada: se ingresa una lista con las inversiones, el capital y en que iteracion va
//Funcion: funcion recursiva que realiza programacion dinamica, ya que realiza un arbol binario
//Donde en cada nivel del arbol va comparando los 2 nodos y cual es mejor y ese retornará
//Entonces en el nodo raiz elige cual hijo es mejor el izquierdo o derecho
//Salida: Lista enlazada con la inversion de mayor beneficio
Inversiones* dinamica(Inversiones* inicio,int capital,Inversiones* lista,int iteracion){
	Inversiones* aux;
	Inversiones* listaFinal;
	Inversiones* lista1=NULL;
	Inversiones* lista2=NULL;
	Inversiones* listaAux=NULL;

    //Lista auxiliar para guarda lista inicial
    listaAux=guardarLista(lista,listaAux);
    
	aux=inicio;

	int capitalNueva;

    //Si el elemento de la lista no es el ultimo sigue
	if(aux->siguiente!=NULL){
		aux=aux->siguiente;

		//Rama izquierda del nodo
		lista1 = dinamica(aux,capital,lista,iteracion+1);
		
		if(inicio->costo <= capital){
	        capitalNueva= capital- inicio->costo;
	        Inversiones* nuevoNodo;
	        nuevoNodo=(Inversiones*)malloc(sizeof(Inversiones));
			nuevoNodo->costo=inicio->costo;
			nuevoNodo->utilidad=inicio->utilidad;
			nuevoNodo->siguiente=NULL;
			if(listaAux==NULL){
				listaAux=nuevoNodo;
			}else{
				agregarInversion(listaAux,nuevoNodo);
			}

			//Rama derecha del nodo
			lista2 = dinamica(aux,capitalNueva,listaAux,iteracion+1);
	    }
	}else{
		//Cuando se llega a una hoja del arbol
		if(lista==NULL && inicio->costo < capital){
			lista=(Inversiones*)malloc(sizeof(Inversiones));
			lista->utilidad=aux->utilidad;
			lista->costo=aux->costo;
			lista->siguiente=NULL;
			return lista;
		}else if(lista !=NULL){
			if(inicio->costo <= capital){
				lista2=(Inversiones*)malloc(sizeof(Inversiones));
				lista2->utilidad=aux->utilidad;
				lista2->costo=aux->costo;
				lista2->siguiente=NULL;
				agregarInversion(lista,lista2);
				return lista;
			}else{
				return lista;
			}
		}
	}
	
    //Se comparan las dos ramas y cual es la mejor
	if(lista2==NULL){
		return lista1;
	}
    
    //Se libera memoria del peor
	if(calcularUtilidad(lista1) > calcularUtilidad(lista2)){
		listaFinal = lista1;
		liberarMemoria(lista2);
		
	}else{
		listaFinal = lista2;
		liberarMemoria(lista1);	
	}
	printCurrent(listaFinal);
	return listaFinal;
}


//Entrada: lista enlazada
//Funcion: libera la memoria 
void liberarMemoria(Inversiones* inicio){
	Inversiones* aux;
	while(inicio!=NULL){
		aux=inicio;
		inicio=inicio->siguiente;
		free(aux);
	}
}


//Entrada: lista enlazada y nodo actual
//Funcion: se suman costos de la lista mas el del actual
//Salida: entero con la suma total
int verificarCosto(Inversiones* lista1, Inversiones* actual){
	Inversiones* aux;
    aux=lista1;
    int costo=0;

    while(aux!=NULL){
    	costo = costo + aux->costo;
    	aux=aux->siguiente;
    }

    costo = costo + actual->costo;

    return costo;
}


//Entrada: lista enlazada
//Funcion: Se calcula la utilidad todas sumando todos los nodos
//Salida: entero con la suma de las utilidades
int calcularUtilidad(Inversiones* lista){
	Inversiones* aux;
	aux=lista;
	int utilidad=0;

	while(aux!=NULL){
		utilidad=utilidad+ aux->utilidad;
		aux=aux->siguiente;
	}

	return utilidad;
}


//Entrada: listas enlazadas
//Funcion: copia una lista en la otra
//Salida: lista auxiliar copiada
Inversiones* guardarLista(Inversiones* lista,Inversiones* listaAux){
	Inversiones* aux;
	Inversiones* inv;
	aux=lista;
	while(aux!=NULL){
		inv=(Inversiones*)malloc(sizeof(Inversiones));
		inv->costo=aux->costo;
		inv->utilidad=aux->utilidad;
		inv->siguiente=NULL;
		if(listaAux==NULL){
			listaAux=inv;
		}else{
			agregarInversion(listaAux,inv);
		}
		aux=aux->siguiente;
	}
	return listaAux;
}


//Entrada: lista enlazada con las inversiones, y el nombre del archivo de salida
//Funcion: crea el archivo de salida
void escribirArchivo(Inversiones* inicio,FILE* solucion){
	Inversiones* aux;
	aux=inicio;
	int capitalInvertido=0,beneficio=0;

	while(aux!=NULL){
		capitalInvertido=capitalInvertido+aux->costo;
		beneficio=beneficio+aux->utilidad;
		aux=aux->siguiente;
	}
	fprintf(solucion, "%i %i\n",capitalInvertido,beneficio);
	aux=inicio;
	while(aux!=NULL){
		fprintf(solucion,"%i\n",aux->costo);
		aux=aux->siguiente;
	}
	fclose(solucion);
	printf("Archivo Creado\n");
}


/////////////////////////////PRINT CURRENT//////////////////////////////////////

//entrada: lista enlazadacon con la inversiones de mayor beneficio actual
//Funcion: Muestra por patalla las inversiones que hasta el momento son las de mayor beneficio
//muestra el costo y la utilidad de cada una 
void printCurrent(Inversiones* inicio){
	#ifdef DEBUG
	Inversiones* aux;
	aux=inicio;

    printf("Inversiones de mayor beneficio actuales\n");
	while(aux!=NULL){
		printf("costo: %i utilidad: %i\n",aux->costo,aux->utilidad);
		aux=aux->siguiente;
	}
	while(getchar() != '\n');
	printf("Enter para continuar...\n\n");
	#endif
}