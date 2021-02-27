#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "lista.h"

#define MAX_NOMBRE 50

typedef int (*funcion_batalla)(void*, void*);

typedef struct pokemon{
    char nombre[MAX_NOMBRE];
    int velocidad;
    int ataque;
    int defensa;
    int mejora;
}pokemon_t;

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    lista_t* lista_pokemon;
}entrenador_t;

typedef struct personaje_principal{
    char nombre[MAX_NOMBRE];
    lista_t* lista_pokemon_obtenidos;
    lista_t* cola_pokemon_combate;
}personaje_principal_t;

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    int dificultad;
    int id_puntero_funcion;
    lista_t* pila_entrenadores;
    funcion_batalla batalla;
}gimnasio_t;

#endif /* __STRUCTS_H__ */