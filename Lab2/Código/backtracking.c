#include "funciones.h"


///FUNCION MAIN////
//Entrada: Se ingresa el archivo de entrada, junto con el nombre del archivo de salida
//Funcion: guarda los valores del archivo de entrada en una matriz para luego pasar a la funcion backtracking
//Salida: Cuando se retorna la lista con los movimientos del puzle se llama a la funcion que imprime el archivo
int main(int argc,char **argv){
	int puzzleInicial[3][3];
	char linea[10];
	Movimientos *movFinal=NULL;
	int count=0;
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
	
	while(!feof(archivo)){
		fscanf(archivo,"%s",linea);
		if(strcmp(linea,"X")==0){
			puzzleInicial[count][0]=0;
		}else{
			puzzleInicial[count][0]=atoi(linea);
		}
		fscanf(archivo,"%s",linea);
		if(strcmp(linea,"X")==0){
			puzzleInicial[count][1]=0;
		}else{
			puzzleInicial[count][1]=atoi(linea);
		}
		fscanf(archivo,"%s",linea);
		if(strcmp(linea,"X")==0){
			puzzleInicial[count][2]=0;
		}else{
			puzzleInicial[count][2]=atoi(linea);
		}
		count++;
	}
	fclose(archivo);
	
	int mantMaxima;
	mantMaxima=obtenerCaminoM(puzzleInicial);
	int iteracion=0;
	movFinal=backtrackingI(puzzleInicial,mantMaxima,iteracion,movFinal);
	escribirArchivo(movFinal,archivoS);
	liberarMemoria(movFinal);
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
}

//Entrada: el puzzle inicial con su distancia de manhattan, la iteracion y la lista con los movimientos (actualmente vacia)
//Funcion: primera parte del backtracking donde verifica los movimientos posibles para el puzzle, para despues ingresar
//a los nuevos puzles con el movimiento realizado, para seguir con el arbol se ingresa a la parte 2 del backtracking
//Salida: Lista enlazada con los movimientos minimos para resolver el puzzle
Movimientos* backtrackingI(int puzzle[][3],int mantMaxima,int iteracion,Movimientos* movFinal){
	int aux,manhattan,i,j;
	int puzzleN[3][3];
	Movimientos* inicio;
    for(i=0;i<3;i++){
	    for(j=0;j<3;j++){
		    puzzleN[i][j]=puzzle[i][j];
	    }
    }
	printCurrent(puzzleN,iteracion,mantMaxima);
	if(comprobarPuzzles(puzzleN)==1){
		return movFinal;
	}
	if(puzzle[0][0]==0){
		aux=puzzleN[0][0];
		puzzleN[0][0]=puzzleN[0][1];
		puzzleN[0][1]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
		if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Derecha");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    }   
		puzzleN[0][0]=puzzle[1][0];
		puzzleN[1][0]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Abajo");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
	}else if(puzzle[0][1]==0){
		aux=puzzleN[0][1];
		puzzleN[0][1]=puzzleN[0][0];
		puzzleN[0][0]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Izquierda");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    }   
	    puzzleN[0][1]=puzzleN[1][1];
	    puzzleN[1][1]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Abajo");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    }   
	    puzzleN[0][1]=puzzleN[0][2];
	    puzzleN[0][2]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Derecha");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
	}else if(puzzle[0][2]==0){
		aux=puzzleN[0][2];
		puzzleN[0][2]=puzzleN[0][1];
		puzzleN[0][1]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Izquierda");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    }   
	    puzzleN[0][2]=puzzleN[1][2];
		puzzleN[1][2]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Abajo");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
	}else if(puzzle[1][0]==0){
		aux=puzzleN[1][0];
		puzzleN[1][0]=puzzleN[0][0];
		puzzleN[0][0]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Arriba");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    }  
		puzzleN[1][0]=puzzleN[1][1];
		puzzleN[1][1]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Derecha");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    } 
		puzzleN[1][0]=puzzleN[2][0];
		puzzleN[2][0]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Abajo");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	 
	}else if(puzzle[1][1]==0){
		aux=puzzleN[1][1];
		puzzleN[1][1]=puzzleN[1][0];
		puzzleN[1][0]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Izquierda");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    }  
	    puzzleN[1][1]=puzzleN[0][1];
		puzzleN[0][1]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Arriba");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    } 
		puzzleN[1][1]=puzzleN[1][2];
		puzzleN[1][2]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Derecha");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    } 
		puzzleN[1][1]=puzzleN[2][1];
		puzzleN[2][1]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Abajo");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	   
	}else if(puzzle[1][2]==0){
		aux=puzzleN[1][2];
		puzzleN[1][2]=puzzleN[1][1];
		puzzleN[1][1]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Izquierda");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    }  
	    puzzleN[1][2]=puzzleN[0][2];
		puzzleN[0][2]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Arriba");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    }  
	    puzzleN[1][2]=puzzleN[2][2];
		puzzleN[2][2]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Abajo");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
	}else if(puzzle[2][0]==0){
		aux=puzzleN[2][0];
		puzzleN[2][0]=puzzleN[1][0];
		puzzleN[1][0]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Arriba");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    }  
	    puzzleN[2][0]=puzzleN[2][1];
		puzzleN[2][1]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Derecha");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
	}else if(puzzle[2][1]==0){
		aux=puzzleN[2][1];
		puzzleN[2][1]=puzzleN[2][0];
		puzzleN[2][0]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Izquierda");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    }  
	    puzzleN[2][1]=puzzleN[1][1];
		puzzleN[1][1]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Arriba");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    }
		puzzleN[2][1]=puzzleN[2][2];
		puzzleN[2][2]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Derecha");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
	}else if(puzzle[2][2]==0){
		aux=puzzleN[2][2];
		puzzleN[2][2]=puzzleN[2][1];
		puzzleN[2][1]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Izquierda");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}	
		for(i=0;i<3;i++){
		    for(j=0;j<3;j++){
			    puzzleN[i][j]=puzzle[i][j];
		    }
	    }
	    puzzleN[2][2]=puzzleN[1][2];
		puzzleN[1][2]=aux;
	    manhattan=obtenerCaminoM(puzzleN);
	    if(manhattan<=mantMaxima+2){
			inicio=(Movimientos*)malloc(sizeof(Movimientos));
			strcpy(inicio->movimiento,"Arriba");
			inicio->siguiente=NULL;
			movFinal=backtracking(puzzleN,inicio,manhattan,iteracion+1,movFinal,puzzle);
		}		  
	}
	return movFinal;
}

//Entrada: algun estado del puzzle, los movimientos que lleva la iteacion, la distancia manhattan, la lista final y el puzzle anterior
//Funcion: segunda parte del backtracking la cual realiza lo mismo que la anterior, verificar los posibles movimientos de X
//segun su posicion, realiza recursion para llamarse asi misma hasta que encuentre la solucion o si supera el numero de 
//iteraciones o el numero de movimientos es superior al numero de movimientos final.
//Salida: retorna lalista final  
Movimientos* backtracking(int puzzle[][3],Movimientos* movInicial,int mantMaxima,int iteracion,Movimientos* movFinal,int puzzle2[][3]){
	Movimientos* nuevoMov;
	int puzzleN[3][3];
	int manhattan,aux,largo,largoFinal,i,j;
	for(i=0;i<3;i++){
	    for(j=0;j<3;j++){
		    puzzleN[i][j]=puzzle[i][j];
	    }
    }
	printCurrent(puzzleN,iteracion,mantMaxima);
	if(comprobarPuzzles(puzzle)==1){
		largo=obtenerLargo(movInicial);
		largoFinal=obtenerLargo(movFinal);
		if(largo< largoFinal || movFinal==NULL){
			movFinal=NULL;
			movFinal=crearFinal(movInicial,movFinal);
		}
		return movFinal;
	}
	if(iteracion > 32){
		return movFinal;
	}
	if(obtenerLargo(movInicial) > obtenerLargo(movFinal) && movFinal!=NULL){
		return movFinal;
	}else{
		if(puzzle[0][0]==0){
			aux=puzzleN[0][0];
			puzzleN[0][0]=puzzleN[0][1];
			puzzleN[0][1]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Derecha");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
			puzzleN[0][0]=puzzleN[1][0];
			puzzleN[1][0]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Abajo");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}	
		}else if(puzzle[0][1]==0){
			aux=puzzleN[0][1];
			puzzleN[0][1]=puzzleN[0][0];
			puzzleN[0][0]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Izquierda");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[0][1]=puzzleN[1][1];
			puzzleN[1][1]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Abajo");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[0][1]=puzzleN[0][2];
			puzzleN[0][2]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Derecha");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
		}else if(puzzle[0][2]==0){
			aux=puzzleN[0][2];
			puzzleN[0][2]=puzzleN[0][1];
			puzzleN[0][1]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Izquierda");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[0][2]=puzzleN[1][2];
			puzzleN[1][2]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Abajo");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
		}else if(puzzle[1][0]==0){
			aux=puzzleN[1][0];
			puzzleN[1][0]=puzzleN[0][0];
			puzzleN[0][0]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Arriba");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[1][0]=puzzleN[1][1];
			puzzleN[1][1]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Derecha");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[1][0]=puzzleN[2][0];
			puzzleN[2][0]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Abajo");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
		}else if(puzzle[1][1]==0){
			aux=puzzleN[1][1];
			puzzleN[1][1]=puzzleN[1][0];
			puzzleN[1][0]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	       if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Izquierda");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[1][1]=puzzleN[0][1];
			puzzleN[0][1]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Arriba");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[1][1]=puzzleN[2][1];
			puzzleN[2][1]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Abajo");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[1][1]=puzzleN[1][2];
			puzzleN[1][2]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Derecha");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
		}else if(puzzle[1][2]==0){
			aux=puzzleN[1][2];
			puzzleN[1][2]=puzzleN[1][1];
			puzzleN[1][1]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Izquierda");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
			puzzleN[1][2]=puzzleN[0][2];
			puzzleN[0][2]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Arriba");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[1][2]=puzzleN[2][2];
			puzzleN[2][2]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Abajo");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
		}else if(puzzle[2][0]==0){
			aux=puzzleN[2][0];
			puzzleN[2][0]=puzzleN[1][0];
			puzzleN[1][0]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Arriba");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[2][0]=puzzleN[2][1];
			puzzleN[2][1]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Derecha");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
		}else if(puzzle[2][1]==0){
			aux=puzzleN[2][1];
			puzzleN[2][1]=puzzleN[2][0];
			puzzleN[2][0]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Izquierda");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[2][1]=puzzleN[1][1];
			puzzleN[1][1]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Arriba");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[2][1]=puzzleN[2][2];
			puzzleN[2][2]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Derecha");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
		}else if(puzzle[2][2]==0){
			aux=puzzleN[2][2];
			puzzleN[2][2]=puzzleN[2][1];
			puzzleN[2][1]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Izquierda");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
			for(i=0;i<3;i++){
			    for(j=0;j<3;j++){
				    puzzleN[i][j]=puzzle[i][j];
			    }
		    }
		    puzzleN[2][2]=puzzleN[1][2];
			puzzleN[1][2]=aux;
	        manhattan=obtenerCaminoM(puzzleN);
	        if(manhattan<=mantMaxima+2 && compararPuzzleA(puzzleN,puzzle2)==0){
	        	nuevoMov=(Movimientos*)malloc(sizeof(Movimientos));
	        	strcpy(nuevoMov->movimiento,"Arriba");
	        	nuevoMov->siguiente=NULL;
	        	agregarMovimiento(movInicial,nuevoMov);
	        	movFinal=backtracking(puzzleN,movInicial,manhattan,iteracion+1,movFinal,puzzle);
	        	reiniciarMovimientos(movInicial,iteracion);
			}
		}		
	}
	return movFinal;	
}


//Entrada: lista enlazada y cantidad de iteraciones
//Funcion: para poder ir actualizando la lista dependiendo en que nivel del arbol vaya, se necesita ir actualizando la lista,
//es decir, Si se esta en el nivel 4 de recorrido y la lista tiene largo 5, se tiene que borrar el ultimo elemento
void reiniciarMovimientos(Movimientos* inicio,int iteracion){
	int n=1;
	Movimientos* aux;
	aux=inicio;
	while(n<= iteracion){
		if(n==iteracion){
			aux->siguiente=NULL;
			n++;
		}else{
			aux=aux->siguiente;
			n++;
		}
	}
}

//Entrada: puzzle del nodo acutal y el puzzle del nodo padre
//Funcion: compara si dos puzzle son iguales, el objetivo es que no haga un nuevo estado si ese puzzle es su nodo padre
//Salida: 0 o 1 si es falso o verdadero
int compararPuzzleA(int puzzle1[][3],int puzzle2[][3]){
	int i,j,count=0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(puzzle1[i][j]==puzzle2[i][j]){
				count++;
			}
		}
	}
	if(count==9){
		return 1;
	}else{
		return 0;
	}
}

/////FUNCIONALIDADES BASICAS DE LAS LISTAS ENLAZADAS///////////////////

//Entradas: lista enlazada actual, lista enlazada final
//Funcion: transforma la lista enzalada actual en la lista final 
//Salida: lista final
Movimientos* crearFinal(Movimientos* inicio,Movimientos* final){
	Movimientos* aux;
	Movimientos* mov;
	aux=inicio;
	while(aux!=NULL){
		mov=(Movimientos*)malloc(sizeof(Movimientos));
		strcpy(mov->movimiento,aux->movimiento);
		mov->siguiente=NULL;
		if(final==NULL){
			final=mov;
		}else{
			agregarMovimiento(final,mov);
		}
		aux=aux->siguiente;
	}
	return final;
}



//Entrada: lista enlazada y nodo a agregar
//Funcion: Funcionalidad basica de lista, la cual es agregar nodo a la lista
void agregarMovimiento(Movimientos* inicio,Movimientos* nuevo){
	Movimientos* aux;
	Movimientos* ultimo;
	aux=inicio;
	ultimo=inicio;
	while(aux!=NULL){
		ultimo=aux;
		aux=aux->siguiente;
	}
	ultimo->siguiente=nuevo;
	nuevo->siguiente=NULL;
}


//Entrada: lista enlazada
//Funcion: obtiene largo de la lista
//Salida: largo de la lista
int obtenerLargo(Movimientos* inicio){
	Movimientos* aux;
	aux=inicio;
	int largo=0;
	if(aux==NULL){
		return 0;
	}
	while(aux!=NULL){
		largo++;
		aux=aux->siguiente;
	}
	return largo;
}

/////////////////////////////////////////////////////////////////////////////////////////

//Entrada: puzzle
//Funcion: comprueba si el puzle es el estado final, es decir, si es el puzle resuelto
//Salida: verdadero o falso
int comprobarPuzzles(int puzzle[][3]){
	if(puzzle[0][0]==1 && puzzle[0][1]==2 && puzzle[0][2]==3 && puzzle[1][0]==4 && puzzle[1][1]==5 && puzzle[1][2]==6 && puzzle[2][0]==7 && puzzle[2][1]==8 ){
		return 1;
	}else{
		return 0;
	}
}

//Entrada: puzzle
//Funcion: realiza la distancia Manhattan en el puzzle
//Salida: entero con el resultado
int obtenerCaminoM(int puzzle[][3]){
	int mant=0;
	if(puzzle[0][0]!=1){
		if(puzzle[0][1]==1){
			mant++;
		}else if(puzzle[0][2]==1){
			mant=mant+2;
		}else if(puzzle[1][0]==1){
			mant++;
		}else if(puzzle[1][1]==1){
			mant=mant+2;
		}else if(puzzle[1][2]==1){
			mant=mant+3;
		}else if(puzzle[2][0]==1){
			mant=mant+2;
		}else if(puzzle[2][1]==1){
			mant=mant+3;
		}else if(puzzle[2][2]==1){
			mant=mant+4;
		}
	}
	if(puzzle[0][1]!=2){
		if(puzzle[0][0]==2){
			mant++;
		}else if(puzzle[0][2]==2){
			mant++;
		}else if(puzzle[1][0]==2){
			mant=mant+2;
		}else if(puzzle[1][1]==2){
			mant++;
		}else if(puzzle[1][2]==2){
			mant=mant+2;
		}else if(puzzle[2][0]==2){
			mant=mant+3;
		}else if(puzzle[2][1]==2){
			mant=mant+2;
		}else if(puzzle[2][2]==2){
			mant=mant+3;
		}
	}
	if(puzzle[0][2]!=3){
		if(puzzle[0][0]==3){
			mant=mant+2;
		}else if(puzzle[0][1]==3){
			mant++;
		}else if(puzzle[1][0]==3){
			mant=mant+3;
		}else if(puzzle[1][1]==3){
			mant=mant+2;
		}else if(puzzle[1][2]==3){
			mant++;
		}else if(puzzle[2][0]==3){
			mant=mant+4;
		}else if(puzzle[2][1]==3){
			mant=mant+3;
		}else if(puzzle[2][2]==3){
			mant=mant+2;
		}
	}
	if(puzzle[1][0]!=4){
		if(puzzle[0][0]==4){
			mant++;
		}else if(puzzle[0][1]==4){
			mant=mant+2;
		}else if(puzzle[0][2]==4){
			mant=mant+3;
		}else if(puzzle[1][1]==4){
			mant++;
		}else if(puzzle[1][2]==4){
			mant=mant+2;
		}else if(puzzle[2][0]==4){
			mant++;
		}else if(puzzle[2][1]==4){
			mant=mant+2;
		}else if(puzzle[2][2]==4){
			mant=mant+3;
		}
	}
	if(puzzle[1][1]!=5){
		if(puzzle[0][0]==5){
			mant=mant+2;
		}else if(puzzle[0][1]==5){
			mant++;
		}else if(puzzle[0][2]==5){
			mant=mant+2;
		}else if(puzzle[1][0]==5){
			mant++;
		}else if(puzzle[1][2]==5){
			mant++;
		}else if(puzzle[2][0]==5){
			mant=mant+2;
		}else if(puzzle[2][1]==5){
			mant++;
		}else if(puzzle[2][2]==5){
			mant=mant+2;
		}
	}
	if(puzzle[1][2]!=6){
		if(puzzle[0][0]==6){
			mant=mant+3;
		}else if(puzzle[0][1]==6){
			mant=mant+2;
		}else if(puzzle[0][2]==6){
			mant++;
		}else if(puzzle[1][0]==6){
			mant=mant+2;
		}else if(puzzle[1][1]==6){
			mant++;
		}else if(puzzle[2][0]==6){
			mant=mant+3;
		}else if(puzzle[2][1]==6){
			mant=mant+2;
		}else if(puzzle[2][2]==6){
			mant++;
		}
	}
	if(puzzle[2][0]!=7){
		if(puzzle[0][0]==7){
			mant=mant+2;
		}else if(puzzle[0][1]==7){
			mant=mant+3;
		}else if(puzzle[0][2]==7){
			mant=mant+4;
		}else if(puzzle[1][0]==7){
			mant++;
		}else if(puzzle[1][1]==7){
			mant=mant+2;
		}else if(puzzle[1][2]==7){
			mant=mant+3;
		}else if(puzzle[2][1]==7){
			mant++;
		}else if(puzzle[2][2]==7){
			mant=mant+2;
		}
	}
	if(puzzle[2][1]!=8){
		if(puzzle[0][0]==8){
			mant=mant+3;
		}else if(puzzle[0][1]==8){
			mant=mant+2;
		}else if(puzzle[0][2]==8){
			mant=mant+3;
		}else if(puzzle[1][0]==8){
			mant=mant+2;
		}else if(puzzle[1][1]==8){
			mant++;
		}else if(puzzle[1][2]==8){
			mant=mant+2;
		}else if(puzzle[2][0]==8){
			mant++;
		}else if(puzzle[2][2]==8){
			mant++;
		}
	}
	if(puzzle[2][2]!=0){
		if(puzzle[0][0]==0){
			mant=mant+4;
		}else if(puzzle[0][1]==0){
			mant=mant+3;
		}else if(puzzle[0][2]==0){
			mant=mant+2;
		}else if(puzzle[1][0]==0){
			mant=mant+3;
		}else if(puzzle[1][1]==0){
			mant=mant+2;
		}else if(puzzle[1][2]==0){
			mant++;
		}else if(puzzle[2][0]==0){
			mant=mant+2;
		}else if(puzzle[2][1]==0){
			mant++;
		}
	}
	return mant;
}

//Entrada: lista enlazada
//Funcion: libera la memoria 
void liberarMemoria(Movimientos* inicio){
	Movimientos* aux;
	while(aux!=NULL){
		aux=inicio;
		inicio=inicio->siguiente;
		free(aux);
	}
}


//Entrada: lista enlazada final, y el nombre del archivo de salida
//Funcion: crea el archivo de salida
void escribirArchivo(Movimientos* inicio,FILE* solucion){
	int largo;
	Movimientos* aux;
	aux=inicio;
	largo=obtenerLargo(inicio);
	fprintf(solucion,"%i",largo);
	fprintf(solucion,"\n");
	while(aux!=NULL){
		fprintf(solucion,"%s",aux->movimiento);
		fprintf(solucion,"\n");
		aux=aux->siguiente;
	}
	fclose(solucion);
	printf("Archivo Creado\n");
}


////////////////PRINT CURRENT//////////////////////////

//entrada: lista enlazada, iteracion y distancia de manhattan
//Funcion: imprime el puzzle, con la cantidad de movimientos que se han realizados y la disntancia de Manhattan del puzzle
void printCurrent(int puzzle[][3],int iteracion,int mantMaxima){
	#ifdef DEBUG
	int i,j;
	printf("Movimientos realizados: %i  Distancia manhattan: %i\n",iteracion,mantMaxima);
    for(i=0;i<3;i++){
    	for(j=0;j<3;j++){
    		if(j==2){
    			if(puzzle[i][j]==0){
    				printf("X\n");
    			}else{
    				printf("%i\n",puzzle[i][j]);
    			}
    		}else{
    			if(puzzle[i][j]==0){
    				printf("X |");
    			}else{
    				printf("%i |",puzzle[i][j]);
    			}
    		}
		}
	}
	while(getchar() != '\n');
	printf("Enter para continuar...\n");
	#endif
}




