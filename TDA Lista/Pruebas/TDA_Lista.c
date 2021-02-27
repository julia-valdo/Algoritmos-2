#include "lista.h"
#include <stdio.h>

int main(){

	lista_t* lista = lista_crear();

	lista_destruir(lista);

	return 0;
}