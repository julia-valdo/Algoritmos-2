#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

#define EXITO 0
#define ERROR -1

/*
 * Crea un nodo y reserva la memoria necesaria para el mismo.
 * Devuelve un puntero al nodo creado o NULL en caso de error.
 */
nodo_abb_t* nodo_crear(void* elemento){

	nodo_abb_t* nodo_abb = calloc(1, sizeof(nodo_abb_t));
	if(!nodo_abb)
		return NULL;

	nodo_abb->elemento = elemento;

	return nodo_abb;
}

/*
 * Compara el elemento del nodo a insertar con los elementos de los nodos que ya estan en el arbol y lo inserta en su debida posicion.
 */
void nodo_insertar(abb_comparador comparador, nodo_abb_t* nodo_actual, nodo_abb_t* nodo_nuevo){

	int comparar = comparador(nodo_actual->elemento, nodo_nuevo->elemento);

	if(comparar < 0){
		if(!nodo_actual->derecha)
			nodo_actual->derecha = nodo_nuevo;
		else
			nodo_insertar(comparador, nodo_actual->derecha, nodo_nuevo);
	}else{
		if(!nodo_actual->izquierda)
			nodo_actual->izquierda = nodo_nuevo;
		else
			nodo_insertar(comparador, nodo_actual->izquierda, nodo_nuevo);		
	}
}

/*
 * Recorre el arbol y devuelve un puntero al nodo que contiene el elemento mayor de los menores.
 */
nodo_abb_t* buscar_nodo_mayor(nodo_abb_t* nodo_actual, nodo_abb_t** nodo_padre_mayor){

	if(!nodo_actual->derecha)
		return nodo_actual;

	(*nodo_padre_mayor) = nodo_actual;
	return buscar_nodo_mayor(nodo_actual->derecha, nodo_padre_mayor);
}

/*
 * Quita un nodo hoja del arbol e invoca, si existe, el destructor con el elemento de dicho nodo.
 */
int nodo_borrar_sin_hijos(abb_t* arbol, nodo_abb_t* nodo_actual, nodo_abb_t** nodo_padre){

	if(nodo_actual == arbol->nodo_raiz)
		arbol->nodo_raiz = NULL;

	if((*nodo_padre)->derecha == nodo_actual)
		(*nodo_padre)->derecha = NULL;			
	else
		(*nodo_padre)->izquierda = NULL;
							
	if(arbol->destructor)
		arbol->destructor(nodo_actual->elemento);			
	free(nodo_actual);
	return EXITO;	
}

/*
 * Quita un nodo que tiene un solo hijo del arbol e invoca, si existe, el destructor con el elemento de dicho nodo.
 */
int nodo_borrar_con_hijo_unico(abb_t* arbol, nodo_abb_t* nodo_actual, nodo_abb_t** nodo_padre){

	nodo_abb_t* nodo_aux;

	if(!nodo_actual->derecha)
		nodo_aux = nodo_actual->izquierda;
	else 
		nodo_aux = nodo_actual->derecha;
	
	if(nodo_actual == arbol->nodo_raiz)			
			arbol->nodo_raiz = nodo_aux;
	else{			
		if((*nodo_padre)->derecha == nodo_actual)
			(*nodo_padre)->derecha = nodo_aux;
		else
			(*nodo_padre)->izquierda = nodo_aux;		
	}

	if(arbol->destructor)
		arbol->destructor(nodo_actual->elemento);
	free(nodo_actual);
	return EXITO;
}

/*
 * Busca el nodo que contiene al elemento mayor de los menores.
 * Swapea el elemento que quiero borrar con el elemento mayor de los menores.
 * Borra el nodo que contiene el elemento a borrar. 
 */
int nodo_borrar_con_2_hijos(abb_t* arbol, nodo_abb_t* nodo_actual){

	nodo_abb_t* nodo_padre_mayor = nodo_actual;
	nodo_abb_t* nodo_mayor = buscar_nodo_mayor(nodo_actual->izquierda, &nodo_padre_mayor);
	void* elemento_mayor;

	elemento_mayor = nodo_mayor->elemento;
	nodo_mayor->elemento = nodo_actual->elemento;
	nodo_actual->elemento = elemento_mayor;

	if(nodo_mayor->izquierda)
		return nodo_borrar_con_hijo_unico(arbol, nodo_mayor, &nodo_padre_mayor);		
	else
		return nodo_borrar_sin_hijos(arbol, nodo_mayor, &nodo_padre_mayor);	
}

/*
 * Busca el elemento a borrar comparando a este con los elementos del arbol.
 * Si encuentra el elemento lo quita del arbol.
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */
int nodo_borrar(abb_t* arbol, nodo_abb_t* nodo_actual, nodo_abb_t** nodo_padre, void* elemento){

	if(!nodo_actual)
		return ERROR;

	int comparar = arbol->comparador(nodo_actual->elemento, elemento);	

	if(comparar == 0){

		// si estoy en una hoja
		if(!nodo_actual->derecha && !nodo_actual->izquierda)
			return nodo_borrar_sin_hijos(arbol, nodo_actual, nodo_padre);			
		
		// si tiene 1 hijo
		if((!nodo_actual->derecha && nodo_actual->izquierda) || (nodo_actual->derecha && !nodo_actual->izquierda))
			return nodo_borrar_con_hijo_unico(arbol, nodo_actual, nodo_padre);		

		// si tiene 2 hijos
		if(nodo_actual->derecha && nodo_actual->izquierda)
			return nodo_borrar_con_2_hijos(arbol, nodo_actual);		
	}

	(*nodo_padre) = nodo_actual;

	if(comparar < 0)
		return nodo_borrar(arbol, nodo_actual->derecha, nodo_padre, elemento);
	
	if(comparar > 0)
		return nodo_borrar(arbol, nodo_actual->izquierda, nodo_padre, elemento);

	return EXITO;
}

/*
 * Busca un elemento comparando a este con los elementos del arbol.
 * Devuelve un puntero al nodo que contiene dicho elemento o NULL si no lo encuentra.
 */
nodo_abb_t* nodo_buscar(nodo_abb_t* nodo_actual, abb_comparador comparador, void* elemento){
	
	if(!nodo_actual)
		return NULL;

	int comparar = comparador(nodo_actual->elemento, elemento);

	if(comparar < 0)
		return nodo_buscar(nodo_actual->derecha, comparador, elemento);

	else if(comparar > 0)
		return nodo_buscar(nodo_actual->izquierda, comparador, elemento);

	return nodo_actual;
}

/*
 * Llena el array del tamaño dado con los elementos de arbol en secuencia inorden.
 */
void recorrido_inorden(nodo_abb_t* nodo_actual, void** array, size_t tamanio_array, size_t* elementos_cargados){

	if(!nodo_actual)
		return;

	if(nodo_actual->izquierda)
		recorrido_inorden(nodo_actual->izquierda, array, tamanio_array, elementos_cargados);

	if((*elementos_cargados) >= tamanio_array)
		return;

	array[*elementos_cargados] = nodo_actual->elemento;
	(*elementos_cargados)++;

	if(nodo_actual->derecha)
		recorrido_inorden(nodo_actual->derecha, array, tamanio_array, elementos_cargados);	
}

/*
 * Llena el array del tamaño dado con los elementos de arbol en secuencia preorden.
 */
void recorrido_preorden(nodo_abb_t* nodo_actual, void** array, size_t tamanio_array, size_t* elementos_cargados){

	if(!nodo_actual)
		return;

	if((*elementos_cargados) >= tamanio_array)
		return;

	array[*elementos_cargados] = nodo_actual->elemento;
	(*elementos_cargados)++;

	if(nodo_actual->izquierda)
		recorrido_preorden(nodo_actual->izquierda, array, tamanio_array, elementos_cargados);

	if(nodo_actual->derecha)
		recorrido_preorden(nodo_actual->derecha, array, tamanio_array, elementos_cargados);	
}

/*
 * Llena el array del tamaño dado con los elementos de arbol en secuencia postorden.
 */
void recorrido_postorden(nodo_abb_t* nodo_actual, void** array, size_t tamanio_array, size_t* elementos_cargados){

	if(!nodo_actual)
		return;

	if(nodo_actual->izquierda)
		recorrido_postorden(nodo_actual->izquierda, array, tamanio_array, elementos_cargados);

	if(nodo_actual->derecha)
		recorrido_postorden(nodo_actual->derecha, array, tamanio_array, elementos_cargados);	

	if((*elementos_cargados) >= tamanio_array)
		return;

	array[*elementos_cargados] = nodo_actual->elemento;
	(*elementos_cargados)++;
}

/*
 * Destruye los nodos del arbol liberando la memoria reservada para los mismos.
 * Invoca el destructor, si existe, con los elementos presentes en los nodos.
 */
void nodo_destruir(nodo_abb_t* nodo_actual, abb_liberar_elemento destructor){

	if(nodo_actual->izquierda)
		nodo_destruir(nodo_actual->izquierda, destructor);

	if(nodo_actual->derecha)
		nodo_destruir(nodo_actual->derecha, destructor);

	if(destructor)
		destructor(nodo_actual->elemento);

	free(nodo_actual);
}

bool it_recorrido_inorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*), void* extra, size_t* elementos_recorridos){

	if(nodo_actual->izquierda)
		if(it_recorrido_inorden(nodo_actual->izquierda, funcion, extra, elementos_recorridos))
			return true;

	(*elementos_recorridos)++;
	if(funcion(nodo_actual->elemento, extra))
		return true;

	if(nodo_actual->derecha)
		if(it_recorrido_inorden(nodo_actual->derecha, funcion, extra, elementos_recorridos))
			return true;

	return false;
}

bool it_recorrido_preorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*), void* extra, size_t* elementos_recorridos){

	(*elementos_recorridos)++;
	if(funcion(nodo_actual->elemento, extra))
		return true;

	if(nodo_actual->izquierda)
		if(it_recorrido_preorden(nodo_actual->izquierda, funcion, extra, elementos_recorridos))
			return true;

	if(nodo_actual->derecha)
		if(it_recorrido_preorden(nodo_actual->derecha, funcion, extra, elementos_recorridos))
			return true;

	return false;
}

bool it_recorrido_postorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*), void* extra, size_t* elementos_recorridos){

	if(nodo_actual->izquierda)
		if(it_recorrido_postorden(nodo_actual->izquierda, funcion, extra, elementos_recorridos))
			return true;

	if(nodo_actual->derecha)
		if(it_recorrido_postorden(nodo_actual->derecha, funcion, extra, elementos_recorridos))
			return true;

	(*elementos_recorridos)++;
	if(funcion(nodo_actual->elemento, extra))
		return true;

	return false;
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){

	if(!comparador)
		return NULL;

	abb_t* abb = calloc(1, sizeof(abb_t));
	if(!abb)
		return NULL;

	abb->comparador = comparador;
	abb->destructor = destructor;

	return abb;
}

int arbol_insertar(abb_t* arbol, void* elemento){

	if(!arbol)
		return ERROR;

	nodo_abb_t* nodo_nuevo = nodo_crear(elemento);
	if(!nodo_nuevo)
		return ERROR;

	if(!arbol->nodo_raiz){
		arbol->nodo_raiz = nodo_nuevo;
		return EXITO;
	}
	
	nodo_insertar(arbol->comparador, arbol->nodo_raiz, nodo_nuevo);
		
	return EXITO;
}

int arbol_borrar(abb_t* arbol, void* elemento){

	if(!arbol)
		return ERROR;

	if(!arbol->nodo_raiz)
		return ERROR;

	nodo_abb_t* nodo_padre = arbol->nodo_raiz;

	int eliminar = nodo_borrar(arbol, arbol->nodo_raiz, &nodo_padre, elemento);
	if(eliminar == ERROR)
		return ERROR;

	return EXITO;
}

void* arbol_buscar(abb_t* arbol, void* elemento){
	
	if(!arbol)
		return NULL;

	if(!arbol->nodo_raiz)
		return NULL;

	nodo_abb_t* nodo_buscado = nodo_buscar(arbol->nodo_raiz, arbol->comparador, elemento);
	if(!nodo_buscado)
		return NULL;

	return nodo_buscado->elemento;
}

void* arbol_raiz(abb_t* arbol){

	if(!arbol)
		return NULL;

	if(!arbol->nodo_raiz)
		return NULL;

	return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t* arbol){

	if(!arbol)
		return true;

	if(!arbol->nodo_raiz)
		return true;

	return false;
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){

	if(!arbol)
		return 0;

	if(!arbol->nodo_raiz)
		return 0;
	
	size_t elementos_cargados = 0;
	
	recorrido_inorden(arbol->nodo_raiz, array, tamanio_array ,&elementos_cargados);

	return elementos_cargados;
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){

	if(!arbol)
		return 0;

	if(!arbol->nodo_raiz)
		return 0;
	
	size_t elementos_cargados = 0;
	
	recorrido_preorden(arbol->nodo_raiz, array, tamanio_array ,&elementos_cargados);

	return elementos_cargados;	
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){

	if(!arbol)
		return 0;

	if(!arbol->nodo_raiz)
		return 0;
	
	size_t elementos_cargados = 0;
	
	recorrido_postorden(arbol->nodo_raiz, array, tamanio_array ,&elementos_cargados);

	return elementos_cargados;	
}

void arbol_destruir(abb_t* arbol){

	if(!arbol)
		return;

	if(!arbol->nodo_raiz){
		free(arbol);
		return;		
	}

	nodo_destruir(arbol->nodo_raiz, arbol->destructor);

	free(arbol);
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){

	if(!arbol)
		return 0;

	if(!funcion)
		return 0;

	size_t elementos_recorridos = 0;

	if(recorrido == ABB_RECORRER_INORDEN)
		it_recorrido_inorden(arbol->nodo_raiz, (*funcion), extra, &elementos_recorridos);
	
	if(recorrido == ABB_RECORRER_PREORDEN)
		it_recorrido_preorden(arbol->nodo_raiz, (*funcion), extra, &elementos_recorridos);
	
	if(recorrido == ABB_RECORRER_POSTORDEN)
		it_recorrido_postorden(arbol->nodo_raiz, (*funcion), extra, &elementos_recorridos);

	return elementos_recorridos;
}