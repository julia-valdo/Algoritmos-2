#include <stdio.h>
#include <stdlib.h>
#include "evento_pesca.h"

#define FORMATO_ARRECIFE "%100[^;];%i;%i;%50[^\n]\n"
#define FORMATO_ACUARIO "%s;%i;%i;%s\n"
#define ERROR -1
#define OK 0
#define ROJO "\e[31m"

const char* ruta_archivo_acuario = "acuario.txt";

/* Pre: recibe un puntero a arrecife y un archivo abierto.
 * Post: devuelve 0 en caso de leer el archivo correctamente y asignar correctamente la memoria para los pokemon, y ERROR en caso contrario.
 */
int cargar_arrecife(arrecife_t* arrecife, FILE* arch_arrecife){

	int leidos = fscanf(arch_arrecife, FORMATO_ARRECIFE, arrecife->pokemon[arrecife->cantidad_pokemon].especie, &(arrecife)->pokemon[arrecife->cantidad_pokemon].velocidad, &(arrecife)->pokemon[arrecife->cantidad_pokemon].peso, arrecife->pokemon[arrecife->cantidad_pokemon].color);
	if(leidos != 4){
		printf(ROJO "Error al leer el archivo de arrecife.\n");
		free(arrecife->pokemon);
		free(arrecife);
		return ERROR;
	}

	while(leidos == 4){
		arrecife->cantidad_pokemon++;
		pokemon_t* pokemon_aux = realloc(arrecife->pokemon, (size_t)(arrecife->cantidad_pokemon+1)*(sizeof(pokemon_t)));
		if(pokemon_aux == NULL){
			printf(ROJO "Fallo al aumentar el vector de pokemon.\n");
			free(arrecife->pokemon);
			free(arrecife);
			return ERROR;
		}
		arrecife->pokemon = pokemon_aux;
		leidos = fscanf(arch_arrecife, FORMATO_ARRECIFE, arrecife->pokemon[arrecife->cantidad_pokemon].especie, &(arrecife)->pokemon[arrecife->cantidad_pokemon].velocidad, &(arrecife)->pokemon[arrecife->cantidad_pokemon].peso, arrecife->pokemon[arrecife->cantidad_pokemon].color);
	}
	return OK;
}

arrecife_t* crear_arrecife(const char* ruta_archivo){

	if(ruta_archivo[0] == '\0'){
		return NULL;
	}

	FILE* arch_arrecife = fopen(ruta_archivo, "r");
	if(!arch_arrecife){
		printf(ROJO "Error al abrir el archivo de arrecife.\n");
		return NULL;
	}

	arrecife_t* arrecife = malloc(sizeof(arrecife_t));
	if(arrecife == NULL){
		printf(ROJO "Error. Fallo malloc()\n");
		fclose(arch_arrecife);
		return NULL;
	}
	
	arrecife->pokemon = malloc(sizeof(pokemon_t));
	if(arrecife->pokemon == NULL){
		printf(ROJO "Error. Fallo malloc()\n");
		free(arrecife);
		fclose(arch_arrecife);
		return NULL;
	}

	arrecife->cantidad_pokemon = 0;

	if(cargar_arrecife(arrecife, arch_arrecife) == ERROR){
		fclose(arch_arrecife);
		return NULL;
	}
	
	fclose(arch_arrecife);
	return arrecife;
}

acuario_t* crear_acuario(){

	acuario_t* acuario = malloc(1 * sizeof(acuario_t));
	if(acuario == NULL){
		printf(ROJO "Error. Fallo malloc()\n");
		return NULL;
	}

	acuario->pokemon = NULL;
	acuario->cantidad_pokemon = 0;

	return acuario;
}

/* Pre: recibe un puntero a arrecife y una posicion.
 * Post: el vector queda con el pokemon que quiero eliminar en la ultima posicion.
 */
void swapeo_a_ultima_posicion(arrecife_t* arrecife, int posicion){

	pokemon_t pokemon_aux;

	pokemon_aux = arrecife->pokemon[posicion];	
	arrecife->pokemon[posicion] = arrecife->pokemon[arrecife->cantidad_pokemon-1];	
	arrecife->pokemon[arrecife->cantidad_pokemon-1] = pokemon_aux;
}

/* Pre: recibe un puntero a arrecife y un puntero a acuario.
 * Post: devuelve 0 si se pudo mover el ultimo pokemon a trasladar al acuario, asignando la memoria necesaria, o ERROR en caso contrario.
 */
int mover_ultimo_pokemon(arrecife_t* arrecife, acuario_t* acuario){

	pokemon_t* pokemon_aux;

	pokemon_aux = realloc(acuario->pokemon, (size_t)(acuario->cantidad_pokemon + 1)*sizeof(pokemon_t));
	if(pokemon_aux == NULL){
		return ERROR;
	}
	acuario->pokemon = pokemon_aux;

	acuario->pokemon[acuario->cantidad_pokemon] = arrecife->pokemon[arrecife->cantidad_pokemon-1]; 
	acuario->cantidad_pokemon++;

	free(arrecife->pokemon);
	arrecife->pokemon = NULL;
	arrecife->cantidad_pokemon--;	

	return OK;
}

/* Pre: recibe un puntero a arrecife, un puntero a acuario y una posicion.
 * Post: devuelve 0 si se pudo mover el pokemon del arrecife al acuario, asignando la memoria necesaria, o ERROR en caso contrario.
 */
int mover_pokemon(arrecife_t* arrecife, acuario_t* acuario, int posicion){

	pokemon_t* pokemon_aux;
	pokemon_t* pokemon_aux2;

	pokemon_aux = realloc(acuario->pokemon, (size_t)(acuario->cantidad_pokemon + 1)*sizeof(pokemon_t));
	if(pokemon_aux == NULL){
		return ERROR;
	}
	acuario->pokemon = pokemon_aux;
	acuario->pokemon[acuario->cantidad_pokemon] = arrecife->pokemon[posicion]; 
	acuario->cantidad_pokemon++;

	swapeo_a_ultima_posicion(arrecife, posicion);

	pokemon_aux2 = realloc(arrecife->pokemon, (size_t)(arrecife->cantidad_pokemon-1)*sizeof(pokemon_t));	
	if(pokemon_aux2 == NULL){
		return ERROR;
	}
	arrecife->pokemon = pokemon_aux2;
	arrecife->cantidad_pokemon--;

	return OK;
}

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon)(pokemon_t*), int cant_seleccion){

	int j = 0;
	int posibles_traslados = 0;	
	int movidos = 0;
	int chequeo_mover = 0;
	int chequeo_mover_ultimo = 0;

	if(cant_seleccion <= arrecife->cantidad_pokemon){

		for(int i = 0; i < arrecife->cantidad_pokemon; i++){
			if((*seleccionar_pokemon)(&(arrecife->pokemon[i]))){ 
				posibles_traslados++;
			}
		}

		if(posibles_traslados == 0){
			printf("No hay pokemon para trasladar!\n");
			return ERROR;
		}if(posibles_traslados < cant_seleccion){
			printf("Queres trasladar mas pokemones de los que hay en el arrecife!\n");
			return ERROR;
		}else{
			while(movidos < cant_seleccion){

				if((*seleccionar_pokemon)(&(arrecife->pokemon[j]))){
					if(arrecife->cantidad_pokemon == 1){
						chequeo_mover_ultimo = mover_ultimo_pokemon(arrecife, acuario);
						if(chequeo_mover_ultimo == ERROR){						
							return ERROR;
						}
					}else{
						chequeo_mover = mover_pokemon(arrecife, acuario, j);
						if(chequeo_mover == ERROR){						
							return ERROR;
						}
						j--;					
					}
					movidos++;
				}
				j++;
			}
		}
	}else{
		printf("Queres trasladar mas pokemones de los que hay en el arrecife!\n");
		return ERROR;
	}
	return OK;
}

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){	
	for(int i = 0; i < arrecife->cantidad_pokemon; i++){
		(*mostrar_pokemon)(&(arrecife->pokemon[i]));
	}
}

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){

	FILE* arch_acuario = fopen(ruta_archivo_acuario, "w");
	if(!arch_acuario){
		printf(ROJO "Error al abrir el archivo de acuario.\n");
		return ERROR;
	}

	for(int i = 0; i < acuario->cantidad_pokemon; i++){
		fprintf(arch_acuario, FORMATO_ACUARIO, acuario->pokemon[i].especie, acuario->pokemon[i].velocidad, acuario->pokemon[i].peso, acuario->pokemon[i].color);
	}

	fclose(arch_acuario);
	return OK;
}

void liberar_acuario(acuario_t* acuario){

	free(acuario->pokemon);
	free(acuario);
}

void liberar_arrecife(arrecife_t* arrecife){

	free(arrecife->pokemon);	
	free(arrecife);
}