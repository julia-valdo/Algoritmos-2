#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

int funcion_batalla_1(void* pkm_1, void* pkm_2){
    pokemon_t* pokemon_personaje = pkm_1;
    pokemon_t* pokemon_entrenador = pkm_2;

    if(pokemon_personaje->velocidad > pokemon_entrenador->velocidad) return 1;
    else return -1;    
}

int funcion_batalla_2(void* pkm_1, void* pkm_2){
    pokemon_t* pokemon_personaje = pkm_1;
    int defensa_pokemon_personaje = pokemon_personaje->defensa;
    pokemon_t* pokemon_entrenador = pkm_2;
    int defensa_pokemon_entrenador = pokemon_entrenador->defensa;

    while(defensa_pokemon_entrenador >= 0 && defensa_pokemon_personaje >= 0){
        defensa_pokemon_entrenador -= pokemon_personaje->ataque;
        defensa_pokemon_personaje -= pokemon_entrenador->ataque;
    }
    if(defensa_pokemon_entrenador <= 0) return 1;
    else return -1;
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){
    pokemon_t* pokemon_personaje = pkm_1;
    int defensa_pokemon_personaje = pokemon_personaje->defensa;
    pokemon_t* pokemon_entrenador = pkm_2;
    int defensa_pokemon_entrenador = pokemon_entrenador->defensa;

    while(defensa_pokemon_entrenador >= 0 && defensa_pokemon_personaje >= 0){
        if(pokemon_personaje->velocidad >= pokemon_entrenador->velocidad){
            defensa_pokemon_entrenador -= pokemon_personaje->ataque;
            defensa_pokemon_personaje -= pokemon_entrenador->ataque;
        }else{
            defensa_pokemon_personaje -= pokemon_entrenador->ataque;
            defensa_pokemon_entrenador -= pokemon_personaje->ataque;
        }
    }
    if(defensa_pokemon_entrenador <= 0) return 1;
    else return -1;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){    
    int numero = rand() % 99;

    if((numero % 2) == 0) return 1;
    else return -1;
}

int funcion_batalla_5(void* pkm_1, void* pkm_2){
    pokemon_t* pokemon_personaje = pkm_1;
    int defensa_pokemon_personaje = pokemon_personaje->defensa;
    pokemon_t* pokemon_entrenador = pkm_2;
    int defensa_pokemon_entrenador = pokemon_entrenador->defensa;
    
    int comparar = strcmp(pokemon_personaje->nombre, pokemon_entrenador->nombre);

    while(defensa_pokemon_entrenador >= 0 && defensa_pokemon_personaje >= 0){
        if(comparar > 0){
            defensa_pokemon_entrenador -= pokemon_personaje->ataque;
            defensa_pokemon_personaje -= pokemon_entrenador->ataque;
        }else{
            defensa_pokemon_personaje -= pokemon_entrenador->ataque;
            defensa_pokemon_entrenador -= pokemon_personaje->ataque;
        }
    }
    if(defensa_pokemon_entrenador <= 0) return 1;
    else return -1;
}