#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

#define BLANCO "\x1b[37;1m"
#define VERDE "\x1b[32;1m"
#define ROJO "\x1b[31;1m"
#define AMARILLO "\x1b[33;1m"
#define AZUL "\x1b[0;36m"
#define NORMAL "\x1b[0m"
#define SUBRAYADO "\x1b[4;33m"
#define FONDO "\x1b[1;90m"
#define TILDE "✓"
#define CRUZ "✗"
#define CIRCULO "•"
#define FLECHA "→"

typedef struct cosa{
    int clave;
    char contenido[10];
}cosa;

void afirmar(char* descripcion, bool afirmacion, int* pruebas_pasadas, int* cantidad_pruebas){

	if(!descripcion || !pruebas_pasadas || !cantidad_pruebas)
		return;

	if(afirmacion){
		(*pruebas_pasadas)++;
	}
	printf("%s %s\n", afirmacion? VERDE TILDE NORMAL : ROJO CRUZ NORMAL, descripcion);

	(*cantidad_pruebas)++;
}

cosa* crear_cosa(int clave){
    cosa* c = (cosa*)malloc(sizeof(cosa));
    if(c)
        c->clave = clave;
    return c;
}

void destruir_cosa(cosa* c){
    free(c);
}

void destructor_de_cosas(void* elemento){
    if(!elemento)
        return;
    destruir_cosa((cosa*)elemento);
}

void probar_heap_crear(int* pruebas_pasadas, int* cantidad_pruebas){

	heap_t* heap = heap_crear(NULL);

	afirmar("Heap creado correctamente", heap != NULL, pruebas_pasadas, cantidad_pruebas);
	afirmar("Heap creado con un destructor nulo", heap != NULL, pruebas_pasadas, cantidad_pruebas);
	heap_destruir(heap);    
}

int main(){

    int pruebas_pasadas = 0;
	int cantidad_pruebas = 0;
	int pruebas_fallidas = 0;

    probar_arbol_crear(&pruebas_pasadas, &cantidad_pruebas);

    heap_t* heap = heap_crear(destructor_de_cosas);

    cosa* c1 = crear_cosa(1);
    cosa* c2 = crear_cosa(2);
    cosa* c3 = crear_cosa(3);
    cosa* c4 = crear_cosa(4);
    cosa* c5 = crear_cosa(5);
    cosa* c6 = crear_cosa(6);
    cosa* c7 = crear_cosa(7);
    
    heap_insertar(heap, c1);
    heap_insertar(heap, c2);
    heap_insertar(heap, c3);
    heap_insertar(heap, c4);
    heap_insertar(heap, c5);
    heap_insertar(heap, c6);
    heap_insertar(heap, c7);

    heap_destruir(heap);

    pruebas_fallidas = cantidad_pruebas - pruebas_pasadas;
	printf(BLANCO "-------------------------------------------------------------------------------\n");
	printf("%i pruebas corridas, %i correctas y %i errores.\n", cantidad_pruebas, pruebas_pasadas, pruebas_fallidas);
	printf("-------------------------------------------------------------------------------\n" NORMAL);

    return 0;
}