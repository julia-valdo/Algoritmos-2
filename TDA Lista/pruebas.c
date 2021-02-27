#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

#define BLANCO "\x1b[37;1m"
#define VERDE "\x1b[32;1m"
#define ROJO "\x1b[31;1m"
#define AMARILLO "\x1b[33;1m"
#define NORMAL "\x1b[0m"
#define FONDO "\x1b[1;90m"
#define TILDE "✓"
#define CRUZ "✗"
#define FLECHA "→"

#define ERROR -1
#define LISTA_VACIA 0
#define POSICION_FINAL 50 // debe ser si o si mayor o igual que PRUEBA_VOLUMEN.
#define POSICION 2
#define POSICION_INICIO 0
#define POSICION_DESPUES_INICIO 1
#define PRUEBA_VOLUMEN 10 // se puede aumentar considerablemente el valor para insertar mas cosas.
#define ELEMENTO_INICIO 0
#define ELEMENTO_PRUEBA 3
#define ELEMENTO_FIN 4

void afirmar(char* descripcion, bool afirmacion, int* pruebas_pasadas, int* cantidad_pruebas){

	if(!descripcion || !pruebas_pasadas || !cantidad_pruebas)
		return;

	if(afirmacion){
		(*pruebas_pasadas)++;
	}
	printf("%s %s\n", afirmacion? VERDE TILDE NORMAL : ROJO CRUZ NORMAL, descripcion);

	(*cantidad_pruebas)++;
}

bool mostrar_elemento(void* elemento, void* contador){

    if(elemento && contador)
        printf("Elemento %i: %i\n", (*(int*)contador)++, *(int*)elemento);

    return true;
}

bool destruir_elemento(void* elemento, void* contador){

	int* elemento_a_borrar = (int*)elemento;

	free(elemento_a_borrar);

	return true;
}

/*
 * destruye la lista cargada usnando un iterador interno.
 */
void destruir_lista_cargada(lista_t* lista){

	if(!lista)
		return;

	lista_con_cada_elemento(lista, destruir_elemento, NULL);
	lista_destruir(lista);
}

/*
 * devuelve un puntero a una lista con elementos, reservados en memoria, cargados en ella.
 */
lista_t* crear_lista_cargada(){

	int* elemento_0 = malloc(sizeof(int));
	if(!elemento_0)	
		return NULL;
	int* elemento_1 = malloc(sizeof(int));
	if(!elemento_1){
		free(elemento_0);
		return NULL;
	}
	int* elemento_2 = malloc(sizeof(int));
	if(!elemento_2){
		free(elemento_0);
		free(elemento_1);
		return NULL;
	}
	int* elemento_3 = malloc(sizeof(int));
	if(!elemento_3){	
		free(elemento_0);
		free(elemento_1);
		free(elemento_2);
		return NULL;
	}
	int* elemento_4 = malloc(sizeof(int));
	if(!elemento_4){
		free(elemento_0);
		free(elemento_1);
		free(elemento_2);
		free(elemento_3);
		return NULL;
	}
	int* elemento_5 = malloc(sizeof(int));
	if(!elemento_5){
		free(elemento_0);
		free(elemento_1);
		free(elemento_2);
		free(elemento_3);
		free(elemento_4);
		return NULL;
	}

	*elemento_0 = 0;
	*elemento_1 = 1;
	*elemento_2 = 2;
	*elemento_3 = 3;
	*elemento_4 = 4;
	*elemento_5 = 5;

	lista_t* lista = lista_crear();

	lista_insertar(lista, elemento_0);	
	lista_insertar(lista, elemento_1);	
	lista_insertar(lista, elemento_2);	
	lista_insertar(lista, elemento_3);	
	lista_insertar(lista, elemento_4);	
	lista_insertar(lista, elemento_5);	

	return lista;
}

void probar_creacion_lista(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;
	lista = lista_crear();

	afirmar("Lista creada correctamente", lista != NULL, pruebas_pasadas, cantidad_pruebas);
	afirmar("La lista se crea vacia", lista->cantidad == 0, pruebas_pasadas, cantidad_pruebas);
	afirmar("Lista creada con un nodo_inicio nulo", lista->nodo_inicio == NULL, pruebas_pasadas, cantidad_pruebas);
	afirmar("Lista creada con un nodo_fin nulo", lista->nodo_fin == NULL, pruebas_pasadas, cantidad_pruebas);

	lista_destruir(lista);
}

void probar_lista_insertar(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;
	int elemento = ELEMENTO_PRUEBA;
	int elementos_insertados = 0;
	size_t cantidad_elementos = 0;

	afirmar("No se puede insertar con una lista nula", lista_insertar(lista, &elemento) == ERROR, pruebas_pasadas, cantidad_pruebas);

	lista = lista_crear();	

	afirmar("Se inserta el primer elemento", lista_insertar(lista, &elemento) != ERROR, pruebas_pasadas, cantidad_pruebas);
	afirmar("Primer elemento insertado correctamente", *(int*)lista_elemento_en_posicion(lista, POSICION_INICIO) == elemento, pruebas_pasadas, cantidad_pruebas);
	if(*(int*)lista_elemento_en_posicion(lista, POSICION_INICIO) == elemento)
		elementos_insertados++;

	afirmar("Se inserta un elemento", lista_insertar(lista, &elemento) != ERROR, pruebas_pasadas, cantidad_pruebas);
	afirmar("Elemento insertado correctamente", *(int*)lista_elemento_en_posicion(lista, (size_t)elementos_insertados) == elemento, pruebas_pasadas, cantidad_pruebas);
	if(*(int*)lista_elemento_en_posicion(lista, (size_t)elementos_insertados) == elemento)
		elementos_insertados++;

	printf(BLANCO FLECHA " Inserto muchos elementos\n" NORMAL);
	for(int i = 0; i < PRUEBA_VOLUMEN; i++){
		lista_insertar(lista, &elemento);	
		elementos_insertados++;
	}

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);

	afirmar("Muchos elementos insertados correctamente", lista->cantidad == elementos_insertados, pruebas_pasadas, cantidad_pruebas);

	lista_destruir(lista);
}

void probar_lista_insertar_en_posicion(int* pruebas_pasadas, int* cantidad_pruebas){
	
	lista_t* lista = NULL;	
	int elemento_inicio = ELEMENTO_INICIO;
	int elemento_siguiente = ELEMENTO_INICIO + 1;
	int elemento_fin = ELEMENTO_FIN;
	int elemento = ELEMENTO_PRUEBA;
	size_t elementos_insertados = 0;
	size_t cantidad_elementos = 0;

	afirmar("No se puede insertar en posicion con una lista nula", lista_insertar_en_posicion(lista, &elemento, POSICION) == ERROR, pruebas_pasadas, cantidad_pruebas);

	lista = lista_crear();	
	
	afirmar("Se inserta el primer elemento", lista_insertar_en_posicion(lista, &elemento, POSICION) != ERROR, pruebas_pasadas, cantidad_pruebas);
	afirmar("Primer elemento insertado correctamente", *(int*)lista->nodo_inicio->elemento == elemento, pruebas_pasadas, cantidad_pruebas);
	if(*(int*)lista_elemento_en_posicion(lista, POSICION_INICIO) == elemento)
		elementos_insertados++;

	printf(BLANCO FLECHA " Inserto muchos elementos\n" NORMAL);
	for(int i = 0; i < PRUEBA_VOLUMEN; i++){
		lista_insertar(lista, &elemento);
		elementos_insertados++;
	}

	afirmar("Elemento insertado en la posicion 0", lista_insertar_en_posicion(lista, &elemento_inicio, POSICION_INICIO) != ERROR, pruebas_pasadas, cantidad_pruebas);
	if(*(int*)lista_elemento_en_posicion(lista, POSICION_INICIO) == elemento_inicio)
		elementos_insertados++;

	afirmar("Elemento insertado en la posicion 1", lista_insertar_en_posicion(lista, &elemento_siguiente, POSICION_DESPUES_INICIO) != ERROR, pruebas_pasadas, cantidad_pruebas);
	if(*(int*)lista_elemento_en_posicion(lista, POSICION_DESPUES_INICIO) == elemento_siguiente)
		elementos_insertados++;

	afirmar("Elemento insertado al final", lista_insertar_en_posicion(lista, &elemento_fin, POSICION_FINAL) != ERROR, pruebas_pasadas, cantidad_pruebas);
	if(*(int*)lista_elemento_en_posicion(lista, elementos_insertados) == elemento_fin)
		elementos_insertados++;

	afirmar("Elemento insertado en la posicion 2", lista_insertar_en_posicion(lista, &elemento, POSICION) != ERROR, pruebas_pasadas, cantidad_pruebas);
	if(*(int*)lista_elemento_en_posicion(lista, POSICION) == elemento)
		elementos_insertados++;

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);
	cantidad_elementos = 0;

	afirmar("Todos los elementos insertados correctamente", lista->cantidad == elementos_insertados, pruebas_pasadas, cantidad_pruebas);

	lista_destruir(lista);
}

void probar_lista_borrar(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;	
	size_t cantidad_elementos = 0;

	afirmar("No se puede borrar con una lista nula", lista_borrar(lista) == ERROR, pruebas_pasadas, cantidad_pruebas);

	lista = crear_lista_cargada();	

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);

	printf(BLANCO FLECHA " Mi ultimo elemento es: %i\n" NORMAL, *(int*)lista->nodo_fin->elemento);

	destruir_elemento(lista->nodo_fin->elemento, NULL);
	cantidad_elementos--;
	afirmar("Borrado el ultimo elemento", lista_borrar(lista) != ERROR && lista->cantidad == cantidad_elementos, pruebas_pasadas, cantidad_pruebas);

	printf(BLANCO FLECHA " Ahora mi ultimo elemento es: %i\n" NORMAL, *(int*)lista->nodo_fin->elemento);

	for(size_t i = 0; i < cantidad_elementos; i++){
		destruir_elemento(lista->nodo_fin->elemento, NULL);
		lista_borrar(lista);
	}

	afirmar("Lista borrada", lista->cantidad == LISTA_VACIA, pruebas_pasadas, cantidad_pruebas);

	destruir_lista_cargada(lista);
}

void probar_lista_borrar_de_posicion(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;
	size_t cantidad_elementos = 0;

	afirmar("No se puede borrar de posicion con una lista nula", lista_borrar_de_posicion(lista, POSICION) == ERROR, pruebas_pasadas, cantidad_pruebas);

	lista = crear_lista_cargada();

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);
	cantidad_elementos = 0;

	destruir_elemento(lista_elemento_en_posicion(lista, POSICION_INICIO), NULL);
	afirmar("Elemento eliminado de la posicion 0", lista_borrar_de_posicion(lista, POSICION_INICIO) != ERROR, pruebas_pasadas, cantidad_pruebas);
	
	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);
	cantidad_elementos = 0;

	destruir_elemento(lista_elemento_en_posicion(lista, POSICION), NULL);
	afirmar("Elemento eliminado de la posicion 2 ", lista_borrar_de_posicion(lista, POSICION) != ERROR, pruebas_pasadas, cantidad_pruebas);
	
	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);
	cantidad_elementos = 0;

	destruir_elemento(lista->nodo_fin->elemento, NULL);
	afirmar("Elemento eliminado de la ultima posicion", lista_borrar_de_posicion(lista, POSICION_FINAL) != ERROR, pruebas_pasadas, cantidad_pruebas);

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);

	destruir_lista_cargada(lista);
}

void probar_lista_elemento_en_posicion(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista_vacia = NULL;
	int elemento_prueba = 0;
	size_t cantidad_elementos = 0;

	afirmar("No hay elementos en posicion en una lista nula", lista_elemento_en_posicion(lista_vacia, POSICION) == NULL, pruebas_pasadas, cantidad_pruebas);

	lista_vacia = lista_crear(); 
	afirmar("No hay elementos en posicion en una lista vacia", lista_elemento_en_posicion(lista_vacia, POSICION) == NULL, pruebas_pasadas, cantidad_pruebas);

	lista_t* lista = crear_lista_cargada();									
		
	elemento_prueba = *(int*)lista_elemento_en_posicion(lista, POSICION);

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);

	printf(BLANCO FLECHA " Elemento: %i, posicion: %i\n" NORMAL, elemento_prueba, POSICION);
	
	lista_destruir(lista_vacia);
	destruir_lista_cargada(lista);
}

void probar_lista_ultimo(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;
	size_t cantidad_elementos = 0;

	afirmar("Lista nula no tiene ultimo", lista_ultimo(lista) == NULL, pruebas_pasadas, cantidad_pruebas);

	lista = crear_lista_cargada();

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);

	printf(BLANCO FLECHA " Mi ultimo elemento deberia ser: %i \n" NORMAL, *(int*)lista->nodo_fin->elemento);
		
	afirmar("Ultimo elemento en posicion", *(int*)lista_ultimo(lista) == *(int*)lista->nodo_fin->elemento, pruebas_pasadas, cantidad_pruebas);
	
	destruir_lista_cargada(lista);
}

void probar_lista_vacia(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;
	size_t cantidad_elementos = 0;

	afirmar("Lista nula esta vacia", lista_vacia(lista), pruebas_pasadas, cantidad_pruebas);

	lista = lista_crear();

	afirmar("Lista vacia", lista_vacia(lista), pruebas_pasadas, cantidad_pruebas);
	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);

	lista_t* lista_cargada = crear_lista_cargada();
	afirmar("Lista no esta vacia", !lista_vacia(lista_cargada), pruebas_pasadas, cantidad_pruebas);
	lista_con_cada_elemento(lista_cargada, mostrar_elemento, &cantidad_elementos);

	lista_destruir(lista);
	destruir_lista_cargada(lista_cargada);
}

void probar_lista_tope(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;
	lista_t* lista_cargada = NULL;
	int elemento_comparar = 5;
	int elemento_prueba = 0;
	size_t cantidad_elementos = 0;

	afirmar("No se puede obtener el tope con una lista nula", lista_tope(lista) == NULL, pruebas_pasadas, cantidad_pruebas);

	lista = lista_crear();									

	afirmar("Lista vacia no tiene tope", lista_tope(lista) == NULL, pruebas_pasadas, cantidad_pruebas);

	lista_cargada = crear_lista_cargada();

	elemento_prueba = *(int*)lista_tope(lista_cargada);

	lista_con_cada_elemento(lista_cargada, mostrar_elemento, &cantidad_elementos);

	printf(BLANCO FLECHA " Mi tope deberia ser: %i y es %i\n" NORMAL, elemento_comparar, elemento_prueba);

	afirmar("Tope correcto", elemento_prueba == elemento_comparar, pruebas_pasadas, cantidad_pruebas);

	lista_destruir(lista);
	destruir_lista_cargada(lista_cargada);
}

void probar_lista_primero(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;
	lista_t* lista_cargada = NULL;
	int elemento_comparar = ELEMENTO_INICIO;
	int elemento_prueba = 0;
	size_t cantidad_elementos = 0;

	afirmar("No se puede obtener el primero con una lista nula", lista_primero(lista) == NULL, pruebas_pasadas, cantidad_pruebas);

	lista = lista_crear();									

	afirmar("Lista vacia no tiene primero", lista_primero(lista) == NULL, pruebas_pasadas, cantidad_pruebas);

	lista_cargada = crear_lista_cargada();	

	elemento_prueba = *(int*)lista_primero(lista_cargada);

	lista_con_cada_elemento(lista_cargada, mostrar_elemento, &cantidad_elementos);

	printf(BLANCO FLECHA " Mi primer elemento deberia ser: %i y es %i\n" NORMAL, elemento_comparar, elemento_prueba);

	afirmar("Primer elemento correcto", elemento_prueba == elemento_comparar, pruebas_pasadas, cantidad_pruebas);

	lista_destruir(lista);
	destruir_lista_cargada(lista_cargada);
}

void probar_lista_encolar(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;
	int elemento_fin = ELEMENTO_FIN;
	int elemento = ELEMENTO_PRUEBA;
	int elementos_insertados = 0;
	size_t cantidad_elementos = 0;

	afirmar("No se puede encolar con una lista nula", lista_encolar(lista, &elemento) == ERROR, pruebas_pasadas, cantidad_pruebas);

	lista = lista_crear();

	afirmar("Se encola el primer elemento", lista_encolar(lista, &elemento) != ERROR, pruebas_pasadas, cantidad_pruebas);
	elementos_insertados++;

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);
	cantidad_elementos = 0;

	for(int i = 0; i < PRUEBA_VOLUMEN; i++){
		lista_encolar(lista, &elemento);
		elementos_insertados++;
	}
	
	afirmar("Se encolan correctamente muchos elementos", lista->cantidad == elementos_insertados, pruebas_pasadas, cantidad_pruebas);

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);
	cantidad_elementos = 0;

	printf(BLANCO FLECHA " Encolo el elemento %i\n" NORMAL, elemento_fin);
	lista_encolar(lista, &elemento_fin);
	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);
	afirmar("Se encola un elemento", *(int*)lista->nodo_fin->elemento == elemento_fin, pruebas_pasadas, cantidad_pruebas);

	lista_destruir(lista);
}

void probar_lista_desencolar(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;
	size_t cantidad_elementos = 0;

	afirmar("No se puede desencolar con una lista nula", lista_desencolar(lista) == ERROR, pruebas_pasadas, cantidad_pruebas);

	lista = crear_lista_cargada();	

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);
	cantidad_elementos = 0;

	printf(BLANCO FLECHA " Desencolo el primer elemento\n" NORMAL);
	destruir_elemento(lista->nodo_inicio->elemento, NULL);
	afirmar("Desencolado el primer elemento", lista_desencolar(lista) != ERROR, pruebas_pasadas, cantidad_pruebas);
	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);


	printf(BLANCO FLECHA " Desencolo todos los elementos\n" NORMAL);
	for(size_t i = 0; i < cantidad_elementos; i++){
		destruir_elemento(lista->nodo_inicio->elemento, NULL);
		lista_desencolar(lista);
	}
	printf(BLANCO FLECHA " Cantidad de elementos en la lista: %li\n" NORMAL, lista->cantidad);
	afirmar("Desencolados todos los elementos", lista->cantidad == LISTA_VACIA, pruebas_pasadas, cantidad_pruebas);

	destruir_lista_cargada(lista);
}

void probar_lista_apilar(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;
	int elemento_fin = ELEMENTO_FIN;
	int elemento = ELEMENTO_PRUEBA;
	int elementos_insertados = 0;
	size_t cantidad_elementos = 0;

	afirmar("No se puede apilar con una lista nula", lista_apilar(lista, &elemento) == ERROR, pruebas_pasadas, cantidad_pruebas);

	lista = lista_crear();

	afirmar("Se apila el primer elemento", lista_apilar(lista, &elemento) != ERROR, pruebas_pasadas, cantidad_pruebas);
	elementos_insertados++;

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);
	cantidad_elementos = 0;

	for(int i = 0; i < PRUEBA_VOLUMEN; i++){
		lista_apilar(lista, &elemento);
		elementos_insertados++;
	}
	
	afirmar("Se apilan correctamente muchos elementos", lista->cantidad == elementos_insertados, pruebas_pasadas, cantidad_pruebas);

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);
	cantidad_elementos = 0;

	printf(BLANCO FLECHA " Apilo el elemento %i\n" NORMAL, elemento_fin);
	lista_apilar(lista, &elemento_fin);
	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);
	afirmar("Se apila un elemento", *(int*)lista->nodo_fin->elemento == elemento_fin, pruebas_pasadas, cantidad_pruebas);

	lista_destruir(lista);
}

void probar_lista_desapilar(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;
	size_t cantidad_elementos = 0;

	afirmar("No se puede desapilar con una lista nula", lista_desapilar(lista) == ERROR, pruebas_pasadas, cantidad_pruebas);

	lista = crear_lista_cargada();	

	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);
	cantidad_elementos = 0;

	printf(BLANCO FLECHA " Desapilo el ultimo elemento\n" NORMAL);
	destruir_elemento(lista->nodo_fin->elemento, NULL);
	afirmar("Desapilado el ultimo elemento", lista_desapilar(lista) != ERROR, pruebas_pasadas, cantidad_pruebas);
	lista_con_cada_elemento(lista, mostrar_elemento, &cantidad_elementos);


	printf(BLANCO FLECHA " Desapilo todos los elementos\n" NORMAL);
	for(size_t i = 0; i < cantidad_elementos; i++){
		destruir_elemento(lista->nodo_fin->elemento, NULL);
		lista_desapilar(lista);
	}
	printf(BLANCO FLECHA " Cantidad de elementos en la lista: %li\n" NORMAL, lista->cantidad);
	afirmar("Desapilado todos los elementos", lista->cantidad == LISTA_VACIA, pruebas_pasadas, cantidad_pruebas);

	destruir_lista_cargada(lista);
}

void probar_iterador_externo(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;

	afirmar("No se puede crear un iterador con una lista nula", lista_iterador_crear(lista) == NULL, pruebas_pasadas, cantidad_pruebas);
	
	lista = crear_lista_cargada();
	lista_iterador_t* iterador = NULL;

	afirmar("No se puede avanzar con un iterador nulo",lista_iterador_avanzar(iterador) == false, pruebas_pasadas, cantidad_pruebas);
	afirmar("No hay mas elementos sobre los cuales iterar",lista_iterador_tiene_siguiente(iterador) == false, pruebas_pasadas, cantidad_pruebas);
	afirmar("No hay elemento actual con un iterador nulo",lista_iterador_elemento_actual(iterador) == NULL, pruebas_pasadas, cantidad_pruebas);

	printf("\n");

	printf("Imprimo la lista usando el iterador externo: \n");
	for(iterador = lista_iterador_crear(lista); lista_iterador_tiene_siguiente(iterador); lista_iterador_avanzar(iterador))
		printf("%i ", *(int*)lista_iterador_elemento_actual(iterador));
	
	printf("\n");

	destruir_lista_cargada(lista);
	lista_iterador_destruir(iterador);
}

void probar_iterador_interno(int* pruebas_pasadas, int* cantidad_pruebas){

	lista_t* lista = NULL;
	int contador = 0;	

	afirmar("No se puede recorrer un lista nula", lista_con_cada_elemento(lista, mostrar_elemento, (void*)&contador) == 0, pruebas_pasadas, cantidad_pruebas);

	lista = crear_lista_cargada();

	afirmar("No se puede recorrer un lista con una funcion nula", lista_con_cada_elemento(lista, NULL, (void*)&contador) == 0, pruebas_pasadas, cantidad_pruebas);
	printf("\n");

	printf("Imprimo la lista usando el iterador interno: \n");
    lista_con_cada_elemento(lista, mostrar_elemento, (void*)&contador);

	destruir_lista_cargada(lista);
}

void probar_operaciones_lista(int* pruebas_pasadas, int* cantidad_pruebas){

	printf(AMARILLO "--------------- CREACION LISTA ---------------\n" NORMAL);
	probar_creacion_lista(pruebas_pasadas, cantidad_pruebas);

	printf(AMARILLO "--------------- LISTA INSERTAR ---------------\n" NORMAL);
	probar_lista_insertar(pruebas_pasadas, cantidad_pruebas);

	printf(AMARILLO "--------- LISTA INSERTAR EN POSICION ---------\n" NORMAL);
	probar_lista_insertar_en_posicion(pruebas_pasadas, cantidad_pruebas);

	printf(AMARILLO "---------------- LISTA BORRAR ----------------\n" NORMAL);
	probar_lista_borrar(pruebas_pasadas, cantidad_pruebas);

	printf(AMARILLO "---------- LISTA BORRAR EN POSICION ----------\n" NORMAL);
	probar_lista_borrar_de_posicion(pruebas_pasadas, cantidad_pruebas);

	printf(AMARILLO "--------- LISTA ELEMENTO EN POSICION ---------\n" NORMAL);
	probar_lista_elemento_en_posicion(pruebas_pasadas, cantidad_pruebas);

	printf(AMARILLO "---------------- LISTA ULTIMO ----------------\n" NORMAL);
	probar_lista_ultimo(pruebas_pasadas, cantidad_pruebas);

	printf(AMARILLO "----------------- LISTA VACIA ----------------\n" NORMAL);
	probar_lista_vacia(pruebas_pasadas, cantidad_pruebas);

	printf(AMARILLO "------------------ LISTA TOPE ----------------\n" NORMAL);
	probar_lista_tope(pruebas_pasadas, cantidad_pruebas);

	printf(AMARILLO "---------------- LISTA PRIMERO ---------------\n" NORMAL);
	probar_lista_primero(pruebas_pasadas, cantidad_pruebas);
}

void probar_operaciones_cola(int* pruebas_pasadas, int* cantidad_pruebas){

	printf(AMARILLO "--------------- LISTA ENCOLAR ----------------\n" NORMAL);
	probar_lista_encolar(pruebas_pasadas, cantidad_pruebas);

	printf(AMARILLO "--------------- LISTA DESENCOLAR -------------\n" NORMAL);
	probar_lista_desencolar(pruebas_pasadas, cantidad_pruebas);
}

void probar_operaciones_pila(int* pruebas_pasadas, int* cantidad_pruebas){

	printf(AMARILLO "---------------- LISTA APILAR ----------------\n" NORMAL);
	probar_lista_apilar(pruebas_pasadas, cantidad_pruebas);

	printf(AMARILLO "--------------- LISTA DESAPILAR --------------\n" NORMAL);
	probar_lista_desapilar(pruebas_pasadas, cantidad_pruebas);
}

void probar_operaciones_iterador(int* pruebas_pasadas, int* cantidad_pruebas){

	printf(AMARILLO "----------- LISTA ITERADOR EXTERNO -----------\n" NORMAL);
	probar_iterador_externo(pruebas_pasadas, cantidad_pruebas);

	printf(AMARILLO "----------- LISTA ITERADOR INTERNO -----------\n" NORMAL);
	probar_iterador_interno(pruebas_pasadas, cantidad_pruebas);
}

int main(){

	int pruebas_pasadas = 0;
	int cantidad_pruebas = 0;
	int pruebas_fallidas = 0;

	probar_operaciones_lista(&pruebas_pasadas, &cantidad_pruebas);
	probar_operaciones_pila(&pruebas_pasadas, &cantidad_pruebas);
	probar_operaciones_cola(&pruebas_pasadas, &cantidad_pruebas);
	probar_operaciones_iterador(&pruebas_pasadas, &cantidad_pruebas);	

	pruebas_fallidas = cantidad_pruebas - pruebas_pasadas;

	printf(BLANCO "-----------------------------------------------\n");
	printf("%i pruebas corridas, %i correctas y %i errores.\n", cantidad_pruebas, pruebas_pasadas, pruebas_fallidas);
	printf("-----------------------------------------------\n" NORMAL);

	return 0;
}