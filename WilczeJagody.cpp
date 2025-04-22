#include "WilczeJagody.h"
#include "Swiat.h"
#include <iostream>
using namespace std;

WilczeJagody::WilczeJagody(Swiat* swiat, int x, int y)
    : Roslina(swiat, 99, x, y) {} 
char WilczeJagody::rysowanie() const {
    return 'J';
}
Organizm* WilczeJagody::klonuj(Swiat* swiat, int x, int y) const {
    return new WilczeJagody(swiat, x, y);
}
void WilczeJagody::kolizja(Organizm* inny, int oldX, int oldY) {
    getSwiat()->dodajLog(inny->getNazwa() + " zjada Wilcze Jagody na polu (" + to_string(getX()) + "," + to_string(getY()) + ")");
    getSwiat()->dodajLog(inny->getNazwa() + " umiera na polu (" + to_string(getX()) + "," + to_string(getY()) + ")");
    inny->zabij();
    this->zabij();
}