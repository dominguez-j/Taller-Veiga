# Sockets

# Compilación

- `make -f MakefileSockets` para compilar y crear los ejecutables
- `make -f MakefileSockets wrapsocks=1` para simular problemas de red
- `make -f MakefileSockets clean` para limpiar

# Ejecución

- `./server <servname> <type-of-protocol>`
- `./client <hostname> <servname> <username>`

# Comandos

El cliente escribe por consola:
- `buy <weapon_name>`
- `ammo <weapon_name> <ammo_count>`

Donde el `<weapon_name>` puede ser `"glock", "ak-47", "m3", "awp"`

# Código fuente usado
Biblioteca de Sockets - Autor: @eldipa - Licencia: GPL v2 - [Repositorio](https://github.com/eldipa/sockets-en-cpp)