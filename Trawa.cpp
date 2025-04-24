#include "Trawa.h"
#include "Swiat.h"
#include <iostream>
using namespace std;

Trawa::Trawa(Swiat* swiat, int x, int y)
    : Roslina(swiat, 0, x, y, "Trawa") {}
char Trawa::rysowanie() const {
    return 'T';
}
Organizm* Trawa::klonuj(Swiat* swiat, int x, int y) const {
    return new Trawa(swiat, x, y);
}