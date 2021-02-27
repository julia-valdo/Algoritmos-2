#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTOS 100

#define ERROR -1
#define OK 0

heap_t* heap_crear(heap_liberar_elemento destructor){

    heap_t* heap = calloc(1, sizeof(heap_t));
    if(!heap)
        return NULL;

    heap->destructor = destructor;

    return heap;
}

int posicion_padre(int n){
    return (n-1)/2;
}

int posicion_hijo_derecho(int n){
    return 2*n+2;
}

int posicion_hijo_izquierdo(int n){
    return 2*n+1;
}

void swap(void** vector, int i, int j){

    void** aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
}

void sift_up(heap_t* heap, int n){

    if(n == 0)
        return;

    int padre = posicion_padre(n); 

    if(heap->vector[n] > heap->vector[padre]){
        swap(heap->vector, n, padre);
        sift_up(heap, padre);
    }
}

int heap_insertar(heap_t* heap, void* elemento){

    void** aux = realloc(heap->vector, (size_t)(heap->tope+1)*sizeof(void*));
    if(!aux)
        return ERROR;
    
    heap->tope++;
    heap->vector = aux;

    heap->vector[heap->tope-1] = elemento;

    sift_up(heap, heap->tope-1);

    return OK;
}

void sift_down(heap_t* heap, int n){

    int pos_der = posicion_hijo_derecho(n);
    int pos_izq = posicion_hijo_izquierdo(n);
    int pos_mayor = pos_izq;

    if(pos_izq >= heap->tope) // no tiene hijos
        return;

    if(pos_der < heap->tope){ // tiene hijo derecho
        if(heap->vector[pos_der] > heap->vector[pos_izq])
            pos_mayor = pos_der;
    }

    if(heap->vector[n] < heap->vector[pos_mayor]){
        swap(heap->vector, n, pos_mayor);
        sift_down(heap, pos_mayor);
    }
}

void* heap_extraer_raiz(heap_t* heap){

    if(heap->tope == 0)
        return 0;

    void* valor = heap->vector[0];

    heap->vector[0] = heap->vector[heap->tope-1];
    heap->tope--;

    if(heap->tope != 0) // si hay elementos...
        sift_down(heap, 0);

    return valor;
}

void heap_destruir(heap_t* heap){
    
    if(!heap)
        return;

    if(heap->destructor){
        for(int i = 0; i < heap->tope; i++){
            heap->destructor(heap->vector[i]);
        }
    }
    free(heap->vector);    
    free(heap);
}