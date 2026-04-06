# Threads

# Compilación

- `make -f MakefileThreads` para compilar y crear los ejecutables
- `make -f MakefileThreads wrapsocks=1` para simular problemas de red
- `make -f MakefileThreads clean` para limpiar

# Test
- `chmod +x ./test/*.sh` para dar permisos de ejecución
- `./test/run_tests.sh ./ ./test/casos multi-client no-valgrind 10` para correr los tests sin valgrind y con timeout de 10
- `./test/run_tests.sh ./ ./test/casos multi-client valgrind 10` para correr los tests con valgrind y con timeout de 10

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