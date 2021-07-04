                                                                ,'\
                                    _.----.       ____         ,'  _\   ___    ___     ____
                                _,-'       `.    |    |  /`.   \,-'    |   \  /   |   |    \  |`.
                                \      __    \   '-.  | /   `.  ___    |    \/    |   '-.   \ |  |
                                 \     \ \   | __  |  |/    ,','_  `.  |          | __  |    \|  |
                                  \     \/  /,' _`.|      ,' / / / /   |          ,'   `.|    |  |
                                   \     ,-'/  /   \    ,'   | \/ / ,`.|         /   /   \ |     |
                                    \    \ |   \_/  |   `-.  \    `'  /|  |    | |   \_/ | |\    |
                                     \    \ \      /       `-.`.___,-' |  |\  /| \      /  | |   |
                                      \    \ `.__,'|  |`-._    |       |__| \/ |  `.__,'|  | |   |
                                       \_.-'       |__|    `-._|               '-.|     '-.| |   |
                                                                `                            '-._|

---------------------------------------------------------------------------------------------------------------------------------------------------

Se hace entrega de:
    la implementacion de un TDA heap
    la implementacion de el trabajo practico numero 2 junto con todos los archivos necesarios para compilarlo y ejecutarlo correctamente

Linea de compilacion: gcc *.c -o batalla -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
Liea de ejecucion: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./batalla

Funcionamiento: se arranca creando las dos estructuras principales (el personaje principal y el heap de gimnasios).
    El menu de inicio permite al usuario cargar el archivo de personaje principal y el/los archivo/s de gimnasio/s que desee. Tambien
    le dara la opcion al usuario de simular una partida para la cual no se pedira ninguna entrada por teclado, jugando asi todos los 
    combates hasta ganar o perder.
    Al iniciar la partida se cargan las estructuras creadas con la informacion de los archivos proporcionados por el usuario.
    Una vez cargadas correctamente las estructuras, el menu de gimnasio le podra proporcionar al usuario informacion de el personaje 
    principal y sus pokemon, la informacion del gimnasio actual, la posibilidad de cambiar los pokemon de combate o la opcion de 
    iniciar el combate.
    La logica de pelea es la siguiente: se pelea contra todos los pokemon de un entrenador. Si todos los pokemon del entrenador rival 
    son derrotados se pasara a combatir contra los pokemon del siguiente entrenador y asi hasta combatir contra todos los entrenadores 
    del gimnasio. Si todos los pokemon del personaje principal son derrotados se pierde la partida. EL menu de derrota la dara al 
    usuario la posibilidad de cambiar sus pokemon de combate y de reintentar el gimnasio o de finalizar la partida.
    En caso de derrotar a todos los pokemon del lider del gimnasio el usuario tendra la posibilidad de "tomar prestado" un pokemon 
    del lider, podra cambiar sus pokemon de combate si asi lo desea o combatir contra el gimnasio siguiente.
    En el caso de no haber mas gimnasios se notifica al usuario que se convirtio en maestro pokemon.
    Todas las estructuras allocadas en memoria se liberan usando un destructor incorporado en la estructura del heap.

---------------------------------------------------------------------------------------------------------------------------------------------------
           _                   _                             
  ___  ___| |_ _ __ _   _  ___| |_ _   _ _ __ __ _ ___       
 / _ \/ __| __| '__| | | |/ __| __| | | | '__/ _` / __|      
|  __/\__ \ |_| |  | |_| | (__| |_| |_| | | | (_| \__ \_ _ _ 
 \___||___/\__|_|   \__,_|\___|\__|\__,_|_|  \__,_|___(_|_|_)

 • Gimnasios: los gimnasios estan ordenados en el heap mediante dificultad y se recorren siguiendo un orden creciente.
    (por eso la implementacion es de un heap MINIMAL).   

 • Entrenadores: la estructura de el entrenador tendra
    → el nombre del mismo
    → una lista de pokemon. Elegi la lista ya que en el momento en que el usuario decide tomar un pokemon
        del lider se pueden usar las funciones de lista que involucran posicion.

Los entrenadores de un gimnasio se iran apilando en una PILA. Elegi este TDA ya que al momento de leer el/los
    archivo/s de gimnasio/s el primer entrenador que se lee (el lider) sera el ultimo entrenador con el cual se
    va a combatir. Se sigue la logica de "first in last out".

• Personaje principal: la estructura de el personaje principal tendra
    → el nombre del mismo
    → una lista de pokemon obtenidos. Elegi la lista ya que en el momento en que el usuario decide cambiar sus pokemon
        de combate se pueden usar las funciones de lista que involucran posicion.
    → una cola de pokemon de combate. Elegi la COLA ya que al leer el archivo de el personaje principal, los
        primeros 6 pokemon leidos deberan combatir. Los pokemon de combate seguiran la logica de "first in first
        out" al momento del combate.                                                         
                                                         
