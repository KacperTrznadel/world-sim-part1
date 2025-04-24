#include "WilczeJagody.h"
#include "Swiat.h"
#include <iostream>
using namespace std;

WilczeJagody::WilczeJagody(Swiat* swiat, int x, int y)
    : Roslina(swiat, 99, x, y, "Wilcze Jagody") {} 
char WilczeJagody::rysowanie() const {
    return 'J';
}
Organizm* WilczeJagody::klonuj(Swiat* swiat, int x, int y) const {
    return new WilczeJagody(swiat, x, y);
}
void WilczeJagody::kolizja(Organizm* inny, int oldX, int oldY) {
    getSwiat()->dodajLog(inny->getNazwa() + string(" zjada Wilcze Jagody na polu (") + to_string(this->getX()) + "," + to_string(this->getY()) + ")");
    getSwiat()->dodajLog(inny->getNazwa() + string(" umiera na polu (") + to_string(this->getX()) + "," + to_string(this->getY()) + ")");
    inny->setPozycja(this->getX(), this->getY());
    this->zabij();
    inny->zabij();
}