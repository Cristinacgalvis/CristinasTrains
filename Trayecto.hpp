#ifndef TRAYECTO_HPP
#define TRAYECTO_HPP

#include "Baraja.hpp"
#include <string>

struct Trayecto {
    char ciudadA;
    char ciudadB;
    Color color;
    int longitud;
    bool reclamado;
    int jugadorId;

    // Constructor que evita los errores al usar push_back({...})
    Trayecto(char a, char b, Color col, int len)
        : ciudadA(a), ciudadB(b), color(col), longitud(len),
          reclamado(false), jugadorId(-1) {}

    int puntos() const {
        switch (longitud) {
            case 2: return 1;
            case 3: return 2;
            case 4: return 4;
            case 5: return 6;
            case 6: return 9;
            default: return 0;
        }
    }

    std::string descripcion() const {
        return std::string(1, ciudadA) + " - " + ciudadB + " (" +
               colorToString(color) + ", " + std::to_string(longitud) + ")";
    }
};

#endif