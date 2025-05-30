#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include "Baraja.hpp"
#include <vector>
#include <string>

class Jugador {
public:
    std::string nombre;
    std::vector<Carta> mano;
    int vagonesDisponibles;
    int puntos;

    Jugador(std::string nombre);
    void agregarCarta(Carta carta);
    void mostrarMano() const;
    std::string getNombre() const;
    int getVagones() const;
    int getPuntos() const;
    void usarVagones(int cantidad);
    void sumarPuntos(int pts);
};

#endif