# Smart Academic Task Planner

Smart Academic Task Planner es una aplicación en C++ basada en terminal, desarrollada para un curso de Estructuras de Datos. El sistema permite organizar tareas académicas mediante funciones para crear, mostrar, buscar, eliminar, procesar y guardar tareas. El proyecto integra estructuras de datos fundamentales como lista enlazada, pila, cola, tabla hash y grafo.

## Descripción

El propósito del proyecto es aplicar estructuras de datos en un contexto práctico. La aplicación permite administrar tareas académicas con información como ID, título, descripción, curso, prioridad, fecha límite y estado. También permite registrar acciones recientes, manejar una cola de tareas pendientes, buscar tareas por ID y modelar dependencias entre tareas.

## Funcionalidades

- Crear tareas académicas.
- Mostrar todas las tareas.
- Buscar tareas por ID.
- Eliminar tareas.
- Registrar historial de acciones.
- Manejar una cola de tareas pendientes.
- Procesar la próxima tarea pendiente.
- Buscar tareas usando una tabla hash.
- Registrar dependencias entre tareas.
- Detectar ciclos simples en las dependencias.
- Verificar si una tarea puede completarse según sus prerrequisitos.
- Guardar datos en archivos de texto.

## Estructuras de datos utilizadas

- **Lista enlazada:** almacena la lista principal de tareas.
- **Pila:** guarda el historial de acciones recientes.
- **Cola:** maneja las tareas pendientes en orden FIFO.
- **Tabla hash:** permite buscar tareas por ID de manera eficiente.
- **Grafo:** representa dependencias entre tareas.

## Archivos principales

```text
main.cpp
Task.h / Task.cpp
TaskList.h / TaskList.cpp
ActionStack.h / ActionStack.cpp
TaskQueue.h / TaskQueue.cpp
SearchIndex.h / SearchIndex.cpp
DependencyGraph.h / DependencyGraph.cpp
```

## Instrucciones de compilación y ejecición

Primero, entrar a la carpeta del proyecto:

```bash
cd lab03

Para compilar el proyecto se abre la terminal en la carpeta donde se encuentran los archivos .cpp y .h y se ejecuta:

g++ -std=c++17 -Wall -Wextra -pedantic main.cpp Task.cpp TaskList.cpp TaskQueue.cpp ActionStack.cpp SearchIndex.cpp DependencyGraph.cpp -o planner

Luego para ejecutar el programa:
./planner
