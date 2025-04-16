#include "Zwierze.h"
#include "Swiat.h"
#include <cstdlib>
#include <ctime>

Zwierze::Zwierze(Swiat* swiat, int sila, int inicjatywa, int x, int y)
    : Organizm(swiat, sila, inicjatywa, x, y) {}

void Zwierze::akcja() {
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
            kolizja(cel);
        }
    }
}

void Zwierze::kolizja(Organizm* inny) {
    if (typeid(*this) == typeid(*inny)) { // ten sam gatunek => rozmnażanie
        //Świat ma metodę dodajOrganizm i klonowanie organizmu — TODO
        wiekInkrementacja();
        // swiat->dodajOrganizm();
    } else { // walka — wygrywa silniejszy
        if (this->getSila() >= inny->getSila()) {
            inny->zabij();
            setPozycja(inny->getX(), inny->getY());
        } else {
            this->zabij();
        }
    }
}
