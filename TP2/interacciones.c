#include <stdio.h>
#include <string.h>
#include "interacciones.h"
#include "structs.h"

#define MAX_POKEMON_COMBATE 6
#define SIMULACION 'S'

#define ROJO "\x1b[91m"
#define BOLD_ROJO "\x1b[1;91m"
#define AMARILLO "\x1b[93m"
#define BOLD_AMARILLO "\x1b[1;97m"
#define VERDE "\x1b[92m"
#define MAGENTA "\x1b[95m"
#define BOLD_AZUL "\x1b[34m"
#define NORMAL "\x1b[0m"
#define FLECHA "→"

char menu_inicio(char archivo_personaje[MAX_NOMBRE], char archivo_gimnasio[MAX_GIMNASIOS][MAX_NOMBRE], int* cantidad_gimnasios){
 
    char opcion;   
    char nombre_archivo_gimnasio[MAX_NOMBRE];

    printf(" ┌──────────────────"BOLD_AZUL" MENU INICIO "NORMAL"──────────────────┐\n");
    printf(" │ "BOLD_AMARILLO"E"NORMAL": Ingresa el archivo del entrenador principal. │\n │ "BOLD_AMARILLO"A"NORMAL": Agrega un gimnasio al arbol de gimnasios.    │\n │ "BOLD_AMARILLO"I"NORMAL": Comienza la partida.                         │\n │ "BOLD_AMARILLO"S"NORMAL": Simula la partida.                           │\n");
    printf(" └─────────────────────────────────────────────────┘\n");
    scanf(" %c", &opcion);

    if(opcion != 'E' && opcion != 'A' && opcion != 'I' && opcion != 'S'){
        printf(ROJO" Debes ingresar un comando valido.\n"NORMAL);
        menu_inicio(archivo_personaje, archivo_gimnasio, cantidad_gimnasios);    
    }

    if((opcion == 'I' || opcion == 'S')){
        printf(ROJO" ¡Atencion!"NORMAL" No se ha ingresado el archivo del entrenador principal ni se ha agregado un gimnasio.\n");
        printf(" ┌─────────────────────────────────────────────────┐\n");
        printf(" │ "BOLD_AMARILLO"E" NORMAL": Ingresa el archivo del entrenador principal. │\n │ "BOLD_AMARILLO"A"NORMAL": Agrega un gimnasio al arbol de gimnasios.    │\n");
        printf(" └─────────────────────────────────────────────────┘\n");
        scanf(" %c", &opcion);
        while(opcion != 'E' && opcion != 'A'){
            printf(" Debes ingresar un comando valido.\n");
            printf(" ┌─────────────────────────────────────────────────┐\n");
            printf(" │ "BOLD_AMARILLO"E" NORMAL": Ingresa el archivo del entrenador principal. │\n │ "BOLD_AMARILLO"A"NORMAL": Agrega un gimnasio al arbol de gimnasios.    │\n");
            printf(" └─────────────────────────────────────────────────┘\n");
            scanf(" %c", &opcion);    
        }
    }    
    if(opcion == 'E'){
        printf(BOLD_AMARILLO FLECHA NORMAL" Ingrese la ruta del archivo del entrenador principal: \n");
        printf("• ");
        scanf(" %s", archivo_personaje);
        printf("\n");
        printf("Ingrese cuantos archivos de gimnasio desea agregar:\n");
        scanf("%i", cantidad_gimnasios);
        while(*cantidad_gimnasios <= 0 || *cantidad_gimnasios > 10){
            printf("Ingrese un numero valido de archivos, minimo 1 y maximo 10:\n");
            scanf("%i", cantidad_gimnasios);
        }
        for(int i = 0; i < *cantidad_gimnasios; i++){
            printf(BOLD_AMARILLO FLECHA NORMAL" Agrega un gimnasio al arbol de gimnasios: \n\n");
            printf("• ");
            scanf(" %s", nombre_archivo_gimnasio);
            printf("\n");
            strcpy(archivo_gimnasio[i], nombre_archivo_gimnasio);
        }
    }

    if(opcion == 'A'){
        printf("Ingrese cuantos archivos de gimnasio desea agregar:\n");
        scanf("%i", cantidad_gimnasios);
        while(*cantidad_gimnasios <= 0 || *cantidad_gimnasios > 10){
            printf("Ingrese un numero valido de archivos (MINIMO 1 y MAXIMO 10):\n");
            scanf("%i", cantidad_gimnasios);
        }
        for(int i = 0; i < *cantidad_gimnasios; i++){
            printf(BOLD_AMARILLO FLECHA NORMAL" Agrega un gimnasio al arbol de gimnasios: \n\n");
            printf("• ");
            scanf(" %s", nombre_archivo_gimnasio);
            printf("\n");
            strcpy(archivo_gimnasio[i], nombre_archivo_gimnasio);
        }
        printf("\n");
        printf(BOLD_AMARILLO FLECHA NORMAL" Ingrese la ruta del archivo del entrenador principal: \n");
        printf("• ");
        scanf(" %s", archivo_personaje);
        printf("\n");
    }

    printf(" ┌──────────────────"BOLD_AZUL" MENU INICIO "NORMAL"──────────────────┐\n");
    printf(" │ "BOLD_AMARILLO"I"NORMAL": comienza la partida.                         │\n │ "BOLD_AMARILLO"S"NORMAL": simula la partida.                           │\n");
    printf(" └─────────────────────────────────────────────────┘\n");
    scanf(" %c", &opcion);
    while(opcion != 'I' && opcion != 'S'){
        printf(" Debes ingresar un comando valido.\n");
        printf(" ┌──────────────────"BOLD_AZUL" MENU INICIO "NORMAL"──────────────────┐\n");
        printf(" │ "BOLD_AMARILLO"I"NORMAL": comienza la partida.                         │\n │ "BOLD_AMARILLO"S"NORMAL": simula la partida.                           │\n");
        printf(" └─────────────────────────────────────────────────┘\n");
        scanf(" %c", &opcion);    
    }
    return opcion;
}

void mostrar_info_personaje(personaje_principal_t* personaje){    
    printf("──────── POKEMON DE COMBATE ────────\n");
    printf("POKEMON │ VELOCIDAD │ ATAQUE │ DEFENSA\n");
    for(size_t i = 0; i < personaje->cola_pokemon_combate->cantidad; i++){
        pokemon_t* pokemon = lista_elemento_en_posicion(personaje->cola_pokemon_combate, i);
        printf("%li) %-15s  │", i, pokemon->nombre);
        printf("%i  │", pokemon->velocidad);
        printf("%i  │", pokemon->ataque);
        printf("%i\n", pokemon->defensa);
    }
    printf("──────── POKEMON OBTENIDOS ────────\n");
    printf("POKEMON │ VELOCIDAD │ ATAQUE │ DEFENSA\n");
    for(size_t i = 0; i < personaje->lista_pokemon_obtenidos->cantidad; i++){
        pokemon_t* pokemon = lista_elemento_en_posicion(personaje->lista_pokemon_obtenidos, i);
        printf("%li) %-15s  │", i, pokemon->nombre);
        printf("%i  │", pokemon->velocidad);
        printf("%i  │", pokemon->ataque);
        printf("%i\n", pokemon->defensa);
    }
}

void mostrar_info_entrenador(entrenador_t* entrenador){
   
    for(size_t i = 0; i < entrenador->lista_pokemon->cantidad; i++){
        pokemon_t* pokemon = lista_elemento_en_posicion(entrenador->lista_pokemon, i);
        printf("%li) %-15s  │", i, pokemon->nombre);
        printf("%i  │", pokemon->velocidad);
        printf("%i  │", pokemon->ataque);
        printf("%i\n", pokemon->defensa);
    }
}

void mostrar_info_gimnasio(gimnasio_t* gimnasio){
    printf(VERDE"%s"NORMAL", dificultad: %i\n", gimnasio->nombre, gimnasio->dificultad);
    printf("──────── LIDER ────────\n");
    entrenador_t* lider = lista_primero(gimnasio->pila_entrenadores);
    printf("Nombre: %s\n", lider->nombre);
    printf("──────── ENTRENADORES ────────\n");
    for(size_t i = 1; i < (gimnasio->pila_entrenadores->cantidad); i++){
        entrenador_t* lider = lista_elemento_en_posicion(gimnasio->pila_entrenadores, i);
        printf("Nombre: %s\n", lider->nombre);
    }
}

void cambiar_pokemon(personaje_principal_t* personaje){
    size_t posicion = 0;
    for(int i = 0; i < MAX_POKEMON_COMBATE; i++)
        lista_desencolar(personaje->cola_pokemon_combate);
    mostrar_info_personaje(personaje);
    printf("Ingrese el numero de los 6 pokemon que quiere agregar: \n");
    while(personaje->cola_pokemon_combate->cantidad < MAX_POKEMON_COMBATE){
        scanf("%zu", &posicion);        
        pokemon_t* pokemon = (pokemon_t*)lista_elemento_en_posicion(personaje->lista_pokemon_obtenidos, posicion);
        lista_encolar(personaje->cola_pokemon_combate, pokemon);
        mostrar_info_personaje(personaje);
    }
}

void menu_gimnasio(gimnasio_t* gimnasio, personaje_principal_t* personaje_principal){
    
    char opcion;

    printf(" ┌──────────────────"AMARILLO" MENU GIMANSIO "NORMAL"────────────────┐\n");
    printf(" │ "VERDE"E"NORMAL": Informacion personaje principal              │\n │ "VERDE"G"NORMAL": Informacion del gimnasio actual              │\n │ "VERDE"C"NORMAL": Cambiar pokemon de combate                   │\n │ "VERDE"B"NORMAL": Proxima batalla                              │\n");
    printf(" └─────────────────────────────────────────────────┘\n");
    scanf(" %c", &opcion);
    if(opcion != 'E' && opcion != 'G' && opcion != 'C' && opcion != 'B'){
        printf(" Debes ingresar un comando valido.\n");
        menu_gimnasio(gimnasio, personaje_principal);
    }
    if(opcion == 'E'){
        printf("Nombre: %s\n", personaje_principal->nombre);
        mostrar_info_personaje(personaje_principal);
        menu_gimnasio(gimnasio, personaje_principal);
    }
    if(opcion == 'G'){
        mostrar_info_gimnasio(gimnasio);
        menu_gimnasio(gimnasio, personaje_principal);
    }
    if(opcion == 'C'){
        cambiar_pokemon(personaje_principal);
        menu_gimnasio(gimnasio, personaje_principal);
    }
    if(opcion == 'B')
        return;
}

void menu_batalla(personaje_principal_t* personaje, pokemon_t* pokemon_personaje, entrenador_t* entrenador, pokemon_t* pokemon_entrenador, int ganador, char opcion){
    char proximo_combate;
    printf("┌────────────────────────────────────────────────────────┐\n");
    printf("│"VERDE"ENTRENADOR:"NORMAL" %-15s│ "VERDE"ENTRENADOR:"NORMAL" %-15s│\n", personaje->nombre, entrenador->nombre);
    printf("├────────────────────────────────────────────────────────┤\n");
    printf("│Pokemon: %-17s │ Pokemon: %-17s │\n", pokemon_personaje->nombre, pokemon_entrenador->nombre);
    printf("│ • Velocidad: %-13i│ • Velocidad: %-13i │\n", pokemon_personaje->velocidad, pokemon_entrenador->velocidad);
    printf("│ • Ataque: %-13i   │ • Ataque: %-13i    │\n", pokemon_personaje->ataque, pokemon_entrenador->ataque);
    printf("│ • Defensa: %-13i  │ • Defensa: %-13i   │\n", pokemon_personaje->defensa, pokemon_entrenador->defensa);
    printf("├───────────────────────────┴────────────────────────────┤\n");
    if(ganador == 1){
        printf("│"AMARILLO"Ganador:"NORMAL" %-46s │\n", personaje->nombre);
        printf("└────────────────────────────────────────────────────────┘\n");
    }else{
        printf("│"AMARILLO"Ganador:"NORMAL" %-46s │\n", entrenador->nombre);
        printf("└────────────────────────────────────────────────────────┘\n");
    }if(opcion != SIMULACION){
        printf("\n");
        printf(VERDE"N:"NORMAL" Proximo combate.\n");
        scanf(" %c", &proximo_combate);
        while(proximo_combate != 'N'){
            printf(ROJO"N: Proximo combate dije.\n"NORMAL);
            scanf(" %c", &proximo_combate);
        }
    } 
}

void tomar_pokemon(personaje_principal_t* personaje, gimnasio_t* gimnasio){
    size_t posicion = 0;
    entrenador_t* lider = (entrenador_t*)lista_primero(gimnasio->pila_entrenadores);
    printf("POKEMON DEL LIDER:\n");
    mostrar_info_entrenador(lider);
    printf("Elige el numero del pokemon que quieres agregar a tu lista de pokemon obtenidos:\n");
    scanf("%zu", &posicion);
    while(posicion >= lider->lista_pokemon->cantidad){
        printf("ERROR. Elige un numero valido.\n");
        mostrar_info_entrenador(lider);
        scanf("%zu", &posicion);
    }
    pokemon_t* pokemon = (pokemon_t*)lista_elemento_en_posicion(lider->lista_pokemon, posicion);
    lista_insertar(personaje->lista_pokemon_obtenidos, pokemon);
    mostrar_info_personaje(personaje);
}

void menu_victoria(personaje_principal_t* personaje, gimnasio_t* gimnasio){
    char opcion;
    printf("T: Toma un pokemon del lider y lo incorpora en los pokemon obtenidos del jugador.\n");
    printf("C: Permite cambiar los pokemon de batalla.\n");
    printf("N: proximo gimnasio.\n");
    scanf(" %c", &opcion);
    if(opcion != 'T' && opcion != 'C' && opcion != 'N'){
        printf(" Debes ingresar un comando valido.\n");
        menu_victoria(personaje, gimnasio);
    }
    if(opcion == 'T'){
        tomar_pokemon(personaje, gimnasio);
        printf("C: Permite cambiar los pokemon de batalla.\n");
        printf("N: proximo gimnasio.\n");
        scanf(" %c", &opcion);
        while(opcion != 'C' && opcion != 'N'){
            printf("C: Permite cambiar los pokemon de batalla.\n");
            printf("N: proximo gimnasio.\n");
            scanf(" %c", &opcion);
        }
        if(opcion == 'C'){
            cambiar_pokemon(personaje);
            return;
        }else return;
    }
    if(opcion == 'C'){
        cambiar_pokemon(personaje);
    }else return;
}

char menu_derrota(personaje_principal_t* personaje){
    char opcion;    

    printf(" ┌──────────────────"AMARILLO" MENU DERROTA "NORMAL"──────────────────┐\n");
    printf(" │ "VERDE"C"NORMAL": Cambiar pokemon de combate │\n │ "VERDE"R"NORMAL": Reintentar gimnasio    │\n │ "VERDE"F"NORMAL": Finalizar la partida                         │\n");
    printf(" └─────────────────────────────────────────────────┘\n");
    scanf(" %c", &opcion);

    while(opcion != 'C' && opcion != 'R' && opcion != 'F'){
        printf(" Debes ingresar un comando valido.\n");
        menu_derrota(personaje);    
    }
    if(opcion == 'C'){
        cambiar_pokemon(personaje);
        menu_derrota(personaje);
    }
    return opcion;
}