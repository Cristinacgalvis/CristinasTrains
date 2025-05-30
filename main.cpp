/******************************************************************************

Juego de trenes 
Contenido 

1 Tablero 
72 cartas distribuidas asi: 
• 12 cartas rojas 
• 12 cartas azules 
• 12 cartas verdes 
• 12 cartas moradas 
• 12 cartas cafés 
• 12 cartas naranjas 

72 vagones distribuidos así: 
• 18 vagones para jugador 1 
• 18 vagones para jugador 2 
• 18 vagones para jugador 3 
• 18 vagones para jugador 4 

Instrucciones 
En un turno un jugador puede realizar una de dos posibles acciones 
1) Robar dos cartas de la zona de cartas. Las cartas robadas se deben reponer de 
la baraja. Cuando no se posean cartas en las barajas, barajar las cartas del 
descarte y crear una nueva baraja con estas. 
2) Realizar un trayecto, en cuyo caso se deben contar con la cantidad de cartas 
correspondientes a cada trayecto. Por ejemplo, para realizar el trayecto de A a 
B se necesita 4 cartas rojas. Tener el color de las cartas necesarias para cada 
trayecto. 

Las cartas usadas para completar un trayecto se deben colocar en la zona de 
descarte. 

El juego finaliza cuando un jugador tenga menos de 5 trenes disponibles para colocar. 
En cuyo se terminará de jugar esa ronda. 

Puntuación 
• Trayectos de 2 vagones dan 1 punto 
• Trayectos de 3 vagones dan 2 punto 
• Trayectos de 4 vagones dan 4 punto 
• Trayectos de 5 vagones dan 6 punto 
• Trayectos de 6 vagones dan 9 punto 

El puntaje total será la suma de todos los trayectos realizados. Gana el jugador con 
mayor cantidad de puntos.

*******************************************************************************/
// main.cpp (versión corregida y limpia)
#include "CristinasTrains.hpp"
#include <iostream>

int main() {
    while (true) {
        CristinasTrains juego;
        int numJugadores;

        std::cout << "Bienvenido a Cristina's Trains\n";
        std::cout << "¿Cuántos jugadores? ";
        std::cin >> numJugadores;

        for (int i = 0; i < numJugadores; ++i) {
            std::string nombre;
            std::cout << "Nombre del jugador " << (i + 1) << ": ";
            std::cin >> nombre;
            juego.agregarJugador(nombre);
        }

        juego.iniciarPartida();

        try {
            while (true) {
                juego.jugarTurno();
            }
        } catch (std::runtime_error& e) {
            if (std::string(e.what()) == "Reiniciar")
                std::cout << "Juego reiniciado.\n";
            else
                std::cerr << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}