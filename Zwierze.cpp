#include "Zwierze.h"
#include "Swiat.h"
#include <cstdlib>
#include <ctime>

Zwierze::Zwierze(Swiat* swiat, int sila, int inicjatywa, int x, int y)
    : Organizm(swiat, sila, inicjatywa, x, y) {}

void Zwierze::akcja() {

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
            kolizja(cel);
        }
    }
}

void Zwierze::kolizja(Organizm* inny) {
    if (typeid(*this) == typeid(*inny)) {

        int dx[] = { 0, 1, 0, -1 };
        int dy[] = { -1, 0, 1, 0 };

        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < swiat->getSzerokosc() && newY >= 0 && newY < swiat->getWysokosc() && swiat->getOrganizmNaPolu(newX, newY) == nullptr) {
                
                Organizm* potomek = this->klonuj(newX, newY);
                swiat->dodajOrganizm(potomek);
                return;
            }
        }

        return;
    }

    // Próba ataku
    if (inny->czyOdbilAtak(this)) {
        // Atak został odparty - TODO
        return;
    }

    // Zwykła walka
    if (this->getSila() >= inny->getSila()) {
        inny->zabij();
        setPozycja(inny->getX(), inny->getY());
    } else {
        this->zabij();
    }
}
