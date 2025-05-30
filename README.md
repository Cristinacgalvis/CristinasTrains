# Integrantes
# Xilena Piedrahita Velasquez
# Cristina Casas Galvis



# Cristina's Trains

**Cristina's Trains** es un juego de trenes por consola desarrollado en **C++**. Está diseñado como una experiencia didáctica y divertida, que pone en práctica estructuras de datos y programación orientada a objetos.

## Descripción

Este proyecto implementa:

- Estructuras tipo **pila** y **cola** para manejar cartas y descartes.
- Manejo de **archivos** (en versiones anteriores).
- Soporte para **2 a 4 jugadores** por turno.
- Visualización del **mapa en consola** con trayectos de colores.
- Reglas de juego basadas en estrategia y recolección de cartas.

---

## Objetivo

Los jugadores compiten por conectar ciudades y reclamar trayectos con cartas del mismo color. Cada trayecto otorga puntos y el juego termina cuando un jugador se queda con menos de 5 vagones.

---

## Archivos del proyecto

| Archivo               | Descripción                                |
|-----------------------|---------------------------------------------|
| `main.cpp`            | Punto de entrada del programa               |
| `CristinasTrains.cpp` | Lógica principal del juego                  |
| `CristinasTrains.hpp` | Declaración de la clase principal           |
| `Jugador.cpp/hpp`     | Clase y funciones relacionadas a jugadores  |
| `Baraja.cpp/hpp`      | Manejo de cartas y mazos                    |
| `Trayecto.hpp`        | Definición de trayectos entre ciudades      |
| `README.md`           | Este archivo de documentación               |

---

## Compilación

Este juego requiere un compilador C++ compatible con C++17 o superior.

```bash
g++ -std=c++17 main.cpp CristinasTrains.cpp Baraja.cpp Jugador.cpp -o juego
./juego
```

---

## 📄 Licencia

Este proyecto puede distribuirse bajo la licencia [MIT](LICENSE).
