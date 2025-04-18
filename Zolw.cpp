#include <iostream>
#include "Zolw.h"
using namespace std;

Zolw::Zolw(Swiat* swiat, int x, int y) : Zwierze(swiat, 2, 1, x, y) {}
char Zolw::rysowanie() const {
    return 'Z';
}
Organizm* Zolw::klonuj(int x, int y) const {
    return new Zolw(swiat, x, y);
}
void Zolw::akcja() {
    wiekInkrementacja();
    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };

    int kierunek = rand() % 4;

    int ruch = rand() % 4;
    if (ruch != 0) {
        return;
    }
    int newX = x + dx[kierunek];
    int newY = y + dy[kierunek];

    if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
        Organizm* cel = swiat->getOrganizmNaPolu(newX, newY);
        if (cel == nullptr) {
            setPozycja(newX, newY);
        } else {
            kolizja(cel);
        }
    }
}
bool Zolw::czyOdbilAtak(Organizm* atakujacy) {
    if (atakujacy->getSila() < 5) {
        cout << "Zolw odbil atak!" << endl;
        return true;
    }
    return false;
}