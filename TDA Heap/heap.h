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

heap_t* heap_crear(heap_liberar_elemento destructor);

void sift_up(heap_t* heap, int n);

int heap_insertar(heap_t* heap, void* elemento);

void sift_down(heap_t* heap, int n);

void* heap_extraer_raiz(heap_t* heap);

void heap_destruir(heap_t* heaps);

#endif /* __HEAP_H__ */

