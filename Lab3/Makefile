outfile = Ejecutable
headers = funciones.h
source  = goloso.c
objects = $(source.c=.o)



CC     = gcc
CFLAGS = -Wall

#Considerar diferencias entre linux y windows
ifeq ($(OS), Windows_NT)
    outfile = Ejecutable.exe
	RM = del
endif

#regla principal - compila el programa 
#$(poutfile) : $(objects)
all:
   $(CC) $(CFLAGS) $(source) -o $(outfile)

DEBUG:
   $(CC) $(CFLAGS) $(source) -o $(outfile) -DDEBUG

#generación automaticas de reglas para compilar *.objects
#$(objects) : $(headers)

#limpiar carpeta de *.o y Ejecutable
#.PHONY : clean

clean:
   $(RM) $(outfile) $(objects)

