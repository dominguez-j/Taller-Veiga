# Threads

# Compilación

- `make -f MakefileThreads` para compilar y crear los ejecutables
- `make -f MakefileThreads wrapsocks=1` para simular problemas de red
- `make -f MakefileThreads clean` para limpiar

# Ejecución

- `./server <port>`
- `./client <host> <port>` 

# Comandos

El cliente escribe por consola:
- `create <nombre-de-partida>`
- `listar`
- `unirse <nombre-de-partida>`
- `jugar <columna> <fila>`

# Código fuente usado
Biblioteca de Sockets - Autor: @eldipa - Licencia: GPL v2 - [Repositorio](https://github.com/eldipa/sockets-en-cpp) <br>
Biblioteca de Threads - Autor: @eldipa - Licencia: GPL v2 - [Repositorio](https://github.com/eldipa/hands-on-threads/blob/master/libs/thread.h)