  _______     _______ _   _ _____ ___    ____   ___  _  _______ __  __  ___  _   _ 
 | ____\ \   / / ____| \ | |_   _/ _ \  |  _ \ / _ \| |/ / ____|  \/  |/ _ \| \ | |
 |  _|  \ \ / /|  _| |  \| | | || | | | | |_) | | | | ' /|  _| | |\/| | | | |  \| |
 | |___  \ V / | |___| |\  | | || |_| | |  __/| |_| | . \| |___| |  | | |_| | |\  |
 |_____|  \_/  |_____|_| \_| |_| \___/  |_|    \___/|_|\_\_____|_|  |_|\___/|_| \_|
                                                                                   
----------------------------------------------------------------------------------------------------------------------------------

Introduccion sobre el funcionamiento: el programa le brinda la posibilidad al entrenador de trasladar los 
	pokemon que desee desde un arrecife a un acuario para el evento pokemon de Misty.
	El programa se encarga de analizar el arrecife indicado, cargando la informacion de los pokemon que viven
	dentro de el. Luego crea un acuario en donde van a poder trasladarse los pokemon que el entrenador desee.
	El entrenador va a poder trasladar el tipo de pokemon y la cantidad de estos que desee, siempre y cuando haya
	suficientes pokemon de ese tipo en el arrecife para trasladar. 
	Tambien se le dara la opcion de ver por pantalla los pokemon que quedaron en el arrecife.
	Una vez hechos los traslados deseados, se le devuelve al entrenador la informacion de los pokemon que traslado al
	acuario.

----------------------------------------------------------------------------------------------------------------------------------

Linea de compilacion: gcc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesca
Linea de ejecucion: ./evento_pesca

----------------------------------------------------------------------------------------------------------------------------------

/*
	-Punteros: un puntero es una variable que almacena una direccion de una posicion de memoria.
	
	-Aritmetica de punteros:

		+ Operador direccion(&): permite acceder a la direccion de memoria de una variable.

		+ Operador de Indireccion(*): permite declarar un tipo de dato puntero y tambien permite ver el 
			valor que esta en la direccion asignada.

		+ Incrementos(++) y decrementos(--): a un puntero se le puede aplicar cualquier operacion de suma o resta. 
			Por ejemplo: si declaro int* ptr, ptr apunta a cierta direccion de memoria. Pero la expresion ptr+i es un puntero 
			que apunta a la direccion de ptr sumandole i veces el espacio ocupado por el elemento del tipo al que apunta (en 
			este caso un int).

	-Punteros a funciones: es la direccion de memoria donde reside una determinada funcion. Ademas permite ejecutar a la funcion 
			desde cualquier parte del programa.
			Los punteros a funciones en C pueden:
				1. ser elementos de un vector.
				2. ser pasados como parametros a una funcion.
				3. ser devueltos por una funcion.

	-Malloc y realloc: estas funciones estan incluidas en la libreria stdlib.

		+ La funcion malloc() reserva size bytes de memoria y devuelve un puntero que apunta a esa memoria reservada. En caso de
			fallar devuelve NULL, lo que permite saber si hubo errores en la asignacion de memoria. 

		+ La funcion realloc() modifica el tamanio del bloque de memoria apuntado por ptr en size bytes sin cambiar su contenido.
			 Si el puntero que se le pasa tiene el valor nulo, esta función actua como malloc. En caso de fallar devolvera NULL.
*/

----------------------------------------------------------------------------------------------------------------------------------

