#include "abb.h"
#include <stdio.h>
#include <stdlib.h>

#define BLANCO "\x1b[37;1m"
#define VERDE "\x1b[32;1m"
#define ROJO "\x1b[31;1m"
#define AMARILLO "\x1b[33;1m"
#define AZUL "\x1b[0;36m"
#define NORMAL "\x1b[0m"
#define SUBRAYADO "\x1b[4;33m"
#define FONDO "\x1b[1;90m"
#define TILDE "✓"
#define CRUZ "✗"
#define CIRCULO "•"
#define FLECHA "→"

#define ERROR -1

typedef struct cosa{
    int clave;
    char contenido[10];
}cosa;

void afirmar(char* descripcion, bool afirmacion, int* pruebas_pasadas, int* cantidad_pruebas){

	if(!descripcion || !pruebas_pasadas || !cantidad_pruebas)
		return;

	if(afirmacion){
		(*pruebas_pasadas)++;
	}
	printf("%s %s\n", afirmacion? VERDE TILDE NORMAL : ROJO CRUZ NORMAL, descripcion);

	(*cantidad_pruebas)++;
}

cosa* crear_cosa(int clave){
    cosa* c = (cosa*)malloc(sizeof(cosa));
    if(c)
        c->clave = clave;
    return c;
}

void destruir_cosa(cosa* c){
    free(c);
}

int comparar_cosas(void* elemento_1, void* elemento_2){
    if(!elemento_1 || !elemento_2)
        return 0;

    if(((cosa*)elemento_1)->clave > ((cosa*)elemento_2)->clave)
        return 1;
    if(((cosa*)elemento_1)->clave < ((cosa*)elemento_2)->clave)
        return -1;
    return 0;
}

void destructor_de_cosas(void* elemento){
    if(!elemento)
        return;
    destruir_cosa((cosa*)elemento);
}

bool mostrar_elemento(void* elemento, void* extra){
    extra = extra;
    if(elemento)
        printf(" %i", ((cosa*)elemento)->clave);
    return false;
}

bool mostrar_hasta_5(void* elemento, void* extra){
    extra = extra;
    if(elemento){
        printf(" %i", ((cosa*)elemento)->clave);
        if(((cosa*)elemento)->clave == 5)
            return true;
    }
    return false;
}

bool mostrar_acumulado(void* elemento, void* extra){
    if(elemento && extra){
        *(int*)extra += ((cosa*)elemento)->clave;
        printf(" %i", *(int*)extra);
    }
    return false;
}

void probar_arbol_crear(int* pruebas_pasadas, int* cantidad_pruebas){

	abb_t* arbol = 	arbol_crear(comparar_cosas, NULL);

	afirmar("Arbol creado correctamente", arbol != NULL, pruebas_pasadas, cantidad_pruebas);
	afirmar("Arbol creado con un destructor nulo", arbol != NULL, pruebas_pasadas, cantidad_pruebas);
	afirmar("El arbol se crea vacio", arbol_vacio(arbol) == true, pruebas_pasadas, cantidad_pruebas);
	afirmar("Arbol creado con un nodo raiz nulo", arbol->nodo_raiz == NULL, pruebas_pasadas, cantidad_pruebas);
	afirmar("No se puede crear un arbol con un comparador nulo", arbol_crear(NULL, destructor_de_cosas) == NULL, pruebas_pasadas, cantidad_pruebas);

	arbol_destruir(arbol);    
}

void probar_arbol_insertar(int* pruebas_pasadas, int* cantidad_pruebas, abb_t* arbol){	

	cosa* c1 = crear_cosa(1);
    cosa* c2 = crear_cosa(2);
    cosa* c3 = crear_cosa(3);
    cosa* c4 = crear_cosa(4);
    cosa* c5 = crear_cosa(5);
    cosa* c6 = crear_cosa(6);
    cosa* c7 = crear_cosa(7);        
    
    afirmar("Primer elemento insertado", arbol_insertar(arbol, c4) != ERROR, pruebas_pasadas, cantidad_pruebas);
    afirmar("El nodo raiz deberia ser 4", ((cosa*)arbol_raiz(arbol))->clave == 4, pruebas_pasadas, cantidad_pruebas);
    afirmar("El arbol ya no esta vacio", arbol_vacio(arbol) == false, pruebas_pasadas, cantidad_pruebas);
    afirmar("Inserto un elemento menor que el primero", arbol_insertar(arbol, c2) != ERROR, pruebas_pasadas, cantidad_pruebas);
    afirmar("Mi raiz no tiene un hijo derecho", arbol->nodo_raiz->derecha == NULL, pruebas_pasadas, cantidad_pruebas);    
    afirmar("Inserto un elemento mayor que el primero", arbol_insertar(arbol, c6) != ERROR, pruebas_pasadas, cantidad_pruebas);
    afirmar("Mi raiz tiene un hijo izquierdo y un hijo derecho", arbol->nodo_raiz->derecha != NULL && arbol->nodo_raiz->izquierda != NULL, pruebas_pasadas, cantidad_pruebas);

    arbol_insertar(arbol, c1);
    arbol_insertar(arbol, c3);
    arbol_insertar(arbol, c5);
    arbol_insertar(arbol, c7);
}

void probar_arbol_nulo(int* pruebas_pasadas, int* cantidad_pruebas, abb_t* arbol){

	printf(AMARILLO "ARBOL NULO --------------------------------------------------------------------\n" NORMAL);
	afirmar("Un arbol nulo esta vacio", arbol_vacio(arbol) == true, pruebas_pasadas, cantidad_pruebas);
	afirmar("No se puede insertar con un arbol nulo", arbol_insertar(arbol, NULL) == ERROR, pruebas_pasadas, cantidad_pruebas);
	afirmar("Un arbol nulo no tiene nodo raiz", arbol_raiz(arbol) == NULL, pruebas_pasadas, cantidad_pruebas);
	afirmar("No se puede buscar con un arbol nulo", arbol_buscar(arbol, NULL) == NULL, pruebas_pasadas, cantidad_pruebas);
	afirmar("No se puede borrar con un arbol nulo", arbol_borrar(arbol, NULL) == ERROR, pruebas_pasadas, cantidad_pruebas);
}

void probar_nodo_raiz_nulo(int* pruebas_pasadas, int* cantidad_pruebas, abb_t* arbol){

	printf(AMARILLO "NODO RAIZ NULO ----------------------------------------------------------------\n" NORMAL);
    afirmar("Un arbol con un nodo raiz nulo esta vacio", arbol_vacio(arbol) == true, pruebas_pasadas, cantidad_pruebas);
    afirmar("Un arbol con nodo raiz nulo no tiene nodo raiz", arbol_raiz(arbol) == NULL, pruebas_pasadas, cantidad_pruebas);
    afirmar("No se puede buscar con un nodo raiz nulo", arbol_buscar(arbol, NULL) == NULL, pruebas_pasadas, cantidad_pruebas);
    afirmar("No se puede borrar con un nodo raiz nulo", arbol_borrar(arbol, NULL) == ERROR, pruebas_pasadas, cantidad_pruebas);
}

void probar_arbol_borrar(int* pruebas_pasadas, int* cantidad_pruebas, abb_t* arbol, cosa* auxiliar){

	auxiliar->clave = 7;
    afirmar("Borro nodo hoja (7)", (arbol_borrar(arbol, auxiliar)) == 0, pruebas_pasadas, cantidad_pruebas);
    afirmar("El nodo eliminado ya no existe", arbol_buscar(arbol, auxiliar) == NULL, pruebas_pasadas, cantidad_pruebas);

    auxiliar->clave = 6;
    afirmar("Borro nodo con un hijo (6)", (arbol_borrar(arbol, auxiliar)) == 0, pruebas_pasadas, cantidad_pruebas);

    auxiliar->clave = 2;
    afirmar("Borro nodo con dos hijos (2)", (arbol_borrar(arbol, auxiliar)) == 0, pruebas_pasadas, cantidad_pruebas);

    auxiliar->clave = 4;
    afirmar("Borro la raiz (4)", (arbol_borrar(arbol, auxiliar)) == 0, pruebas_pasadas, cantidad_pruebas);
}

void probar_recorridos(int* pruebas_pasadas, int* cantidad_pruebas, abb_t* arbol){

	cosa* elementos[10];

	afirmar("No se puede iterar con un arbol nulo", arbol_recorrido_preorden(NULL, (void**)elementos, 10) == 0, pruebas_pasadas, cantidad_pruebas);
	
    printf(AZUL CIRCULO NORMAL " Recorrido INORDEN   " AZUL FLECHA NORMAL);
    size_t cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 10);
    for(size_t i = 0; i < cantidad; i++)
        printf(" %i", elementos[i]->clave);
    printf(" (resultado esperado: 1 2 3 4 5 6 7)\n");

    cantidad = 0;
    printf(AZUL CIRCULO NORMAL " Recorrido PREORDEN  " AZUL FLECHA NORMAL);
    cantidad = arbol_recorrido_preorden(arbol, (void**)elementos, 10);
    for(size_t i = 0; i < cantidad; i++)
        printf(" %i", elementos[i]->clave);
    printf(" (resultado esperado: 4 2 1 3 6 5 7)\n");

    cantidad = 0;
    printf(AZUL CIRCULO NORMAL " Recorrido POSTORDEN " AZUL FLECHA NORMAL);
    cantidad = arbol_recorrido_postorden(arbol, (void**)elementos, 10);
    for(size_t i = 0; i < cantidad; i++)
        printf(" %i", elementos[i]->clave);
    printf(" (resultado esperado: 1 3 2 5 7 6 4)\n");
}

void probar_iterador_interno(int* pruebas_pasadas, int* cantidad_pruebas, abb_t* arbol){

	printf(SUBRAYADO "Inserto mas valores\n" NORMAL);
    arbol_insertar(arbol, crear_cosa(15));
    arbol_insertar(arbol, crear_cosa(0));
    arbol_insertar(arbol, crear_cosa(9));
    arbol_insertar(arbol, crear_cosa(7));
    arbol_insertar(arbol, crear_cosa(4));

    afirmar("No se puede iterar con un arbol nulo", abb_con_cada_elemento(NULL, ABB_RECORRER_INORDEN, mostrar_elemento, NULL) == 0, pruebas_pasadas, cantidad_pruebas);
    afirmar("No se puede iterar con una funcion nula", abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, NULL, NULL) == 0, pruebas_pasadas, cantidad_pruebas); 

    printf(AZUL CIRCULO NORMAL " Recorrido INORDEN   " AZUL FLECHA NORMAL); 
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
    printf("\n");

    printf(AZUL CIRCULO NORMAL " Recorrido PREORDEN  " AZUL FLECHA NORMAL);    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elemento, NULL);
    printf("\n");
    
    printf(AZUL CIRCULO NORMAL " Recorrido POSTORDEN " AZUL FLECHA NORMAL);  
    size_t elementos_recorridos = abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elemento, NULL);
    printf("\n");
    afirmar("Puedo iterar con un extra nulo", elementos_recorridos != 0, pruebas_pasadas, cantidad_pruebas); 

    printf(AZUL "-------------------------------------------------------------------------------\n" NORMAL);

    printf(AZUL CIRCULO NORMAL " Recorrido INORDEN hasta encontrar el 5:   " AZUL FLECHA NORMAL);    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_5, NULL);
    printf("\n");

    printf(AZUL CIRCULO NORMAL " Recorrido PREORDEN hasta encontrar el 5:  " AZUL FLECHA NORMAL);    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_5, NULL);
    printf("\n");

    printf(AZUL CIRCULO NORMAL " Recorrido POSTORDEN hasta encontrar el 5: " AZUL FLECHA NORMAL);    
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_5, NULL);
    printf("\n");

    printf(AZUL "-------------------------------------------------------------------------------\n" NORMAL);

    int acumulador_inorden = 0;
    printf(AZUL CIRCULO NORMAL " Recorrido INORDEN acumulando los valores:   " AZUL FLECHA NORMAL);    
    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_acumulado, &acumulador_inorden);
    printf("\n");

    int acumulador_preorden = 0;
    printf(AZUL CIRCULO NORMAL " Recorrido PREORDEN acumulando los valores:  " AZUL FLECHA NORMAL);    
    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_acumulado, &acumulador_preorden);
    printf("\n");

    int acumulador_postorden = 0;
    printf(AZUL CIRCULO NORMAL " Recorrido POSTORDEN acumulando los valores: " AZUL FLECHA NORMAL);    
    abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_acumulado, &acumulador_postorden);    
    printf("\n");
    afirmar("Valores acumulados correctamente", acumulador_inorden == 44 && acumulador_preorden == 44 && acumulador_postorden == 44, pruebas_pasadas, cantidad_pruebas); 
}

void probar_operaciones_arbol(int* pruebas_pasadas, int* cantidad_pruebas){

	abb_t* arbol = 	NULL;
	cosa* auxiliar = crear_cosa(0);

	probar_arbol_nulo(pruebas_pasadas, cantidad_pruebas, arbol);

	arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

	probar_nodo_raiz_nulo(pruebas_pasadas, cantidad_pruebas, arbol);

	printf(AMARILLO "OPERACIONES ARBOL -------------------------------------------------------------\n" NORMAL);

    probar_arbol_insertar(pruebas_pasadas, cantidad_pruebas, arbol);	

	auxiliar->clave = 5;
	afirmar("Busco el elemento 5", ((cosa*)arbol_buscar(arbol, auxiliar))->clave == 5, pruebas_pasadas, cantidad_pruebas);

    printf(AZUL "RECORRIDOS --------------------------------------------------------------------\n" NORMAL);
    probar_recorridos(pruebas_pasadas, cantidad_pruebas, arbol);
    printf(AZUL "-------------------------------------------------------------------------------\n" NORMAL);

    probar_arbol_borrar(pruebas_pasadas, cantidad_pruebas, arbol, auxiliar);

    afirmar("El nodo raiz ahora deberia ser 3", ((cosa*)arbol_raiz(arbol))->clave == 3, pruebas_pasadas, cantidad_pruebas);

	auxiliar->clave = 3;
	afirmar("Busco el elemento 3", ((cosa*)arbol_buscar(arbol, auxiliar))->clave == 3, pruebas_pasadas, cantidad_pruebas);

	auxiliar->clave = 10;
	afirmar("Busco un elemento que no esta en el arbol", arbol_buscar(arbol, auxiliar) == NULL, pruebas_pasadas, cantidad_pruebas);

    afirmar("Arbol no esta vacio", arbol_vacio(arbol) == false, pruebas_pasadas, cantidad_pruebas);

    printf(AZUL "ITERADOR INTERNO --------------------------------------------------------------\n" NORMAL);
    probar_iterador_interno(pruebas_pasadas, cantidad_pruebas, arbol);
    printf(AZUL "-------------------------------------------------------------------------------\n" NORMAL);

    free(auxiliar);
    arbol_destruir(arbol);    
}

int main(){

	int pruebas_pasadas = 0;
	int cantidad_pruebas = 0;
	int pruebas_fallidas = 0;
	
    printf(AMARILLO "ARBOL CREAR -------------------------------------------------------------------\n" NORMAL);
	probar_arbol_crear(&pruebas_pasadas, &cantidad_pruebas);
	
	probar_operaciones_arbol(&pruebas_pasadas, &cantidad_pruebas);

	pruebas_fallidas = cantidad_pruebas - pruebas_pasadas;

	printf(BLANCO "-------------------------------------------------------------------------------\n");
	printf("%i pruebas corridas, %i correctas y %i errores.\n", cantidad_pruebas, pruebas_pasadas, pruebas_fallidas);
	printf("-------------------------------------------------------------------------------\n" NORMAL);

	return 0;
}