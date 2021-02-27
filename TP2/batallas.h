#ifndef __BATALLAS_H__
#define __BATALLAS_H__

#define GANO_PRIMERO 1
#define GANO_SEGUNDO -1

/*
 * Se deberan implementar las 5 funciones de batalla.
 * Las reglas para decidir al ganador las inventan ustedes
 * 
 * Si el ganador es el primer pokemon, se devolvera 1
 * Si el ganador es el segundo pokemon, se devolvera -1
 * 
 * No habran empates.
 */

/*
 * Gana el pokemon mas rapido.
 */
int funcion_batalla_1(void* pkm_1, void* pkm_2);

/*
 * Primero ataque el primer pokemon y luego el segundo pokemon.
 * Pierde el primer pokemon que se quede sin defensa.
 */
int funcion_batalla_2(void* pkm_1, void* pkm_2);

/*
 * El pokemon con mayor velocidad ataca primero.
 * Pierde el primer pokemon que se quede sin defensa.
 */
int funcion_batalla_3(void* pkm_1, void* pkm_2);

/*
 * Se elige un numero random del 0 al 99.
 * Si el numero random es par gana el primer pokemon y si es impar gana el segundo pokemon.
 */
int funcion_batalla_4(void* pkm_1, void* pkm_2);

/* 
 * Dependiendo de el nombre del pokemon atacara el primero o el segundo.
 * Pierde el primer pokemon que se quede sin defensa.
 */
int funcion_batalla_5(void* pkm_1, void* pkm_2);

#endif /* __BATALLAS_H__ */