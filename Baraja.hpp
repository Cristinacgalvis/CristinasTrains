#ifndef BARAJA_HPP
#define BARAJA_HPP

#include <vector>
#include <queue>
#include <stack>
#include <string>

enum Color { ROJO, AZUL, VERDE, MORADO, CAFE, NARANJA };

std::string colorToString(Color c);

struct Carta {
    Color color;
};

class Baraja {
private:
    std::queue<Carta> mazo;
    std::stack<Carta> descarte;
    std::vector<Carta> visibles;

public:
    Baraja();

    void inicializarMazo();
    void rellenarVisibles();
    void mostrarVisibles();

    Carta robarDelMazo();
    Carta robarVisible(int indice);
    void agregarAlDescarte(Carta c);
    void reciclarDescarte();

    // NUEVO: Acceso controlado a visibles
    std::vector<Carta> getVisibles() const;
    void setVisibles(const std::vector<Carta>& nuevasVisibles);
};

#endif