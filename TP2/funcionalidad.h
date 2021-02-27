#ifndef __FUNCIONALIDAD_H__
#define __FUNCIONALIDAD_H__

#include "heap.h"
#include "structs.h"

/*
 * Crea el personaje principal reservando la memoria necesaria.
 * Devuelve un puntero a el personaje principal creado o NULL en caso de error.
 */
personaje_principal_t* crear_personaje_principal();

/*
 *
 */
int cargar_personaje(const char* nombre_archivo, personaje_principal_t* personaje);

/*
 *
 */
int cargar_gimnasios(const char* nombre_archivo, heap_t* heap_gimnasios);

/*
 *
 */
int pelear(gimnasio_t* gimnasio, personaje_principal_t* personaje, char opcion_partida);

#endif /* __FUNCIONALIDAD_H__ */