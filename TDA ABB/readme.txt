										  	  _______ _____                     ____  ____  
											 |__   __|  __ \   /\         /\   |  _ \|  _ \ 
											    | |  | |  | | /  \       /  \  | |_) | |_) |
											    | |  | |  | |/ /\ \     / /\ \ |  _ <|  _ < 
											    | |  | |__| / ____ \   / ____ \| |_) | |_) |
											    |_|  |_____/_/    \_\ /_/    \_\____/|____/ 
											                                              
---------------------------------------------------------------------------------------------------------------------------------------------------	

Se hace entrega de:
	la implementacion de una arbol binario de busqueda
	la implementacion de un iterador interno para dicha estructura
	un conjunto de pruebas que comprueba el correcto funcionamiento del TDA

Linea de compilacion: gcc *.c -o abb -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
Liea de ejecucion: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb

Funcionamiento: el arbol se crea reservando la memoria necesaria para el mismo. Para insertar un elemento se reserva en memoria el espacio 
	suficiente para la estructura de un nodo. 
	Se van insertando nodos de forma ordenada utilizando la funcion de comparacion del arbol, a la derecha los elementos mayores al elemento del nodo actual y a la izquierda los elementos	menores o iguales.
	El usuario puede buscar un elemento que desee con la funcion arbol_buscar, puede obtener la raiz del arbol con la funcion arbol_raiz y tambien saber si el arbol esta vacio con la funcion arbol_vacio.
	Tambien se cuenta con 3 funciones que recorren el arbol en secuencia inorden, postorden o preorden y con un iterador interno el cual recorre el arbol y me devuelve la cantidad de elementos que se recorrieron.
	-> El usuario es responsable de liberar los elementos almacenados en el heap con el destructor del arbol <-

---------------------------------------------------------------------------------------------------------------------------------------------------
                                 _                _                  _                     
                                | |              | |                (_)                    
   ___ ___  _ __   ___ ___ _ __ | |_ ___  ___    | |_ ___  ___  _ __ _  ___ ___  ___       
  / __/ _ \| '_ \ / __/ _ \ '_ \| __/ _ \/ __|   | __/ _ \/ _ \| '__| |/ __/ _ \/ __|      
 | (_| (_) | | | | (_|  __/ |_) | || (_) \__ \   | ||  __/ (_) | |  | | (_| (_) \__ \_ _ _ 
  \___\___/|_| |_|\___\___| .__/ \__\___/|___/    \__\___|\___/|_|  |_|\___\___/|___(_|_|_)
                          | |                                                            
                          |_|                                                          

ABB: es un tipo particular de arbol binario que que puede ser vacio o en cada nodo del mismo contener un valor clave que satisfaga las siguientes
	condiciones:
	1. la clave en el nodo izquierdo del hijo (si existe) es menor que la clave en el nodo padre
	2. la clave en el nodo derecho del hijo (si existe) es mayor que la clave en el nodo padre
	3. los arboles derecho e izquierdo son tambien arboles binarios de busqueda

	La diferencia entre un arbol binario y un arbol binario de busqueda radica en la regla para insertar elementos. El arbol binario no tiene
	especificado ningun tipo de regla para poder insertar elementos, en cambio en el ABB si uno se mueve al subarbol derecho sabe que se mueve
	a un subarbol con claves mas grandes. Y si uno se mueve hacia el subarbol izquierdo el mismo almacenara valores de datos con claves mas 
	pequeñas.

Objetivo de tener una funcion de destruccion: poder destruir el arbol en cualquier momento sin importar cuantos nodos tenga el mismo. Si esta no
	existiese, el usuario tendria que llevar un seguimiento de los nodos que hay en el arbol y luego borrarlos uno por uno, lo cual es
	engorroso e incrementa las posibilidades de que haya perdidas de memoria.

Complejidad:
	
	Complejidad constante, independiente de lo que reciba la funcion, el rendimiento va a ser constante.
		- arbol_crear
		- arbol_raiz
		- arbol_vacio
	
	O(log(n)): a medida que aumenta la cantidad de datos, el número de operaciones aumenta, pero no de forma proporcional a los datos
		(no es necesario recorrer todos los elementos).
		En estas funciones se divide el arbol en 2 y se avanza, se divide el arbol en 2 y se avanza, etc.
		- arbol_insertar 
		- arbol_borrar
		- arbol_buscar
	
	O(n): a medida que aumentan los datos el número de operaciones aumenta de forma proporcional. En estas funciones se recorre el arbol entero.
		- arbol_recorrido_inorden
		- arbol_recorrido_preorden
		- arbol_recorrido_postorden
		- arbol_destruir
		- abb_con_cada_elemento