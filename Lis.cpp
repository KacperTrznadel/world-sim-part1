#include <iostream>
#include "Lis.h"
using namespace std;

Lis::Lis(Swiat* swiat, int x, int y) : Zwierze(swiat, 3, 7, x, y) {}
char Lis::rysowanie() const {
    return 'L';
}
Organizm* Lis::klonuj(int x, int y) const {
    return new Lis(swiat, x, y);
}
void Lis::akcja() {
    wiekInkrementacja();
    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };
    int kierunek = rand() % 4;

    int newX = x + dx[kierunek];
    int newY = y + dy[kierunek];

    if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {

        Organizm* cel = swiat->getOrganizmNaPolu(newX, newY);
        if (cel == nullptr) {
            setPozycja(newX, newY);
        } else {
            return;
        }
    }
}

void Lis::akcja() {
    wiekInkrementacja();
    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };
    int kierunek = rand() % 4;

    int newX = getX() + dx[kierunek];
    int newY = getY() + dy[kierunek];

    if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc()) {
        Organizm* cel = swiat->getOrganizmNaPolu(newX, newY);
        if (cel == nullptr || cel->getSila() <= this->getSila()) {
            setPozycja(newX, newY);
        }
    }
}