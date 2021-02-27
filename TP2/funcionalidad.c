#include "funcionalidad.h"
#include "structs.h"
#include "heap.h"
#include "lista.h"
#include "batallas.h"
#include "interacciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARACTERES 50
#define ERROR -1
#define OK 0
#define CANT_POKEMON_COMBATE 6
#define GANO 1
#define PERDIO 0
#define MAX_BATALLAS 5
#define MAX_POKEMON 6
#define GANO_ENTRENADOR -1
#define MAX_ENTRENADORES 50
#define MAX_GIMNASIOS 10

#define GIMNASIO 'G'
#define LIDER 'L'
#define ENTRENADOR 'E'
#define POKEMON 'P'
#define SIMULACION 'S'
#define REINTENTAR 'R'
#define FINALIZAR 'F'

#define FORMATO_STANDAR "%c;%50[^\n]\n"
#define FORMATO_GIMNASIO "%50[^;];%i;%i\n"
#define FORMATO_ENTRENADOR "%50[^\n]\n"
#define FORMATO_POKEMON "%50[^;];%i;%i;%i\n"

#define ROJO "\x1b[91m"
#define AMARILLO "\x1b[93m"
#define VERDE "\x1b[92m"
#define MAGENTA "\x1b[95m"
#define NORMAL "\x1b[0m"
#define TILDE "✓"
#define CRUZ "✗"
#define FLECHA "→"

void destruir_pokemon(entrenador_t* entrenador){
    while(entrenador->lista_pokemon->cantidad > 0){        
        free((pokemon_t*)lista_ultimo(entrenador->lista_pokemon));  
        lista_borrar(entrenador->lista_pokemon);           
    }
    lista_destruir(entrenador->lista_pokemon);
}

void destruir_gimnasio(gimnasio_t* gimnasio){   
    while(gimnasio->pila_entrenadores->cantidad > 0){
        destruir_pokemon((entrenador_t*)lista_ultimo(gimnasio->pila_entrenadores));  
        free(lista_ultimo(gimnasio->pila_entrenadores));
        lista_desapilar(gimnasio->pila_entrenadores);      
    }
    lista_destruir(gimnasio->pila_entrenadores);
    free(gimnasio);
}

void destructor_de_gimnasios(void* elemento){
    if(!elemento) return;
    destruir_gimnasio((gimnasio_t*)elemento);
}

void destruir_personaje(personaje_principal_t* personaje){
    while(personaje->lista_pokemon_obtenidos->cantidad > 0){
        free((pokemon_t*)lista_ultimo(personaje->lista_pokemon_obtenidos));
        lista_borrar(personaje->lista_pokemon_obtenidos);
    }
    lista_destruir(personaje->lista_pokemon_obtenidos);
    lista_destruir(personaje->cola_pokemon_combate);
    free(personaje);
}

personaje_principal_t* crear_personaje(){
    personaje_principal_t* personaje =  calloc(1, sizeof(personaje_principal_t));
    if(!personaje) return NULL;
    return personaje;
}

/*
 * Asigna una batalla al gimnasio. 
 */
void asignar_batalla(gimnasio_t* gimnasio, int id_puntero_funcion){

    gimnasio->id_puntero_funcion = (id_puntero_funcion--);

    int (*batallas[MAX_BATALLAS])(void*, void*);
    batallas[0] = funcion_batalla_1;
    batallas[1] = funcion_batalla_2;
    batallas[2] = funcion_batalla_3;
    batallas[3] = funcion_batalla_4;
    batallas[4] = funcion_batalla_5;
    for(int i = 0; i < MAX_BATALLAS; i++){
        if(i == id_puntero_funcion)
            gimnasio->batalla = batallas[i];
    }
}

/*
 * Crea el gimnasio reservando la memoria necesaria.
 * Devuelve un puntero a el gimnasio creado o NULL en caso de error.
 */
gimnasio_t* crear_gimnasio(char linea[MAX_CARACTERES]){
    
    char nombre_gimnasio[MAX_NOMBRE];
    int dificultad = 0;
    int id_puntero_funcion = 0;

    gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
    if(!gimnasio) return NULL;
      
    int leidos = sscanf(linea, FORMATO_GIMNASIO, nombre_gimnasio, &dificultad, &id_puntero_funcion);
    if(leidos != 3) return NULL;
        
    strcpy(gimnasio->nombre, nombre_gimnasio);
    gimnasio->dificultad = dificultad;
    asignar_batalla(gimnasio, id_puntero_funcion);
    
    return gimnasio;  
}

/*
 * Crea el entrenador reservando la memoria necesaria.
 * Devuelve un puntero a el entrenador creado o NULL en caso de error.
 */
entrenador_t* crear_entrenador(char linea[MAX_CARACTERES]){

    char nombre_entrenador[MAX_NOMBRE];    
    
    entrenador_t* entrenador =  calloc(1, sizeof(entrenador_t));
    if(!entrenador) return NULL;

    int leidos = sscanf(linea, FORMATO_ENTRENADOR, nombre_entrenador);
    if(leidos != 1) return NULL;

    strcpy(entrenador->nombre, nombre_entrenador);
    return entrenador;
}

/*
 * Crea el pokemon reservando la memoria necesaria.
 * Devuelve un puntero a el pokemon creado o NULL en caso de error.
 */
pokemon_t* crear_pokemon(char linea[MAX_CARACTERES]){

    char nombre_pokemon[MAX_NOMBRE];
    int velocidad = 0;
    int ataque = 0;
    int defensa = 0;

    pokemon_t* pokemon =  calloc(1, sizeof(pokemon_t));    
    if(!pokemon) return NULL;

    int leidos = sscanf(linea, FORMATO_POKEMON, nombre_pokemon, &velocidad, &ataque, &defensa);
    if(leidos != 4) return NULL; 

    strcpy(pokemon->nombre, nombre_pokemon);
    pokemon->velocidad = velocidad;
    pokemon->ataque = ataque;
    pokemon->defensa = defensa;
    return pokemon;
}

/*
 * Lee la informacion del archivo de gimnasio/s y carga la informacion leida a los stucts previamente creados.
 * Los structs se insertan en sus respectivos TDAs.
 * Devuelve -1 en caso de error y 1 en caso contrario.
 */
int leer_archivo_gimnasio(FILE* archivo_gimnasio, heap_t* heap_gimnasios){

    char linea_fgets[MAX_CARACTERES];
    char linea_sscanf[MAX_CARACTERES];
    char letra;    

    char* linea = fgets(linea_fgets, MAX_CARACTERES, archivo_gimnasio);
    int leidos = sscanf(linea_fgets, FORMATO_STANDAR, &letra, linea_sscanf);
    if(letra != GIMNASIO || leidos != 2) return ERROR;    
    
    while(linea){
        if(letra == GIMNASIO){
            gimnasio_t* gimnasio = crear_gimnasio(linea_sscanf);
            if(!gimnasio) return ERROR;
                       
            lista_t* pila_entrenadores = lista_crear();
            if(!pila_entrenadores) return ERROR;
            
            linea = fgets(linea_fgets, MAX_CARACTERES, archivo_gimnasio);
            leidos = sscanf(linea_fgets, FORMATO_STANDAR, &letra, linea_sscanf);
            while(letra == LIDER || letra == ENTRENADOR){
                if(leidos != 2) return ERROR;    
                
                entrenador_t* entrenador = crear_entrenador(linea_sscanf);
                if(!entrenador) return ERROR;
                              
                lista_t* lista_pokemon = lista_crear();
                if(!lista_pokemon) return ERROR; 
                  
                linea = fgets(linea_fgets, MAX_CARACTERES, archivo_gimnasio);
                leidos = sscanf(linea_fgets, FORMATO_STANDAR, &letra, linea_sscanf);                
                while(letra == POKEMON && linea){
                    if(leidos != 2) return ERROR;    
                    
                    pokemon_t* pokemon = crear_pokemon(linea_sscanf);
                    if(!pokemon) return ERROR;
                                                           
                    if(lista_insertar(lista_pokemon, pokemon) != 0) return ERROR;
                    
                    linea = fgets(linea_fgets, MAX_CARACTERES, archivo_gimnasio);
                    leidos = sscanf(linea_fgets, FORMATO_STANDAR, &letra, linea_sscanf);
                }
                entrenador->lista_pokemon = lista_pokemon;
                if(lista_apilar(pila_entrenadores, entrenador) != 0) return ERROR;
                
            }    
            gimnasio->pila_entrenadores = pila_entrenadores;         
            if(heap_insertar(heap_gimnasios, gimnasio) != 0) return ERROR;            
        }        
    }
    return OK;
}

int cargar_gimnasios(const char* nombre_archivo, heap_t* heap_gimnasios){

    if(nombre_archivo[0] == '\0') return ERROR;

    FILE* archivo_gimnasio = fopen(nombre_archivo, "r");
    if(!archivo_gimnasio){
		printf(ROJO CRUZ " Error al abrir el archivo de gimnasio/s.\n" NORMAL);
		return ERROR;
	}
    
    int lectura = leer_archivo_gimnasio(archivo_gimnasio, heap_gimnasios);
    if(lectura == ERROR) printf(ROJO CRUZ " Error al leer el archivo de gimnasio/s.\n" NORMAL);
    
    fclose(archivo_gimnasio);
    return lectura;
}

/*
 * Encola los primeros 6 pokemon de la lista de pokemon obtenidos en la cola de pokemon de combate.
 * Asigna la cola de pokemon de combate al struct del personaje.
 */
void guardar_pokemon_combate(personaje_principal_t* personaje, lista_t* cola_pokemon_combate, size_t cant_pokemon_obtenido){
   
    size_t cant_pokemon_combate = 0;
    pokemon_t* pokemon_combate;

    if(cant_pokemon_obtenido < CANT_POKEMON_COMBATE) cant_pokemon_combate = cant_pokemon_obtenido;
    else cant_pokemon_combate = CANT_POKEMON_COMBATE;

    for(size_t i = 0; i < cant_pokemon_combate; i++){
        pokemon_combate = (pokemon_t*)lista_elemento_en_posicion(personaje->lista_pokemon_obtenidos, i);
        lista_encolar(cola_pokemon_combate, pokemon_combate);        
    }
    personaje->cola_pokemon_combate = cola_pokemon_combate;    
}

/*
 * Lee la informacion del archivo de el personjae y carga la informacion leida a los stucts previamente creados.
 * Los structs se insertan en sus respectivos TDAs.
 * Devuelve -1 en caso de error y 1 en caso contrario.
 */
int leer_archivo_personaje(FILE* archivo_personaje, personaje_principal_t* personaje){

    size_t cant_pokemon_obtenido = 0;

    char linea_fgets[MAX_CARACTERES];
    char linea_sscanf[MAX_CARACTERES];    
    char letra;  

    lista_t* lista_pokemon_obtenidos = lista_crear();
    if(!lista_pokemon_obtenidos) return ERROR;    
    
    lista_t* cola_pokemon_combate = lista_crear();
    if(!cola_pokemon_combate) return ERROR;
    
    char* linea = fgets(linea_fgets, MAX_CARACTERES, archivo_personaje);
    int leidos = sscanf(linea_fgets, FORMATO_STANDAR, &letra, linea_sscanf);
    if(letra != ENTRENADOR || leidos != 2) return ERROR;    
           
    while(linea){
        strcpy(personaje->nombre, linea_sscanf);
        linea = fgets(linea_fgets, MAX_CARACTERES, archivo_personaje);
        leidos = sscanf(linea_fgets, FORMATO_STANDAR, &letra, linea_sscanf);  
        while(letra == POKEMON && linea){
            if(leidos != 2) return ERROR;    
                      
            pokemon_t* pokemon = crear_pokemon(linea_sscanf);
            if(!pokemon) return ERROR;
            
            if(lista_insertar(lista_pokemon_obtenidos, pokemon) != 0) return ERROR;
            
            cant_pokemon_obtenido++;
            linea = fgets(linea_fgets, MAX_CARACTERES, archivo_personaje);
            leidos = sscanf(linea_fgets, FORMATO_STANDAR, &letra, linea_sscanf);
        }        
    }
    personaje->lista_pokemon_obtenidos = lista_pokemon_obtenidos;
    guardar_pokemon_combate(personaje, cola_pokemon_combate, cant_pokemon_obtenido);
    return OK;
}

int cargar_personaje(const char* nombre_archivo, personaje_principal_t* personaje){
    
    if(nombre_archivo[0] == '\0') return ERROR;

    FILE* archivo_personaje = fopen(nombre_archivo, "r");
    if(!archivo_personaje){
		printf(ROJO CRUZ " Error al abrir el archivo de personaje.\n");
		return ERROR;
	}

    int lectura = leer_archivo_personaje(archivo_personaje, personaje); 
    if(lectura == ERROR) printf(ROJO CRUZ " Error al leer el archivo de personaje.\n" NORMAL);

    fclose(archivo_personaje);
    return lectura;
}

/*
 * Guarda los pokemon derrotados en batalla.
 */
void guardar_pokemon(pokemon_t* pokemon_derrotado_entrenador[MAX_POKEMON], entrenador_t* entrenador, pokemon_t* pokemon_derrotado_personaje[MAX_POKEMON], personaje_principal_t* personaje, size_t derrotas_entrenador, size_t derrotas_personaje){
    for(size_t i = 0; i < derrotas_entrenador; i++) 
        lista_insertar(entrenador->lista_pokemon, pokemon_derrotado_entrenador[i]);  
    
    for(size_t i = 0; i < derrotas_personaje; i++)
        lista_encolar(personaje->cola_pokemon_combate, pokemon_derrotado_personaje[i]);  
}

/*
 * Guarda los entrenadores derrotados en batalla.
 */
void guardar_entrenadores(entrenador_t* vector_entrenadores[MAX_ENTRENADORES], size_t entrenadores_derrotados, gimnasio_t* gimnasio){
    for(size_t i = 0; i < entrenadores_derrotados; i++)
        lista_apilar(gimnasio->pila_entrenadores, vector_entrenadores[i]); 
}

/*
 * Aumenta en 1 las caracteristicas del pokemon recibido.
 */
void aumentar_caracteristicas(pokemon_t* pokemon){
    if(pokemon->mejora == 63) return;
    pokemon->velocidad++;
    pokemon->defensa++;
    pokemon->ataque++;
    pokemon->mejora++;
}

/*
 *
 */
int batalla_entrenadores(entrenador_t* entrenador, personaje_principal_t* personaje, int batalla(void*, void*), char opcion_partida){

    int ganador = 0;
    bool perdio_personaje = false;

    size_t derrotas_personaje = 0;
    size_t derrotas_entrenador = 0;
    pokemon_t* pokemon_derrotado_entrenador[MAX_POKEMON];
    pokemon_t* pokemon_derrotado_personaje[MAX_POKEMON];

    pokemon_t* pokemon_personaje = (pokemon_t*)lista_primero(personaje->cola_pokemon_combate);
    pokemon_t* pokemon_entrenador = (pokemon_t*)lista_primero(entrenador->lista_pokemon);

    while(!lista_vacia(entrenador->lista_pokemon) && !perdio_personaje){
        menu_batalla(personaje, pokemon_personaje, entrenador, pokemon_entrenador, ganador, opcion_partida);
        ganador = batalla(pokemon_personaje, pokemon_entrenador);
        if(ganador == GANO_ENTRENADOR){ 
            pokemon_derrotado_personaje[derrotas_personaje] = pokemon_personaje;
            derrotas_personaje++;
            lista_desencolar(personaje->cola_pokemon_combate);
            if(lista_vacia(personaje->cola_pokemon_combate))                
                perdio_personaje = true;            
            pokemon_personaje = (pokemon_t*)lista_primero(personaje->cola_pokemon_combate);
        }else{
            pokemon_derrotado_entrenador[derrotas_entrenador] = pokemon_entrenador;
            derrotas_entrenador++;
            aumentar_caracteristicas(pokemon_personaje);
            lista_borrar_de_posicion(entrenador->lista_pokemon, 0);
            pokemon_entrenador = (pokemon_t*)lista_primero(entrenador->lista_pokemon);       
        }        
    }
    guardar_pokemon(pokemon_derrotado_entrenador, entrenador, pokemon_derrotado_personaje, personaje, derrotas_entrenador, derrotas_personaje);
    
    if(perdio_personaje) return PERDIO;
    else return GANO; 
}

int pelear(gimnasio_t* gimnasio, personaje_principal_t* personaje, char opcion_partida){

    int resultado_batalla = 0;
    size_t entrenadores_derrotados = 0;
    entrenador_t* entrenador;
    entrenador_t* vector_entrenadores[MAX_ENTRENADORES];

    while(!lista_vacia(gimnasio->pila_entrenadores)){
        entrenador = (entrenador_t*)lista_ultimo(gimnasio->pila_entrenadores);
        resultado_batalla = batalla_entrenadores(entrenador, personaje, gimnasio->batalla, opcion_partida);
        if(resultado_batalla == GANO){
            vector_entrenadores[entrenadores_derrotados] = entrenador;
            entrenadores_derrotados++;
            lista_desapilar(gimnasio->pila_entrenadores);
        }
        else break;        
    } 
    guardar_entrenadores(vector_entrenadores, entrenadores_derrotados, gimnasio);    
    return resultado_batalla;
}

int main(){

    char archivo_personaje[MAX_NOMBRE];
    char archivo_gimnasio[MAX_GIMNASIOS][MAX_NOMBRE];
    int cantidad_gimnasios = 0;

    personaje_principal_t* personaje = crear_personaje();
    if(!personaje){
        printf(ROJO CRUZ NORMAL "Error al crear el personaje principal.\n" NORMAL);
        return ERROR;
    }

    heap_t* heap_gimnasios = heap_crear(destructor_de_gimnasios);
    if(!heap_gimnasios){
        printf(ROJO CRUZ NORMAL" Error al crear el gimnasio.\n");
        return ERROR;
    }
    
    char opcion_partida = menu_inicio(archivo_personaje, archivo_gimnasio, &cantidad_gimnasios);
    
    int cargar = cargar_personaje(archivo_personaje, personaje);
    if(cargar != OK) return ERROR;    
    
    int cargar_gimnasio = 0;
    for(int i = 0; i < cantidad_gimnasios; i++){
        cargar_gimnasio = cargar_gimnasios(archivo_gimnasio[i], heap_gimnasios);
        if(cargar_gimnasio != OK) return ERROR;
    }
    
    int pelea = 0;
    gimnasio_t* gimnasio;
    for(int i = 0; i < heap_gimnasios->tope; i++){
        gimnasio = heap_gimnasios->vector[i];
        if(opcion_partida != SIMULACION)  
            menu_gimnasio(gimnasio, personaje);      
        pelea = pelear(gimnasio, personaje, opcion_partida);        
        if(pelea == PERDIO){
            if(opcion_partida != SIMULACION){ 
                char opcion_derrota = menu_derrota(personaje);
                if(opcion_derrota == REINTENTAR)
                    pelea = pelear(gimnasio, personaje, opcion_partida);
                else if(opcion_derrota == FINALIZAR){
                    printf("PERDISTE\n");
                    destruir_personaje(personaje);
                    heap_destruir(heap_gimnasios);
                    return 0;
                }
            }            
        }
        else if(pelea == GANO){
            if(opcion_partida != SIMULACION) 
                menu_victoria(personaje, gimnasio);
        }
    }    
    printf("TE CONVERTISTE EN MAESTRO POKEMON\n");
    destruir_personaje(personaje);
    heap_destruir(heap_gimnasios);
    return OK;
}