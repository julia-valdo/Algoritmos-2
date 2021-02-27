#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define LISTA_VACIA 0
#define POSICION_INICIO 0

lista_t* lista_crear(){

	lista_t* lista = calloc(1, sizeof(lista_t));
	if(!lista)
		return NULL;

	return lista;
}

/*
 * Crea el nodo reservando la memoria necesaria.
 * Devuelve un puntero a el nodo creado o NULL en caso de error.
 */
nodo_t* nodo_crear(){

	nodo_t* nodo = calloc(1, sizeof(nodo_t));
	if(!nodo)
		return NULL;

	return nodo;
}

int lista_insertar(lista_t* lista, void* elemento){

	if(!lista)
		return ERROR;

	nodo_t* nodo_nuevo = nodo_crear();
	if(!nodo_nuevo)
		return ERROR;

	nodo_nuevo->elemento = elemento;

	if(lista->cantidad == LISTA_VACIA){
		lista->nodo_inicio = nodo_nuevo;
		lista->nodo_fin = nodo_nuevo;
	}else{	
		lista->nodo_fin->siguiente = nodo_nuevo;
		lista->nodo_fin = nodo_nuevo;	
	}

	lista->cantidad++;
	return 0;
}

/*
 * inserta el nodo en la posicion recibida.
 */
void posicionar_nodo(lista_t* lista, nodo_t* nodo_nuevo, size_t posicion){

	size_t i = 0;

	nodo_t* nodo_siguiente = lista->nodo_inicio;

	if(posicion == 0){
		nodo_nuevo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_nuevo;
	}
	else if(posicion == 1){
		nodo_siguiente = lista->nodo_inicio->siguiente;
		lista->nodo_inicio->siguiente = nodo_nuevo;                
		nodo_nuevo->siguiente = nodo_siguiente;
	}
	else{
		while(i < (posicion - 1)){
			nodo_siguiente = nodo_siguiente->siguiente;
			i++;
		}
		nodo_nuevo->siguiente = nodo_siguiente->siguiente;
		nodo_siguiente->siguiente = nodo_nuevo;
	}
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){

	int insertado = 0;

	if(!lista) 
		return ERROR;

	if(posicion >= lista->cantidad){
		insertado = lista_insertar(lista, elemento);
		return insertado;
	}

	if(lista->cantidad == LISTA_VACIA){
		insertado = lista_insertar(lista, elemento);
		return insertado;
	}

	nodo_t* nodo_nuevo = nodo_crear();
	if(!nodo_nuevo) 
		return ERROR;

	nodo_nuevo->elemento = elemento;

	posicionar_nodo(lista, nodo_nuevo, posicion);

	lista->cantidad++;

	return 0;
}

int lista_borrar(lista_t* lista){
	
	if(!lista) 
		return ERROR;

	if(lista->cantidad == 0)
		return ERROR;

	if(lista->cantidad == 1){		
		free(lista->nodo_fin);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
	}else{
		nodo_t* nodo_auxiliar = lista->nodo_inicio;

		while(nodo_auxiliar->siguiente != lista->nodo_fin){
			nodo_auxiliar = nodo_auxiliar->siguiente;
		}
		free(lista->nodo_fin);
		nodo_auxiliar->siguiente = NULL;
		lista->nodo_fin = nodo_auxiliar;		
	}

	lista->cantidad--;

	return 0;	
}

/*
 * elimina el nodo que esta en la posicion recibida.
 */
void eliminar_nodo(lista_t* lista, size_t posicion){

	size_t i = 0;

	nodo_t* nodo_auxiliar = lista->nodo_inicio;
	nodo_t* nodo_eliminar = NULL;

	while(i < (posicion - 1) ){
		nodo_auxiliar = nodo_auxiliar->siguiente;
		i++;
	}

	nodo_eliminar = nodo_auxiliar->siguiente;
	nodo_auxiliar->siguiente = nodo_eliminar->siguiente;
	free(nodo_eliminar);
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){

	if(!lista) 
		return ERROR;

	if(lista->cantidad == LISTA_VACIA)
		return ERROR;

	if(posicion >= lista->cantidad)
		return lista_borrar(lista);

	nodo_t* nodo_eliminar = lista->nodo_inicio;
	
	if(posicion == 0){
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		free(nodo_eliminar);
		lista->cantidad--;
		return 0;		
	}
	
	eliminar_nodo(lista, posicion);

	lista->cantidad--;

	return 0;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){

	size_t i = 0;

	if(!lista)
		return NULL;

	if(posicion > lista->cantidad)
		return NULL;

	if(posicion == 0)
		return lista->nodo_inicio->elemento;

	nodo_t* nodo_auxiliar = lista->nodo_inicio;

	while(i < (posicion - 1)){
		nodo_auxiliar = nodo_auxiliar->siguiente;
		i++;
	}
	return (nodo_auxiliar->siguiente)->elemento;
}

void* lista_ultimo(lista_t* lista){

	size_t i = 0;

	if(!lista)
		return NULL;

	if(lista->cantidad == LISTA_VACIA)
		return NULL;

	nodo_t* nodo_auxiliar = lista->nodo_inicio;

	while(i < (lista->cantidad - 1)){
		nodo_auxiliar = nodo_auxiliar->siguiente;
		i++;
	}
	return nodo_auxiliar->elemento;
}

bool lista_vacia(lista_t* lista){

	if(!lista)
		return true;

	if(lista->cantidad == LISTA_VACIA)
		return true;
	else
		return false;
}

size_t lista_elementos(lista_t* lista){

	if(!lista)
		return 0;

	return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento){

	if(!lista)
		return ERROR;

	return lista_insertar(lista, elemento);
}

int lista_desapilar(lista_t* lista){

	if(!lista)
		return ERROR;

	return lista_borrar(lista);
}

void* lista_tope(lista_t* lista){

	if(!lista)
		return NULL;

	if(lista->cantidad == LISTA_VACIA)
		return NULL;

	return lista->nodo_fin->elemento;
}

int lista_encolar(lista_t* lista, void* elemento){

	if(!lista)
		return ERROR;

	return lista_insertar(lista, elemento);
}

int lista_desencolar(lista_t* lista){

	if(!lista)
		return ERROR;

	return lista_borrar_de_posicion(lista, POSICION_INICIO);

}

void* lista_primero(lista_t* lista){

	if(!lista)
		return NULL;

	if(lista->cantidad == LISTA_VACIA)
		return NULL;

	return lista->nodo_inicio->elemento;
}

void lista_destruir(lista_t* lista){

	if(!lista)
		return;

	nodo_t* nodo_aux = NULL;	

	while(lista->nodo_inicio != NULL){
		nodo_aux = lista->nodo_inicio->siguiente;
		free(lista->nodo_inicio);
		lista->nodo_inicio = nodo_aux;
		lista->cantidad--;
	}	
	free(lista);		
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){

	if(!lista)
		return NULL;

	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
	if(!iterador)
		return NULL;

	iterador->lista = lista;
	iterador->corriente = lista->nodo_inicio;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){

	if(!iterador)
		return false;

	if(!iterador->corriente)
		return false;
	
	return true;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){

	if(!iterador)
		return false;

	if(lista_iterador_tiene_siguiente(iterador))
		iterador->corriente = iterador->corriente->siguiente;
		
	return iterador->corriente != NULL;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){

	if(!iterador)
		return NULL;

	if(iterador->corriente == NULL)
		return NULL;
	else
		return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){

	free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){

	size_t elementos_iterados = 0;

	if(!lista)
		return 0;

	if((*funcion) == NULL)
		return 0;

	nodo_t* nodo_aux = lista->nodo_inicio;

	while(elementos_iterados < lista->cantidad && (*funcion)(nodo_aux->elemento, contexto)){
		nodo_aux = nodo_aux->siguiente;		
		elementos_iterados++;		
	}
	
	return elementos_iterados;
}