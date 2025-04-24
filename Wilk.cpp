#include <iostream>
#include <string>
#include "Wilk.h"
#include "Swiat.h"
using namespace std;

Wilk::Wilk(Swiat* swiat, int x, int y) : Zwierze(swiat, 9, 5, x, y, "Wilk") {}
char Wilk::rysowanie() const {
    return 'W';
}
Organizm* Wilk::klonuj(Swiat* swiat, int x, int y) const {
    string nowyLog = "Wilk rozmnaza sie wspolnie z innym wilkiem. Nowy wilk na polu: " + to_string(x) + ", " + to_string(y);
    swiat->dodajLog(nowyLog);
    return new Wilk(swiat, x, y);
}