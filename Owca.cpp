#include <iostream>
#include "Owca.h"
using namespace std;

Owca::Owca(Swiat* swiat, int x, int y) : Zwierze(swiat, 4, 4, x, y) {}
char Owca::rysowanie() const {
    return 'O';
}
Organizm* Owca::klonuj(int x, int y) const {
    return new Owca(swiat, x, y);
}