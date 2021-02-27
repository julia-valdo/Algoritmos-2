

								  _______  _____                _       _____   _____  _______        
								 |__   __||  __ \    /\        | |     |_   _| / ____||__   __| /\    
								    | |   | |  | |  /  \       | |       | |  | (___     | |   /  \   
								    | |   | |  | | / /\ \      | |       | |   \___ \    | |  / /\ \  
								    | |   | |__| |/ ____ \     | |____  _| |_  ____) |   | | / ____ \ 
								    |_|   |_____//_/    \_\    |______||_____||_____/    |_|/_/    \_\
								                                                                   
								                                                                   
---------------------------------------------------------------------------------------------------------------------------------------------------

Se hace entrega de:
	 la implementacion de una lista simplemente enlazada y de las funciones basicas de los TDAs pila y cola 
	 la creacion de un iterador interno y uno externo para dicha lista
	 un conjunto de pruebas que comprueba el correcto funcionamiento del TDA

Linea de compilacion: gcc *.c -o lista_se -g -std=c99 -Wall -Wconversion -Wtype -limits -pedantic -Werror -O0

Liea de ejecucion: valgrind --leak-check=full --track -origins=yes --show-reachable=yes ./lista_se

Funcionamiento: la lista se crea reservando la memoria necesaria para la misma. Para insertar un elemento se reserva en memoria el espacio 
	suficiente para la 	estructura de un nodo, el cual va a tener un puntero que almacene dicho elemento y un puntero al nodo siguiente el cual me permite no perder la referencia a los nodos(en el caso de el ultimo nodo, si siguiente apunta a NULL). 
	A medida que se van insertando nodos se actualizan las referencias de la lista al primer y ultimo nodo.
	En funciones en donde se modifica la cantidad de elementos en la lista (ya sea insertando, apilando, encolando, eliminando, desapilando o desencolando nodos), se actualizan las referencias que tienen los nodos alrededor del nodo afectado para no perder la referencia al resto de los nodos.
	Tambien se cuenta con un iterador externo el cual me permite iterar de forma controlada sobre los nodos que contiene la lista y darme informacion sobre estos (si el nodo tiene siguiente, el elemento actual del nodo) y con un iterador interno el cual recorre la lista e invoca una funcion con cada elemento de la misma hasta que esta funcion me devuelva false.
	-> El usuario es responsable de liberar los elementos almacenados en el heap <-

---------------------------------------------------------------------------------------------------------------------------------------------------
                                 _                _                  _                     
                                | |              | |                (_)                    
   ___ ___  _ __   ___ ___ _ __ | |_ ___  ___    | |_ ___  ___  _ __ _  ___ ___  ___       
  / __/ _ \| '_ \ / __/ _ \ '_ \| __/ _ \/ __|   | __/ _ \/ _ \| '__| |/ __/ _ \/ __|      
 | (_| (_) | | | | (_|  __/ |_) | || (_) \__ \   | ||  __/ (_) | |  | | (_| (_) \__ \_ _ _ 
  \___\___/|_| |_|\___\___| .__/ \__\___/|___/    \__\___|\___/|_|  |_|\___\___/|___(_|_|_)
                          | |                                                            
                          |_|                                                          

Lista: una lista es un tipo de dato abstracto. Se puede ver a la lista como un contenedor dinamico de objetos que pueden ser insertados, eliminados
	y accedidos. Estos objetos reciben el nombre de nodos. Cada nodo es un registro que contiene un puntero a el elemento que va a almacenar y un puntero al siguiente nodo, excepto el ultimo que no tiene sucesor y apunta a NULL.

	Lista SIMPLEMENTE ENLAZADA: en este tipo de lista, cada nodo conoce al siguiente, de forma tal que su recorrido es unidireccional.
	Lista DOBLEMENTE ENLAZADA: en este tipo de lista, cada nodo conoce al siguiente (menos el ultimo) y al anterior (menos el primero).

Cracteristicas de las Pilas y de las Colas: ambas son un tipo de lista.

	PILAS: en ella se pueden insertar y eliminar elementos por un extremo, denominado tope (last in, first out). Su conjunto minimo de operaciones es: crear, apilar (push), desapilar (pop), tope, esta_vacia y destruir (puede variar segun quien implemente el tda).

	COLAS: posee dos extremos. Un extremo es el inicio de la cola, por donde se eliminan los elementos, y el otro extremo es el final de la cola, por donde se insertan elementos (first int, first out). Su conjunto minimo de operaciones es: crear, encolar, desencolar, primero, esta_vacia y destruir (puede variar segun quien implemente el tda).

Iterador: un iterador es una estructura que permite recorrer secuencialmente datos almacenados en un tda.

	Iterador INTERNO: permite recorrer todos los elementos de un tda sin tener que controlar el ciclo en el cual se recorre el mismo. Para ello normalmente un iterador interno es una funcion que recibe tres parametros: la lista, un puntero a una funcion y un puntero extra que funciona como un contador de todos los nodos visitados. 

	Iterador EXTERNO: es un tda que provee un conjunto de primitivas especiales para recorrer una estructura (u otro tda).

	La diferencia entre ambos es el control del flujo, en el externo puedo controlar el flujo de la iteracion mientras que en el interno dependo de lo que retorna la funcion que recibe el iterador.