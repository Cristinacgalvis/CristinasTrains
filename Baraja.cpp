#include "Baraja.hpp"
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>

std::string colorToString(Color c) {
    switch(c) {
        case ROJO: return "Rojo";
        case AZUL: return "Azul";
        case VERDE: return "Verde";
        case MORADO: return "Morado";
        case CAFE: return "Café";
        case NARANJA: return "Naranja";
        default: return "Desconocido";
    }
}

Baraja::Baraja() {
    inicializarMazo();
    rellenarVisibles();
}

void Baraja::inicializarMazo() {
    std::vector<Carta> cartas;
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 12; ++j)
            cartas.push_back({static_cast<Color>(i)});
    std::shuffle(cartas.begin(), cartas.end(), std::mt19937(std::random_device()()));
    for (auto& c : cartas)
        mazo.push(c);
}

void Baraja::rellenarVisibles() {
    visibles.clear();
    while (visibles.size() < 5 && !mazo.empty()) {
        visibles.push_back(mazo.front());
        mazo.pop();
    }
}

void Baraja::mostrarVisibles() {
    std::cout << "Cartas visibles:\n";
    for (size_t i = 0; i < visibles.size(); ++i)
        std::cout << i + 1 << ") " << colorToString(visibles[i].color) << "\n";
}

Carta Baraja::robarDelMazo() {
    if (mazo.empty()) {
        if (descarte.empty()) throw std::runtime_error("¡No hay cartas disponibles!");
        reciclarDescarte();
    }
    Carta c = mazo.front();
    mazo.pop();
    return c;
}

Carta Baraja::robarVisible(int indice) {
    if (indice < 0 || indice >= static_cast<int>(visibles.size()))
        throw std::runtime_error("índice inválido de carta visible.");
    Carta c = visibles[indice];
    visibles.erase(visibles.begin() + indice);
    if (!mazo.empty()) {
        visibles.push_back(mazo.front());
        mazo.pop();
    } else if (!descarte.empty()) {
        reciclarDescarte();
    }
    return c;
}

void Baraja::agregarAlDescarte(Carta c) {
    descarte.push(c);
}

void Baraja::reciclarDescarte() {
    std::vector<Carta> cartas;
    while (!descarte.empty()) {
        cartas.push_back(descarte.top());
        descarte.pop();
    }
    std::shuffle(cartas.begin(), cartas.end(), std::mt19937(std::random_device()()));
    for (auto& c : cartas)
        mazo.push(c);
}

std::vector<Carta> Baraja::getVisibles() const {
    return visibles;
}

void Baraja::setVisibles(const std::vector<Carta>& nuevasVisibles) {
    visibles = nuevasVisibles;
}