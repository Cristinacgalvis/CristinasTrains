#include "Jugador.hpp"
#include <iostream>

Jugador::Jugador(std::string nombre) : nombre(nombre), vagonesDisponibles(18), puntos(0) {}

void Jugador::agregarCarta(Carta carta) {
    mano.push_back(carta);
}

void Jugador::mostrarMano() const {
    std::cout << "Mano de " << nombre << ": ";
    for (auto& c : mano)
        std::cout << colorToString(c.color) << " ";
    std::cout << "\n";
}

std::string Jugador::getNombre() const { return nombre; }
int Jugador::getVagones() const { return vagonesDisponibles; }
int Jugador::getPuntos() const { return puntos; }
void Jugador::usarVagones(int cantidad) { vagonesDisponibles -= cantidad; }
void Jugador::sumarPuntos(int pts) { puntos += pts; }