// CristinasTrains.cpp (trazado en L, sin diagonales)
#include "CristinasTrains.hpp"
#include <iostream>
#include <map>
#include <cmath>

#define BG_ROJO     "\x1B[41m"
#define BG_AZUL     "\x1B[44m"
#define BG_VERDE    "\x1B[42m"
#define BG_MORADO   "\x1B[45m"
#define BG_CAFE     "\x1B[48;2;139;69;19m"
#define BG_NARANJA  "\x1B[48;2;255;128;0m"
#define RESET       "\x1b[0m"

std::string colorToBG(Color c) {
    switch(c) {
        case ROJO: return BG_ROJO;
        case AZUL: return BG_AZUL;
        case VERDE: return BG_VERDE;
        case MORADO: return BG_MORADO;
        case CAFE: return BG_CAFE;
        case NARANJA: return BG_NARANJA;
        default: return RESET;
    }
}
CristinasTrains::CristinasTrains() : turnoActual(0) {}

void CristinasTrains::agregarJugador(const std::string& nombre) {
    jugadores.emplace_back(nombre);
}

void CristinasTrains::iniciarPartida() {
    std::cout << "\n--- Iniciando partida ---\n";
    inicializarTrayectos();
    for (auto& jugador : jugadores)
        for (int i = 0; i < 4; ++i)
            jugador.agregarCarta(baraja.robarDelMazo());
}

void CristinasTrains::inicializarTrayectos() {
    trayectos.push_back(Trayecto('A', 'B', ROJO, 4));
    trayectos.push_back(Trayecto('B', 'C', ROJO, 3));
    trayectos.push_back(Trayecto('A', 'F', AZUL, 4));
    trayectos.push_back(Trayecto('F', 'E', VERDE, 2));
    trayectos.push_back(Trayecto('E', 'D', CAFE, 2));
    trayectos.push_back(Trayecto('F', 'G', NARANJA, 2));
    trayectos.push_back(Trayecto('G', 'C', CAFE, 2));
    trayectos.push_back(Trayecto('F', 'H', NARANJA, 2));
    trayectos.push_back(Trayecto('H', 'K', AZUL, 2));
    trayectos.push_back(Trayecto('K', 'L', ROJO, 2));
    trayectos.push_back(Trayecto('L', 'M', MORADO, 2));
    trayectos.push_back(Trayecto('K', 'P', VERDE, 2));
    trayectos.push_back(Trayecto('P', 'Q', MORADO, 2));
    trayectos.push_back(Trayecto('Q', 'S', CAFE, 2));
    trayectos.push_back(Trayecto('P', 'O', AZUL, 2));
    trayectos.push_back(Trayecto('O', 'R', MORADO, 2));
    trayectos.push_back(Trayecto('K', 'I', MORADO, 2));
    trayectos.push_back(Trayecto('I', 'J', AZUL, 2));
    trayectos.push_back(Trayecto('J', 'N', NARANJA, 2));
    trayectos.push_back(Trayecto('N', 'O', VERDE, 2));
}

void CristinasTrains::mostrarTrayectosDisponibles() const {
    std::cout << "\n--- Trayectos Disponibles ---\n";
    for (size_t i = 0; i < trayectos.size(); ++i)
        if (!trayectos[i].reclamado)
            std::cout << i + 1 << ") " << trayectos[i].descripcion() << "\n";
}

void CristinasTrains::reclamarTrayecto() {
    Jugador& jugador = jugadores[turnoActual];
    mostrarTrayectosDisponibles();

    std::cout << "Seleccione un trayecto (número): ";
    int indice;
    std::cin >> indice;
    indice -= 1;

    if (indice < 0 || indice >= static_cast<int>(trayectos.size()) || trayectos[indice].reclamado) {
        std::cout << "Índice inválido o ya reclamado.\n";
        return;
    }

    Trayecto& t = trayectos[indice];
    int cantidad = 0;
    for (auto& carta : jugador.mano)
        if (carta.color == t.color) cantidad++;

    if (cantidad < t.longitud) {
        std::cout << "No tienes suficientes cartas " << colorToString(t.color) << ".\n";
        return;
    }

    std::vector<Carta> nuevas;
    int usadas = 0;
    for (auto& carta : jugador.mano) {
        if (carta.color == t.color && usadas < t.longitud) {
            baraja.agregarAlDescarte(carta);
            usadas++;
        } else {
            nuevas.push_back(carta);
        }
    }
    jugador.mano = nuevas;
    jugador.usarVagones(t.longitud);
    jugador.sumarPuntos(t.puntos());
    t.reclamado = true;
    t.jugadorId = turnoActual;

    std::cout << "¡Trayecto reclamado con éxito!\n";
}

void CristinasTrains::mostrarPuntuaciones() const {
    std::cout << "\n📊 Puntajes finales:\n";
    int maxPuntos = -1;
    std::string ganador;

    for (const auto& j : jugadores) {
        std::cout << j.getNombre()
                  << " - Puntos: " << j.getPuntos()
                  << ", Vagones restantes: " << j.getVagones() << "\n";
        if (j.getPuntos() > maxPuntos) {
            maxPuntos = j.getPuntos();
            ganador = j.getNombre();
        }
    }

    std::cout << "\n🏆 Ganador: " << ganador << " con " << maxPuntos << " puntos!\n";
}

void CristinasTrains::verificarFinDelJuego() {
    Jugador& jugador = jugadores[turnoActual];

    if (!finDelJuego && jugador.getVagones() < 5) {
        std::cout << "⚠️ " << jugador.getNombre()
                  << " tiene menos de 5 vagones. Última ronda.\n";
        finDelJuego = true;
        rondasRestantes = jugadores.size();
    }

    if (finDelJuego) {
        rondasRestantes--;
        if (rondasRestantes <= 0) {
            mostrarPuntuaciones();
            std::cout << "🏍️ Fin del juego. ¡Gracias por jugar Cristina's Trains!\n";
            exit(0);
        }
    }
}

void CristinasTrains::jugarTurno() {
    Jugador& jugador = jugadores[turnoActual];
    std::cout << "\nTurno de " << jugador.getNombre() << "\n";
    jugador.mostrarMano();

    std::cout << "1. Robar 2 cartas del mazo\n";
    std::cout << "2. Reclamar trayecto\n";
    std::cout << "3. Mostrar mapa del juego (cuadrícula)\n";
    std::cout << "4. Terminar turno\n";

    int op;
    std::cin >> op;

    switch (op) {
        case 1: {
            for (int i = 0; i < 2; ++i) {
                Carta c = baraja.robarDelMazo();
                std::cout << "Robaste: " << colorToString(c.color) << "\n";
                jugador.agregarCarta(c);
            }
            break;
        }
        case 2:
            reclamarTrayecto();
            break;
        case 3:
            mostrarMapaCuadricula();
            break;
        case 4:
        default:
            break;
    }

    turnoActual = (turnoActual + 1) % jugadores.size();
    verificarFinDelJuego();
}

void CristinasTrains::mostrarMapaCuadricula() const {
    const int FILAS = 20;
    const int COLS = 20;
    std::string mapa[FILAS][COLS];

    for (int i = 0; i < FILAS; ++i)
        for (int j = 0; j < COLS; ++j)
            mapa[i][j] = "  ";

    std::map<char, std::pair<int, int>> coords = {
        {'A', {8, 1}}, {'B', {5, 3}}, {'C', {14, 3}}, {'D', {1, 4}},
        {'E', {4, 6}}, {'F', {8, 6}}, {'G', {12, 6}}, {'H', {8, 9}},
        {'I', {5, 10}}, {'J', {2, 11}}, {'K', {8, 12}}, {'L', {12, 12}},
        {'M', {14, 13}}, {'N', {2, 14}}, {'O', {4, 16}}, {'P', {8, 16}},
        {'Q', {12, 16}}, {'R', {6, 19}}, {'S', {10, 19}}
    };

    for (const auto& t : trayectos) {
        if (!t.reclamado) continue;
        if (coords.count(t.ciudadA) && coords.count(t.ciudadB)) {
            auto coordA = coords.at(t.ciudadA);
            auto coordB = coords.at(t.ciudadB);
            int r1 = coordA.first, c1 = coordA.second;
            int r2 = coordB.first, c2 = coordB.second;
            std::string color = colorToBG(t.color);

            // Paso 1: trazar verticalmente de r1 a r2 en c1
            int dr = (r2 - r1) == 0 ? 0 : (r2 - r1) / std::abs(r2 - r1);
            int r = r1;
            while (r != r2) {
                if (r >= 0 && r < FILAS && c1 >= 0 && c1 < COLS)
                    mapa[r][c1] = color + "  " + RESET;
                r += dr;
            }

            // Paso 2: trazar horizontalmente de c1 a c2 en r2
            int dc = (c2 - c1) == 0 ? 0 : (c2 - c1) / std::abs(c2 - c1);
            int c = c1;
            while (c != c2) {
                if (r2 >= 0 && r2 < FILAS && c >= 0 && c < COLS)
                    mapa[r2][c] = color + "  " + RESET;
                c += dc;
            }
        }
    }

    for (const auto& entry : coords) {
        int y = entry.second.first;
        int x = entry.second.second;
        if (y >= 0 && y < FILAS && x >= 0 && x < COLS)
            mapa[y][x] = std::string(1, entry.first) + " ";
        else
            std::cerr << "⚠ Coordenada inválida para ciudad " << entry.first << ": (" << y << "," << x << ")\n";
    }

    std::cout << "\n🗺️  Mapa del juego (cuadrícula 20x20):\n";
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLS; ++j)
            std::cout << mapa[i][j];
        std::cout << "\n";
    }
}
