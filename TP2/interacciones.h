#ifndef __INTERACCIONES_H__
#define __INTERACCIONES_H__

#include "structs.h"

#define MAX_GIMNASIOS 10

char menu_inicio(char archivo_entrenador[MAX_NOMBRE], char archivo_gimnasio[MAX_GIMNASIOS][MAX_NOMBRE], int* cantidad_gimnasios);

void menu_gimnasio(gimnasio_t* gimnasio, personaje_principal_t* personaje_principal);

void menu_batalla(personaje_principal_t* personaje, pokemon_t* pokemon_personaje, entrenador_t* enrenador, pokemon_t* pokemon_entrenador, int ganador, char opcion);

void menu_victoria(personaje_principal_t* personaje, gimnasio_t* gimnasio);

char menu_derrota(personaje_principal_t* personaje);

#endif /* __INTERACCIONES_H__ */