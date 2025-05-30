// CristinasTrains.hpp (solo declaraciones)
#ifndef CRISTINASTRAINS_HPP
#define CRISTINASTRAINS_HPP

#include "Baraja.hpp"
#include "Jugador.hpp"
#include "Trayecto.hpp"
#include <vector>
#include <string>

class CristinasTrains {
private:
    std::vector<Jugador> jugadores;
    std::vector<Trayecto> trayectos;
    Baraja baraja;
    int turnoActual;
    bool finDelJuego = false;
    int rondasRestantes = 0;

    void inicializarTrayectos();
    void verificarFinDelJuego();

public:
    CristinasTrains();

    void agregarJugador(const std::string& nombre);
    void iniciarPartida();
    void jugarTurno();
    void reclamarTrayecto();
    void mostrarTrayectosDisponibles() const;
    void mostrarPuntuaciones() const;
    void mostrarMapaCuadricula() const;
};

#endif