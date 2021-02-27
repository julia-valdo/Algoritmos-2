#ifndef __HEAP_H__
#define __HEAP_H__

/*
 * Destructor de elementos. Cada vez que un elemento deja el heap
 * se invoca al destructor pasandole el elemento.
 */
typedef void (*heap_liberar_elemento)(void*);

typedef struct heap{
    void** vector;
    int tope;
    heap_liberar_elemento destructor;
}heap_t;

/*
 * Crea el heap reservando la memoria necesaria.
 * Devuelve un puntero a el heap creado o NULL en caso de error.
 */
heap_t* heap_crear(heap_liberar_elemento destructor);

/*
 *  Va intercambiando el nodo de la posicion n con su padre hasta que cumpla la condicion de heap.
 *  Si el nodo es menor que su padre se intercambian.
 */
void sift_up(heap_t* heap, int n);

/*
 * Inserta un elemento al final de el heap.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int heap_insertar(heap_t* heap, void* elemento);

/*
 *  Va intercambiando el nodo de la posicion n con su hijo hasta que cumpla la condicion de heap.
 *  Si el nodo no tiene hijos se queda en donde esta.
 *  Si el nodo en posicion es mayor a alguno de sus nodos hijos, se intercambian.
 */
void sift_down(heap_t* heap, int n);

/*  
 * Devuelve la raiz.
 */
void* heap_extraer_raiz(heap_t* heap);

/*
 * Libera la memoria reservada por el heap.
 */
void heap_destruir(heap_t* heaps);

#endif /* __HEAP_H__ */

