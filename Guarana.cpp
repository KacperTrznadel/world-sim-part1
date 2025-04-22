#include "Guarana.h"
#include "Swiat.h"
#include <iostream>
using namespace std;

Guarana::Guarana(Swiat* swiat, int x, int y)
    : Roslina(swiat, 0, x, y) {}
char Guarana::rysowanie() const {
    return 'G';
}
Organizm* Guarana::klonuj(Swiat* swiat, int x, int y) const {
    return new Guarana(swiat, x, y);
}
void Guarana::kolizja(Organizm* inny, int oldX, int oldY) {
    getSwiat()->dodajLog(inny->getNazwa() + " zjada Guarane na polu (" + to_string(getX()) + "," + to_string(getY()) + ")");
    getSwiat()->dodajLog(inny->getNazwa() + " zwieksza sile o 3. Jest ona teraz rowna " + to_string(inny->getSila() + 3));
    inny->setSila(inny->getSila() + 3);
    this->zabij();
}