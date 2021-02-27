#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "evento_pesca.h"

#define ERROR -1
#define MAX_POKEMON 1000
#define POKEMON_RAPIDO 80

#define AZUL_LENTO 'A'
#define GORDITOS 'G'
#define PIPLUP 'P'
#define RAPIDOS 'R'
#define BLANCO_RAPIDO 'B'
#define SI 'S'
#define NO 'N'

#define ROJO "\e[31m"
#define BLANCO "\e[0m"
#define AMARILLO "\e[0;93m"
#define BOLD_AZUL "\e[1;94m"
#define BOLD_AMARILLO "\e[1;93m"
#define BOLD_ROJO "\e[1;91m"
#define BOLD_BLANCO "\e[1;97m"
#define UNDER_BLANCO "\e[4;37m"
#define FONDO_AZUL "\e[44m"

const char* ruta_archivo = "arrecife.txt";

/* Pre: arrecife y acuario creados con todas sus estructuras validas.
 * Post: devuelve un char que representa el pokemon a trasladar.
 */
char pokemon_seleccionado(){

	char letra;

	printf("Desea trasladar:\n\t-pokemon azules y lentos? (Ingrese 'A')\n\t-pokemon gorditos? (Ingrese 'G')\n\t-pokemon de tipo Piplup? (Ingrese 'P')\n\t-pokemon rapidos? (Ingrese 'R')\n\t-pokemon blancos y rapidos? (Ingrese 'B')\n");
	scanf(" %c", &letra);
	while(letra != AZUL_LENTO && letra != GORDITOS && letra != PIPLUP && letra != RAPIDOS && letra != BLANCO_RAPIDO){
		printf("Recuerde ingresar leras validas y en mayuscula!\n");
		printf("Desea trasladar:\n\t-pokemon azules y lentos? (Ingrese 'A')\n\t-pokemon gorditos? (Ingrese 'G')\n\t-pokemon de tipo Piplup? (Ingrese 'P')\n\t-pokemon rapidos? (Ingrese 'R')\n\t-pokemon blancos y rapidos? (Ingrese 'B')\n");
		scanf(" %c", &letra);
	}
	return letra;
}

/* Pre: arrecife y acuario creados con todas sus estructuras validas.
 * Post: devuelve un int que representa la cantidad de pokemones a trasladar.
 */
int cant_a_trasladar(){

	int cant_a_mover;

	printf("Cuantos pokemon desea trasladar al acuario?: \n");
	scanf("%i", &cant_a_mover);

	return cant_a_mover;
}

/* Pre: arrecife y acuario creados con todas sus estructuras validas.
 * Post: 
 */
void seguir_trasladando(char* trasladar){

	printf("Desea trasladar pokemon? (S/N): \n");
	scanf(" %c", trasladar);
	while((*trasladar) != SI && (*trasladar) != NO){
		printf("Debes responder 'S' para trasladar o 'N' para no trasladar\n");
		printf("Desea trasladar pokemon? (S/N): \n");
		scanf(" %c", trasladar);
	}
}

/* Pre: recibe un puntero que apunta a un pokemon.
 * Post: devuelve true si el pokemon es azul y lento y false en caso contrario.
 */
bool es_azul_y_lento(pokemon_t* pokemon){
	return((strcmp(pokemon->color, "azul") == 0) && pokemon->velocidad <= POKEMON_RAPIDO);
}

/* Pre: recibe un puntero que apunta a un pokemon.
 * Post: devuelve true si el pokemon es gordito y false en caso contrario.
 */
bool es_gordito(pokemon_t* pokemon){
	return(pokemon->peso > 50);
}

/* Pre: recibe un puntero que apunta a un pokemon.
 * Post: devuelve true si el pokemon es Piplup y false en caso contrario.
 */
bool es_piplup(pokemon_t* pokemon){
	return((strcmp(pokemon->especie, "Piplup")) == 0);
}

/* Pre: recibe un puntero que apunta a un pokemon.
 * Post: devuelve true si el pokemon es rapido y false en caso contrario.
 */
bool es_rapido(pokemon_t* pokemon){
	return(pokemon->velocidad > POKEMON_RAPIDO);
}

/* Pre: recibe un puntero que apunta a un pokemon.
 * Post: devuelve true si el pokemon es rapido y blanco y false en caso contrario.
 */
bool es_rapido_y_blanco(pokemon_t* pokemon){
	return(((strcmp(pokemon->color, "blanco")) == 0) && pokemon->velocidad > POKEMON_RAPIDO);
}

void mostrar_titulo_1(){

	printf(UNDER_BLANCO "Pokemon en el arrecife:\n");

}

/* Pre: recibe un puntero que apunta a un pokemon.
 * Post: imprime por pantalla los datos del pokemon.
 */
void mostrar_formato_1(pokemon_t* pokemon){
	
	printf("\n");
	printf(BLANCO "%s %i %i %s\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);	
	printf("\n");	
}

void mostrar_titulo_2(){

		printf(AMARILLO " _________________________________\n");
		printf("|                                 |\n");
		printf("|" BOLD_AMARILLO " POKEMON EN EL ARRECIFE:         " AMARILLO "|\n");
		printf("|_________________________________|\n");
}

/* Pre: recibe un puntero que apunta a un pokemon.
 * Post: imprime por pantalla los datos del pokemon.
 */
void mostrar_formato_2(pokemon_t* pokemon){
	
		printf(AMARILLO "|                                 |\n");	
		printf(AMARILLO "|" BLANCO " %-10s %-3i %-3i %-10s   " AMARILLO "|\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
		printf(AMARILLO "|_________________________________|\n" BLANCO);
	
}

void mostrar_titulo_3(){

	printf(BOLD_AZUL "------- ARRECIFE --------\n");
}

/* Pre: recibe un puntero que apunta a un pokemon.
 * Post: imprime por pantalla los datos del pokemon.
 */
void mostrar_formato_3(pokemon_t* pokemon){

	printf(BOLD_AZUL "+-----------------------+\n");
	printf(BOLD_AZUL "|" BLANCO " Nombre:    %10s " BOLD_AZUL "|\n", pokemon->especie);
	printf(BOLD_AZUL "|" BLANCO " Velocidad: %10i " BOLD_AZUL "|\n", pokemon->velocidad);
	printf(BOLD_AZUL "|" BLANCO " Peso:      %10i " BOLD_AZUL "|\n", pokemon->peso);
	printf(BOLD_AZUL "|" BLANCO " Color:     %10s " BOLD_AZUL "|\n", pokemon->color);
	printf("+-----------------------+\n" BLANCO);
}

void mostrar_titulo_4(){

	printf(BOLD_ROJO "                            P" BOLD_BLANCO "O" BOLD_ROJO "K" BOLD_BLANCO "E" BOLD_ROJO "M" BOLD_BLANCO "O" BOLD_ROJO "N" BLANCO "\n");
	printf(BOLD_ROJO " ______________________________________________________________ \n" BLANCO);
}

/* Pre: recibe un puntero que apunta a un pokemon.
 * Post: imprime por pantalla los datos del pokemon.
 */
void mostrar_formato_4(pokemon_t* pokemon){

	printf(BOLD_ROJO "|" BLANCO " %-10s -----> velocidad: %-3i peso: %-3i color: %-10s " BOLD_ROJO "|\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);	
}

void mostrar_titulo_5(){

	printf(FONDO_AZUL " ARRECIFE POKEMON ARRECIFE POKEMON ARRECIFE POKEMON \n" BLANCO);
	printf("          |velocidad: |peso:      |color:     |\n");
	printf("----------|-----------|-----------|-----------|\n");
}

/* Pre: recibe un puntero que apunta a un pokemon.
 * Post: imprime por pantalla los datos del pokemon.
 */
void mostrar_formato_5(pokemon_t* pokemon){

	printf(BOLD_BLANCO "%-10s" BLANCO "|" BLANCO "        %-3i|       %3i | %-10s|\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);	
}

/* Pre: arrecife y acuario creados con todas sus estructuras validas.
 * Post: 
 */
void censar_pokemon(arrecife_t* arrecife){

	int formato = rand() % 4+1;

	switch(formato){
		case 1:
			mostrar_titulo_1();
			censar_arrecife(arrecife, &mostrar_formato_1);
			break;
		case 2:
			mostrar_titulo_2();
			censar_arrecife(arrecife, &mostrar_formato_2);
			break;
		case 3:
			mostrar_titulo_3();
			censar_arrecife(arrecife, &mostrar_formato_3);
			break;
		case 4:
			mostrar_titulo_4();
			censar_arrecife(arrecife, &mostrar_formato_4);
			printf(BOLD_ROJO "|______________________________________________________________|\n" BLANCO);
			break;
		case 5:
			mostrar_titulo_5();
			censar_arrecife(arrecife, &mostrar_formato_5);
			break;
	}		
}

int main(){

	srand((unsigned)time(NULL));
	char trasladar;
	char tipo_pokemon;
	char ver_arrecife;
	int trasladados = 0;
	int cant_seleccion = 0;
		
	arrecife_t* arrecife;
	arrecife = crear_arrecife(ruta_archivo);
	if(arrecife == NULL){
		printf(ROJO "Error al crear arrecife.\n");
		return ERROR;
	}
	
	acuario_t* acuario;
	acuario = crear_acuario();
	if(acuario == NULL){
		printf(ROJO "Error al crear acuario.\n");
		return ERROR;
	}

	seguir_trasladando(&trasladar);

	while(trasladar == SI){

		tipo_pokemon = pokemon_seleccionado();
		cant_seleccion = cant_a_trasladar();

		if(tipo_pokemon == AZUL_LENTO)
			trasladados = trasladar_pokemon(arrecife, acuario, &es_azul_y_lento, cant_seleccion);
		else if(tipo_pokemon == GORDITOS)
			trasladados = trasladar_pokemon(arrecife, acuario, &es_gordito, cant_seleccion);
		else if(tipo_pokemon == PIPLUP)
			trasladados = trasladar_pokemon(arrecife, acuario, &es_piplup, cant_seleccion);
		else if(tipo_pokemon == RAPIDOS)
			trasladados = trasladar_pokemon(arrecife, acuario, &es_rapido, cant_seleccion);
		else if(tipo_pokemon == BLANCO_RAPIDO)
			trasladados = trasladar_pokemon(arrecife, acuario, &es_rapido_y_blanco, cant_seleccion);

		if(trasladados == ERROR){
			printf(ROJO "Error al trasladar pokemon.\n");
			liberar_acuario(acuario);
			liberar_arrecife(arrecife);	
			return ERROR;		
		}

		printf("Desea ver a los tipos de pokemon que hay en el errecife? (S/N): \n");
		scanf(" %c", &ver_arrecife);
		while(ver_arrecife != SI && ver_arrecife != NO){
			printf("Debes responder 'S' para ver el arrecife o 'N' para seguir\n");
			printf("Desea trasladar pokemon? (S/N): \n");
			scanf(" %c", &ver_arrecife);
		}

		if(ver_arrecife == SI){
			censar_pokemon(arrecife);					
		}

		seguir_trasladando(&trasladar);
	}

	guardar_datos_acuario(acuario, ruta_archivo);

	liberar_arrecife(arrecife);
	liberar_acuario(acuario);
	return 0;
}