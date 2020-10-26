#include "funciones.h"

///FUNCION MAIN////
//Entrada: Se ingresa el archivo de entrada, junto con el nombre del archivo de salida
//Funcion: guarda los valores del archivo de entrada en un grafo para luego pasar a la funcion Goloso
//Salida: Cuando se retorna la lista con la ruta que se realiza 
int main(int argc,char **argv){
	grafo G;
	Lista *listaFinal=NULL;
	int i,j,costo,nodoO,nodoD,x,y;
	char linea[10],numeroC[10];
	if(!validarEntradas(argc,argv)){
		return 0;
	}
	FILE* archivo;
	FILE* archivoS;
	archivo= fopen(argv[1],"r");
	archivoS=fopen(argv[2],"w");

	//En el caso de que el archivo no exista
	if(archivo == NULL){
		printf("No se ha encontrado el archivo\n");
		exit(0);
	}
	fscanf(archivo,"%s",numeroC);
	G.nodos=atoi(numeroC)+1;
	G.vertice=(nodo*)malloc(sizeof(nodo)*G.nodos);
	G.adj = (double**)malloc(sizeof(double*)*G.nodos);
	for(i=0;i < G.nodos;i++){
		G.adj[i] = (double*)malloc(sizeof(double)*G.nodos);
	}
	for(i=0;i<G.nodos;i++){
		G.vertice[i].numero=i;
		G.vertice[i].marcado=0;
	}

	for(i=0;i< G.nodos;i++){
		for(j=0;j < G.nodos;j++){
			if(i==0 && j!=0){
				G.adj[i][j]=1;
			}else{
				if(j==0 && i!=0){
					G.adj[i][j]=1;
				}else{
					G.adj[i][j]=0;
				}
			}
		}
	}

	while(!feof(archivo)){
		fscanf(archivo,"%s",linea);
		nodoO=atoi(linea);
		fscanf(archivo,"%s",linea);
		nodoD=atoi(linea);
		fscanf(archivo,"%s",linea);
		costo=atoi(linea);
		for(i=0;i < G.nodos;i++){
			if(G.vertice[i].numero==nodoO){
				x=i;
			}
			if(G.vertice[i].numero==nodoD){
				y=i;
			}

		}
		G.adj[x][y]=costo;
		G.adj[y][x]=costo;
	}
	fclose(archivo);
	listaFinal = greedy(G);
	escribirArchivo(listaFinal,archivoS);

	//Se libera memoria
	liberarMemoria(listaFinal);
	return 0;
}

//Entrada: lista enlazada
//Funcion: libera la memoria 
void liberarMemoria(Lista* inicio){
	Lista* aux;
	while(aux!=NULL){
		aux=inicio;
		inicio=inicio->siguiente;
		free(aux);
	}
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
		return 0;
	}
}


/*
Entrada: Se ingresa el grafo con la informacion de las rutas
Funcion: Funcion la cual realiza el metodo de Goloso quien primero selecciona al azar por cual camino
irse inicialmente (ya que todos valen 1), despues usar el criterio de irse por la ruta mas corta desde ese 
punto, realizará este criterio hasta recorrer todos los nodos del grafo y devolverse a la capital
Salida: Lista enlazada con la ruta que recorre el grafo
*/
Lista* greedy(grafo G){
	Lista* ruta;
	int nodoAleatorio,nodosMarcados=0,ultimoNumero,i,j;
	int minimo,numeroMin;
	ruta=(Lista*)malloc(sizeof(Lista));
	ruta->siguiente=NULL;
	ruta->nodo=0;
	ruta->costo=0;
	G.vertice[0].marcado=1;
	nodosMarcados++;


    //Selecciona al azar el primer nodo por el que se irá de la capital
    //Da igual por cual se vaya, ya que todos tiene costo 1
	srand(time(NULL));
	nodoAleatorio = 1+rand()% (G.nodos-1);
	Lista* nodoInicio;
	nodoInicio=(Lista*)malloc(sizeof(Lista));
	nodoInicio->nodo=nodoAleatorio;
	nodoInicio->costo=1;
	nodoInicio->siguiente=NULL;
	agregarNodo(ruta,nodoInicio);
	G.vertice[nodoAleatorio].marcado=1;
	ultimoNumero=nodoAleatorio;
	nodosMarcados++;

	printCurrent(ruta);


    //Despues de seleccionar el nodo por el cual irse de la capital al azar, se realiza aqui el criterio
    //de Goloso que en este caso, es ir seleccionando el camino minimo posible para ese nodo, esto incluye
    //que no puede meterse por un camino donde el nodo destino ya se haya recorrido
	while(nodosMarcados < G.nodos){
		minimo=0;
		for(j=0;j <G.nodos;j++){
			if(minimo==0){
				if(G.adj[ultimoNumero][j]!=0 && G.vertice[j].marcado!=1){
					minimo= G.adj[ultimoNumero][j];
					numeroMin=j;
				}
			}else{
				if(G.adj[ultimoNumero][j]<minimo && G.adj[ultimoNumero][j]!=0 && G.vertice[j].marcado!=1){
					minimo= G.adj[ultimoNumero][j];
					numeroMin=j;
				}
			}
		}


		Lista* nodoNuevo;
		nodoNuevo=(Lista*)malloc(sizeof(Lista));
		nodoNuevo->nodo=numeroMin;
		nodoNuevo->costo=minimo;
		agregarNodo(ruta,nodoNuevo);
		G.vertice[numeroMin].marcado=1;
		ultimoNumero=numeroMin;
		nodosMarcados++;
		printCurrent(ruta);
	}
	Lista* nodoFinal;
	nodoFinal=(Lista*)malloc(sizeof(Lista));
	nodoFinal->nodo=0;
	nodoFinal->costo=1;
	agregarNodo(ruta,nodoFinal);
	printCurrent(ruta);

	return ruta;
}


//Entrada: lista enlazada y nodo a agregar
//Funcion: Funcionalidad basica de lista, la cual es agregar nodo a la lista
void agregarNodo(Lista* inicio,Lista* nuevo){
	Lista* aux;
	Lista* ultimo;
	aux=inicio;
	ultimo=inicio;
	while(aux!=NULL){
		ultimo=aux;
		aux=aux->siguiente;
	}
	ultimo->siguiente=nuevo;
	nuevo->siguiente=NULL;
}

//Entrada: lista enlazada con la ruta, y el nombre del archivo de salida
//Funcion: crea el archivo de salida
void escribirArchivo(Lista* inicio,FILE* solucion){
	Lista* aux;
	aux=inicio;
	int costoTotal=0;
	while(aux!=NULL){
		costoTotal= costoTotal+ aux->costo;
		aux=aux->siguiente;
	}
	fprintf(solucion, "%i\n",costoTotal);
	aux=inicio;
	while(aux!=NULL){
		if(aux->siguiente!=NULL){
			fprintf(solucion, "%i-",aux->nodo);
		}else{
			fprintf(solucion, "%i",aux->nodo);
		}
		aux=aux->siguiente;
	}
	fclose(solucion);
	printf("Archivo Creado\n");
}


/////////////////////////////PRINT CURRENT//////////////////////////////////////

//entrada: lista enlazadacon la ruta
//Funcion: Muestra por patalla la ruta actual que se lleva, junto con el costo que lleva
void printCurrent(Lista* ruta){
	#ifdef DEBUG
	int costoTotal=0;
	Lista* aux;
	aux=ruta;;
	while(aux!=NULL){
		costoTotal= costoTotal+ aux->costo;
		aux=aux->siguiente;
	}
	aux=ruta;
	printf("El costo actual es: %i\n",costoTotal);
	int numero=0;
	while(aux!=NULL){
		if(numero==0){
			printf("%i",aux->nodo);
		}else{
			printf("-> %i",aux->nodo);
		}
		numero++;
		aux=aux->siguiente;
	}
	while(getchar() != '\n');
	printf("Enter para continuar...\n\n");
	#endif
}


