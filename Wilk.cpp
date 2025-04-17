#include <iostream>
#include "Wilk.h"
using namespace std;

Wilk::Wilk(Swiat* swiat, int x, int y) : Zwierze(swiat, 9, 5, x, y) {}
char Wilk::rysowanie() const {
    return 'W';
}
Organizm* Wilk::klonuj(int x, int y) const {
    return new Wilk(swiat, x, y);
}